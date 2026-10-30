// 题目：818. 赛车（Race Car）
// 思路：动态规划，dp[i] 表示到达位置 i 的最少指令数。i 恰为 2^k-1 时答案就是 k；否则要么冲过头再折返，要么先到 2^(k-1)-1 再反向、前进、反向，枚举后取最小。
// 时间复杂度：O(target·log target)，内层至多循环 log target 次；空间复杂度：O(target)，dp 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int racecar(int target) {  // target：要到达的目标位置（从 0 出发）
        vector<int> dp(target + 1);  // dp[i]：到达位置 i 所需的最少指令条数
        for (int i = 1; i <= target; ++i) {  // 从小到大依次求解每个位置（i=0 时 0 条指令）
            int k = 32 - __builtin_clz(i);  // k 为 i 的二进制位数（__builtin_clz 统计前导零个数），代表需要连续加速几次的量级
            if (i == (1 << k) - 1) {  // i 恰好是 2^k-1：连续 k 次 A 刚好停在 i
                dp[i] = k;  // 因此只需要 k 条指令
                continue;  // 已是最优，跳过其余转移
            }  // if 结束
            dp[i] = dp[(1 << k) - 1 - i] + k + 1;  // 方案一：先冲过头到 2^k-1，再执行一次 R 反向，从对称位置转移过来
            for (int j = 0; j < k; ++j) {  // 方案二：枚举掉头前/后走到的位置，尝试更优解
                dp[i] = min(dp[i], dp[i - (1 << (k - 1)) + (1 << j)] + k - 1 + j + 2);  // 转移：先走 k-1 步 A 到 2^(k-1)-1，再 R 掉头，接着 A 走 j 步，再 R 掉头，总指令数为 k-1+j+2
            }  // 内层枚举结束
        }  // 外层递推结束
        return dp[target];  // 返回到达 target 的最少指令数
    }  // racecar 方法结束
};  // Solution 类结束