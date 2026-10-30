// 3693. Climbing Stairs II（3693. 爬楼梯 II）
// 核心思路：用 f[i] 表示到达第 i 级台阶的最小花费；因为每次最多跳 3 级，所以 f[i] = min(f[i-j] + costs[i-1] + j²)，j = 1..3，跳跃距离的平方作为额外代价。
// 复杂度：时间 O(3n) 即 O(n)，空间 O(n)。
class Solution {  // 定义题解类
public:  // 公有接口
    int climbStairs(int n, vector<int>& costs) {  // 主函数：返回到达第 n 级台阶的最小总花费
        vector<int> f(n + 1, INT_MAX / 2);  // f[i] 表示到达第 i 级的最小花费，初始化为极大值（取 INT_MAX/2 防止加法溢出）
        f[0] = 0;  // 起点在地面，花费为 0
        for (int i = 1; i <= n; ++i) {  // 逐级递推
            int x = costs[i - 1];  // 踩上第 i 级需要支付 costs[i-1]
            for (int j = max(0, i - 3); j < i; ++j) {  // 枚举上一次所在的台阶 j，只能往前跳 1~3 级
                f[i] = min(f[i], f[j] + x + (i - j) * (i - j));  // 转移：上一级花费 + 本级花费 + 跳跃距离的平方
            }  // 内层循环结束
        }  // 外层循环结束
        return f[n];  // 返回到达第 n 级的最小花费
    }  // 主函数结束
};  // 类定义结束
