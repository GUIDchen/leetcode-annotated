// 题目：1916. 统计为蚁群构筑房间的不同顺序（Count Ways to Build Rooms in an Ant Colony）
// 思路：把前驱关系看成以 0 为根的树，自底向上后序遍历；合并兄弟子树时，把 cn 个节点插入已合并的 merged 个节点序列，乘上组合数 C(merged+cn, cn)；阶乘与逆元预处理后 O(1) 求组合数。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，存树、阶乘表与逆元表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int waysToBuildRooms(vector<int>& prevRoom) {  // prevRoom[i] 是房间 i 的前驱房间（房间 0 无前驱），返回合法的建造顺序数
        int n = prevRoom.size();  // n 为房间总数
        g.assign(n, {});  // 邻接表 g[u] 存放 u 的所有子房间，先把 n 个空列表准备好
        for (int i = 1; i < n; ++i) {  // 房间 0 是根，从 1 号开始逐个挂到前驱下面
            g[prevRoom[i]].push_back(i);  // 前驱必须先建好，因此 i 是 prevRoom[i] 的子节点
        }  // 结束建树
        fact.assign(n + 1, 1);  // fact[i] 预留给 i!，先全部置 1
        invFact.assign(n + 1, 1);  // invFact[i] 预留给 i! 的模逆元，同样先置 1
        for (int i = 1; i <= n; ++i) {  // 线性递推求 0! 到 n!
            fact[i] = fact[i - 1] * i % MOD;  // 阶乘递推：i! = (i-1)! * i，边乘边取模
        }  // 结束阶乘预处理
        invFact[n] = qpow(fact[n], MOD - 2);  // 费马小定理：n! 在模 MOD 下的逆元等于 (n!)^(MOD-2)
        for (int i = n; i > 0; --i) {  // 倒序递推所有阶乘的逆元，避免每项都做一次快速幂
            invFact[i - 1] = invFact[i] * i % MOD;  // (i-1)! 的逆元 = i! 的逆元 * i
        }  // 结束逆元预处理
        ans = 1;  // 答案初始化为 1（乘法的单位元）
        dfs(0);  // 从根房间出发后序遍历，沿途把各子树的方案数乘进 ans
        return ans;  // 返回总方案数
    }  // 结束方法

private:  // 以下是内部实现细节
    static constexpr int MOD = 1e9 + 7;  // 答案取模的大质数
    vector<vector<int>> g;  // 树用邻接表存储：g[u] 是 u 的所有子房间
    vector<long long> fact, invFact;  // 阶乘表与阶乘逆元表，用 long long 防止中间乘法溢出
    int ans;  // 累计的方案数（类成员，便于 dfs 中直接修改）

    int dfs(int u) {  // 返回以 u 为根的子树节点数，同时把该子树的顺序方案数乘进 ans
        int merged = 0;  // merged 记录已经合并过的兄弟子树节点总数
        for (int v : g[u]) {  // 依次处理每个子房间
            int cn = dfs(v);  // 递归得到子树节点数，同时该子树内部的顺序方案数已在递归中计入 ans
            if (merged) {  // 第一棵子树无需交错；已有节点时才需要乘组合数
                ans = 1LL * ans * comb(merged + cn, cn) % MOD;  // 把 cn 个新节点插入 merged 个已有节点的序列，方案数为 C(merged+cn, cn)
            }  // 结束条件分支
            merged += cn;  // 更新已合并的节点总数
        }  // 结束子节点遍历
        return merged + 1;  // 加上 u 自己，返回整棵子树的节点数
    }  // 结束 dfs

    long long comb(int n, int k) {  // 借助预处理好的阶乘表 O(1) 求组合数 C(n, k)
        return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;  // C(n,k) = n! * (k!)^-1 * ((n-k)!)^-1，每一步都取模防止溢出
    }  // 结束 comb

    long long qpow(long long a, long long n) {  // 快速幂：求 a^n mod MOD
        long long res = 1;  // 结果初始为 1
        for (; n; n >>= 1) {  // 指数每次右移一位（相当于除以 2）
            if (n & 1) {  // 当前二进制最低位为 1，说明这一份幂要乘进结果
                res = res * a % MOD;  // 把 a^(2^k) 累乘到结果中
            }  // 结束按位判断
            a = a * a % MOD;  // 底数自乘，为下一位准备 a^(2^(k+1))
        }  // 结束快速幂循环
        return res;  // 返回 a^n mod MOD
    }  // 结束 qpow
};  // 类定义结束
