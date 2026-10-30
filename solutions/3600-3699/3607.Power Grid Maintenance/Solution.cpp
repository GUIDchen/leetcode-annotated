// 3607. 电网维护 / Power Grid Maintenance
// 核心思路：用并查集把线缆相连的电站合并成连通块，并为每个连通块维护一个有序集合；类型 1 查询取该电站（若已离线则取块内在线的编号最小者），类型 2 查询把电站从集合中删除。
// 复杂度：时间 O((c + e + q)·α(c) + q log c)，空间 O(c)；c 为电站数、e 为线路数、q 为查询数。
class UnionFind {  // 并查集：维护连通块与按大小合并
public:  // 公有接口部分
    UnionFind(int n) {  // 构造函数：n 个电站各自独立成块
        p = vector<int>(n);  // 父节点数组
        size = vector<int>(n, 1);  // 块大小数组，初始每个块只有自己
        iota(p.begin(), p.end(), 0);  // 把父节点初始化成自身下标
    }  // 构造函数结束

    bool unite(int a, int b) {  // 合并两个电站所在的连通块
        int pa = find(a), pb = find(b);  // 先分别找到两个块的根
        if (pa == pb) {  // 本来就在同一块里，无需合并
            return false;  // 返回合并失败
        }  // 分支结束
        if (size[pa] > size[pb]) {  // 把较小的块挂到较大的块下面
            p[pb] = pa;  // 小编号块指向大编号块
            size[pa] += size[pb];  // 合并后更新大块的规模
        } else {  // 否则反过来挂
            p[pa] = pb;  // 大编号块指向小编号块
            size[pb] += size[pa];  // 合并后更新大块的规模
        }  // 分支结束
        return true;  // 返回合并成功
    }  // 合并函数结束

    int find(int x) {  // 查找所在连通块的根，并做路径压缩
        if (p[x] != x) {  // 当前节点不是根
            p[x] = find(p[x]);  // 递归找根并把沿途节点直接挂到根上
        }  // 条件分支结束
        return p[x];  // 返回根编号
    }  // 查找函数结束

private:  // 私有数据部分
    vector<int> p, size;  // 父节点数组与块大小数组
};  // 并查集类定义结束

class Solution {  // 题解类
public:  // 公有接口部分
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {  // 主函数：c 为电站数，connections 为线路，queries 为查询序列
        UnionFind uf(c + 1);  // 电站编号从 1 开始，因此开 c+1 大小
        for (auto& e : connections) {  // 把每条线路连接的两个电站合并
            uf.unite(e[0], e[1]);  // 合并该线路的两端
        }  // 遍历结束

        vector<set<int>> st(c + 1);  // 为每个连通块准备一个有序集合，存块内在线的电站编号
        for (int i = 1; i <= c; i++) {  // 电站编号从 1 到 c
            st[uf.find(i)].insert(i);  // 把电站放进它所属连通块的集合里
        }  // 遍历结束

        vector<int> ans;  // 按顺序收集每次查询的答案
        for (auto& q : queries) {  // 逐条处理查询
            int a = q[0], x = q[1];  // 拆出查询类型 a 与目标电站 x
            int root = uf.find(x);  // 找到该电站当前所在连通块的根
            if (a == 1) {  // 类型 1：查询维护时应输出的电站编号
                if (st[root].count(x)) {  // 该电站本身仍在线
                    ans.push_back(x);  // 直接输出它自己
                } else if (!st[root].empty()) {  // 否则若块内还有在线电站
                    ans.push_back(*st[root].begin());  // 输出块内在线的编号最小的电站
                } else {  // 否则块内已无在线电站
                    ans.push_back(-1);  // 输出 -1 表示无可用电站
                }  // 分支结束
            } else {  // 类型 2：该电站离线维护
                st[root].erase(x);  // 把它从所属连通块的有序集合中删除
            }  // 分支结束
        }  // 遍历结束
        return ans;  // 返回所有类型 1 查询的答案
    }  // 主函数结束
};  // 类定义结束
