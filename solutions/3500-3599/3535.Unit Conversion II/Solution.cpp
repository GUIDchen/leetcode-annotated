// 3535. 单位转换 II / Unit Conversion II
// 核心思路：以单位 0 为根，DFS 求出 0 到每个单位的累计倍率 res；任意 x→y 的倍率即 res[y] / res[x]，用费马小定理求模逆元。
// 复杂度：时间 O(n + q log MOD)，空间 O(n)。
class Solution {  // 定义题解类
public:  // 公有方法区
    vector<int> queryConversions(vector<vector<int>>& conversions, vector<vector<int>>& queries) {  // 回答：每个查询 (x, y) 的换算倍率，对 1e9+7 取模
        const int mod = 1e9 + 7;  // 取模常数
        int n = conversions.size() + 1;  // 节点数 = 边数 + 1
        vector<vector<pair<int, int>>> g(n);  // 邻接表：g[s] 存 (目标单位, 倍率)
        for (auto& e : conversions) {  // 根据转换关系建图
            g[e[0]].emplace_back(e[1], e[2]);  // 从 e[0] 到 e[1] 的倍率为 e[2]
        }  // 循环结束

        vector<int> res(n);  // res[i]：从单位 0 到单位 i 的累计倍率

        auto dfs = [&](this auto&& dfs, int s, long long mul) -> void {  // 递归 DFS：mul 为从 0 到 s 的累计倍率
            res[s] = mul;  // 记录 0 到 s 的倍率
            for (auto [t, w] : g[s]) {  // 遍历 s 的所有出边
                dfs(t, mul * w % mod);  // 递归孩子，倍率相乘并取模
            }  // 循环结束
        };  // lambda 定义结束
        dfs(0, 1);  // 从单位 0 出发，初始倍率为 1

        auto qpow = [&](long long x, int n) {  // 快速幂，用于求模逆元
            long long res = 1;  // 结果初值为 1
            while (n) {  // 指数不为 0 时继续
                if (n & 1) {  // 当前二进制位为 1
                    res = res * x % mod;  // 把 x 的这一份幂乘进结果
                }  // if 语句结束
                x = x * x % mod;  // 底数平方
                n >>= 1;  // 指数右移一位
            }  // while 循环结束
            return res;  // 返回 x^n mod mod
        };  // lambda 定义结束

        vector<int> ans;  // 存放每个查询的答案
        for (auto& q : queries) {  // 逐个处理查询
            ans.push_back(res[q[1]] * qpow(res[q[0]], mod - 2) % mod);  // res[y] / res[x] 用乘逆元实现
        }  // 循环结束
        return ans;  // 返回全部答案
    }  // 方法结束
};  // 类定义结束
