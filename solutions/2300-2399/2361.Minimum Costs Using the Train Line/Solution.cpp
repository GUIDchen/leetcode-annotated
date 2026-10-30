// 题目：2361. 乘坐火车路线的最少费用（Minimum Costs Using the Train Line）
// 思路：线性 DP，用 f[i]、g[i] 分别表示到第 i 站时人在普通线 / 快线上的最小累计费用，逐站转移并取两者较小值作为答案。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(n)，两个 DP 数组加一个答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<long long> minimumCosts(vector<int>& regular, vector<int>& express, int expressCost) {  // regular、express：两趟车逐站票价；expressCost：换乘快线的额外费用
        int n = regular.size();  // n 为站数
        long long f[n + 1];  // f[i]：到达第 i 站后仍停留在普通线上的最小花费
        long long g[n + 1];  // g[i]：到达第 i 站后停留在快线上的最小花费
        f[0] = 0;  // 起点在普通线，尚未花钱
        g[0] = 1 << 30;  // 起点不可能位于快线，用很大的数表示该状态不可达
        vector<long long> cost(n);  // 依次保存到每一站的最少总费用
        for (int i = 1; i <= n; ++i) {  // 从第 1 站推到第 n 站
            int a = regular[i - 1];  // 第 i-1 站到第 i 站的普通线票价
            int b = express[i - 1];  // 第 i-1 站到第 i 站的快线票价
            f[i] = min(f[i - 1] + a, g[i - 1] + a);  // 无论上一站在哪条线，付普通票价 a 都能到达普通线，取较小者
            g[i] = min(f[i - 1] + expressCost + b, g[i - 1] + b);  // 从普通线换到快线要额外付 expressCost；已在快线则只付 b
            cost[i - 1] = min(f[i], g[i]);  // 两条线取较小值即为到达该站的最少费用
        }  // 逐站转移结束
        return cost;  // 返回每一站的最少费用列表
    }  // 方法结束
};  // 类定义结束