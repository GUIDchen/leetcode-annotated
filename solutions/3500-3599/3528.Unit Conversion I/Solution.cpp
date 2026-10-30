// 题目：3528. 单位转换 I（Unit Conversion I）
// 思路：把 conversions 看成以 0 号单位为根的有向树，从 0 DFS，把沿途的换算系数连乘（对 1e9+7 取模）即得每个单位折算成 0 号单位的系数。
// 时间复杂度：O(n)，n 为单位个数，每个单位只访问一次；空间复杂度：O(n)，邻接表与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 判题器只调用 public 区的方法
    vector<int> baseUnitConversions(vector<vector<int>>& conversions) {  // conversions[i] = [源单位, 目标单位, 换算系数]
        const int mod = 1e9 + 7;  // 题目要求的取模值
        int n = conversions.size() + 1;  // 单位个数 = 换算关系数 + 1
        vector<vector<pair<int, int>>> g(n);  // 邻接表：g[u] 存 (目标单位, 换算系数)
        vector<int> ans(n);  // ans[u] 表示 1 个 u 单位折合多少个 0 号单位
        for (const auto& e : conversions) {  // 逐条建立有向边
            g[e[0]].push_back({e[1], e[2]});  // 源单位指向目标单位，边权为换算系数
        }  // 建图结束
        auto dfs = [&](this auto&& dfs, int s, long long mul) -> void {  // 自引用 lambda：从 s 出发，mul 为到 s 为止的累计系数
            ans[s] = mul;  // 到达 s 时的累计系数就是它折合 0 号单位的系数
            for (auto [t, w] : g[s]) {  // 枚举 s 的所有后继单位
                dfs(t, mul * w % mod);  // 系数连乘并取模后继续深搜
            }  // 后继遍历结束
        };  // lambda 定义结束
        dfs(0, 1);  // 从 0 号单位出发，系数为 1
        return ans;  // 返回每个单位折算成 0 号单位的系数
    }  // 方法结束
};  // 类定义结束
