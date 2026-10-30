// 题目：2977. 转换字符串的最小成本 II（Minimum Cost to Convert String II）
// 思路：把规则里的字符串插入 Trie 并编号，用 Floyd 求出编号之间的最小转换成本；再对 source 做带记忆化的 DFS，从 i 出发让 source、target 同步沿两条 Trie 下行，两边同时落在某个规则串结尾时就尝试整段转换。
// 时间复杂度：O(V^3 + n^2)，V 为规则串编号数、n 为串长；空间复杂度：O(V^2 + n)，邻接矩阵与记忆化数组。
class Node {  // Trie 结点：26 个儿子指针，外加一个规则串编号
public:  // 成员对外可见
    Node* children[26];  // 26 个小写字母分支，指向子结点
    int v = -1;  // v 是该串的编号，-1 表示这里不是一个规则串的结尾
    Node() {  // 构造函数：把所有儿子置空
        fill(children, children + 26, nullptr);  // fill 批量把 26 个指针设为 nullptr
    }  // 构造完成
};  // Node 定义结束

class Solution {  // LeetCode 约定的题解类
private:  // 以下为内部实现细节
    const long long inf = 1LL << 60;  // inf 表示不可达，1LL<<60 相加也不会溢出 long long
    Node* root = new Node();  // Trie 根结点，所有规则串共享同一棵 Trie
    int idx;  // 已分配的字符串编号个数，同时也是 Floyd 的规模

    vector<vector<long long>> g;  // 转换成本的邻接矩阵，规模按编号上界 m<<1 开
    string s;  // 缓存输入的 source，供 dfs 使用
    string t;  // 缓存输入的 target，供 dfs 使用
    vector<long long> f;  // 记忆化数组：f[i] 表示从下标 i 转换到末尾的最小成本

public:  // 题解方法对外可见
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {  // 参数：source/target 两串；original/changed/cost 为转换规则及代价
        int m = cost.size();  // 规则条数 m，编号上界为 2m
        g = vector<vector<long long>>(m << 1, vector<long long>(m << 1, inf));  // 构造 (2m)x(2m) 的矩阵，初值全为不可达
        s = source;  // 保存 source
        t = target;  // 保存 target

        for (int i = 0; i < g.size(); ++i) {  // 逐个编号处理，把对角线成本初始化为 0
            g[i][i] = 0;  // 同一字符串转成自己不需要任何代价
        }  // 对角线初始化循环结束

        for (int i = 0; i < m; ++i) {  // 逐条处理转换规则
            int x = insert(original[i]);  // 把起点串插入 Trie，拿到它的编号
            int y = insert(changed[i]);  // 把终点串插入 Trie，拿到它的编号
            g[x][y] = min(g[x][y], static_cast<long long>(cost[i]));  // 同一起终对可能有多条规则，保留最便宜的一条
        }  // 规则处理循环结束

        for (int k = 0; k < idx; ++k) {  // Floyd 的中间点 k
            for (int i = 0; i < idx; ++i) {  // 起点 i
                if (g[i][k] >= inf) {  // g[i][k] 不可达就无需松弛
                    continue;  // 直接跳过，省掉整个内层循环
                }  // 不可达分支结束
                for (int j = 0; j < idx; ++j) {  // 终点 j
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);  // 松弛：借助 k 中转更便宜则更新
                }  // 终点 j 循环结束
            }  // 起点 i 循环结束
        }  // 中间点 k 循环结束

        f = vector<long long>(s.length(), -1);  // f 初始化为 -1，表示该位置还没计算过
        long long ans = dfs(0);  // 从下标 0 开始做记忆化搜索
        return ans >= inf ? -1 : ans;  // 无解返回 -1，否则返回最小总成本
    }  // 方法结束

private:  // 内部辅助函数区
    int insert(const string& w) {  // 把字符串 w 插入 Trie，返回它的编号
        Node* node = root;  // 从根开始走
        for (char c : w) {  // 逐字符下行，Trie 的深度即字符串长度
            int i = c - 'a';  // 字符映射成 0..25 的下标
            if (node->children[i] == nullptr) {  // 该分支还不存在
                node->children[i] = new Node();  // 新建结点挂到该分支上
            }  // 新建分支处理结束
            node = node->children[i];  // 沿分支走到下一层
        }  // 字符串逐字符下行结束
        if (node->v < 0) {  // 这个串还没有分配过编号
            node->v = idx++;  // 分配新编号（idx 后自增）
        }  // 编号分配分支结束
        return node->v;  // 返回字符串对应的编号
    }  // insert 结束

    long long dfs(int i) {  // 记忆化 DFS：求从下标 i 转换到串尾的最小成本
        if (i >= s.length()) {  // 已经扫完整个串
            return 0;  // 无需再转换，收尾成本为 0
        }  // 递归边界分支结束
        if (f[i] != -1) {  // 该位置已经算过
            return f[i];  // 直接返回缓存值
        }  // 缓存命中分支结束
        long long res = (s[i] == t[i]) ? dfs(i + 1) : inf;  // 字符相同就能免费跳过一位；不同则先记为不可达
        Node* p = root;  // p 沿 source 的 Trie 路径下行
        Node* q = root;  // q 沿 target 的 Trie 路径下行
        for (int j = i; j < s.length(); ++j) {  // 枚举起止区间 [i, j] 作为一段整体转换
            p = p->children[s[j] - 'a'];  // 同步下行 source 的第 j 个字符
            q = q->children[t[j] - 'a'];  // 同步下行 target 的第 j 个字符
            if (p == nullptr || q == nullptr) {  // 任一边 Trie 走不下去，更长的段也不可能匹配
                break;  // 提前结束枚举
            }  // 提前退出分支结束
            if (p->v < 0 || q->v < 0) {  // 两边都必须落在某个规则串的结尾才有编号
                continue;  // 这段不是可整段转换的规则串，试更长的段
            }  // 跳过分支结束
            long long temp = g[p->v][q->v];  // 取出「source 这段 → target 这段」的最小成本
            if (temp < inf) {  // 可达时才值得尝试
                res = min(res, temp + dfs(j + 1));  // 整段转换成本 + 剩余部分的最优成本
            }  // 整段转换分支结束
        }  // 区间枚举结束
        return f[i] = res;  // 写入记忆化数组并返回
    }  // dfs 结束
};  // 类定义结束
