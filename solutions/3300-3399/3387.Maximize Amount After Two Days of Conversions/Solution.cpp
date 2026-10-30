// 题目：3387. 两天自由外汇交易后的最大货币数（Maximize Amount After Two Days of Conversions）
// 思路：分别把两天的汇率建成无向图，DFS 求出「初始货币 → 每种货币」的换算倍数 d1、d2；答案是 max(d1[c] / d2[c])，等价于第一天换出去、第二天再换回来。
// 时间复杂度：O(V + E)，每个货币节点只访问一次；空间复杂度：O(V + E)，存两张货币图与两张换算表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {  // initialCurrency：初始货币；pairs1/rates1 是第一天汇率；pairs2/rates2 是第二天汇率
        unordered_map<string, double> d1 = build(pairs1, rates1, initialCurrency);  // 第一天：初始货币换成各货币的倍数表
        unordered_map<string, double> d2 = build(pairs2, rates2, initialCurrency);  // 第二天：初始货币换成各货币的倍数表
        double ans = 0;  // ans：两天后能得到的最大货币数
        for (const auto& [currency, rate] : d2) {  // 枚举第二天能换到的每种货币
            if (d1.find(currency) != d1.end()) {  // 该货币第一天也能换到，才可能「第一天换出去、第二天换回来」
                ans = max(ans, d1[currency] / rate);  // 先按第一天换出（乘以 d1），再按第二天汇率换回初始货币（除以 rate）
            }
        }
        return ans;  // 返回最大货币数
    }

private:  // 以下为内部辅助函数
    unordered_map<string, double> build(vector<vector<string>>& pairs, vector<double>& rates, const string& init) {  // 建图并求出 init 到每种货币的换算倍数表
        unordered_map<string, vector<pair<string, double>>> g;  // 邻接表：g[a] 保存 (能换成的货币, 汇率)
        unordered_map<string, double> d;  // d[c]：init 换成货币 c 的倍数
        for (int i = 0; i < pairs.size(); ++i) {  // 枚举每个汇率对
            const string& a = pairs[i][0];  // 汇率对的第一种货币
            const string& b = pairs[i][1];  // 汇率对的第二种货币
            double r = rates[i];  // 1 单位 a 可以换 r 单位 b
            g[a].push_back({b, r});  // 正向边 a -> b，汇率 r
            g[b].push_back({a, 1 / r});  // 反向边 b -> a，汇率为倒数
        }

        auto dfs = [&](this auto&& dfs, const string& a, double v) -> void {  // C++23 的递归 lambda：dfs(当前货币, 已累计的换算倍数)
            if (d.find(a) != d.end()) {  // 该货币已经算过就不再重复（同时也处理了环）
                return;  // 直接返回，避免在环上无限递归
            }

            d[a] = v;  // 记录 init 换成 a 的倍数
            for (const auto& [b, r] : g[a]) {  // 枚举 a 的所有邻居
                if (d.find(b) == d.end()) {  // 邻居还没被算过
                    dfs(b, v * r);  // 递归传递累计倍数 v * r
                }
            }
        };  // lambda 定义结束
        dfs(init, 1.0);  // 从初始货币出发，初始倍数为 1
        return d;  // 返回整张换算表
    }
};  // 题解类定义结束
