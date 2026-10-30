// 题目：651. 四个键的键盘（4 Keys Keyboard）
// 思路：动态规划。dp[i] 表示按 i 次键最多能得到的 A 数，枚举最后一次「全选 + 复制」发生的位置 j，之后所有按键都用于粘贴，故 dp[i] = max(dp[i], dp[j-1] × (i-j))。
// 时间复杂度：O(n^2)，两层循环；空间复杂度：O(n)，dp 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxA(int n) {  // n 是允许按下的按键次数，返回屏幕上最多能出现的 A 的个数
        vector<int> dp(n + 1);  // dp[i] 表示按 i 次键最多能得到多少个 A
        iota(dp.begin(), dp.end(), 0);  // 先填入基线：全程只按 A 键，i 次按键正好得到 i 个 A
        for (int i = 3; i < n + 1; ++i) {  // 从按 3 次键开始才可能用完「全选 + 复制 + 粘贴」
            for (int j = 2; j < i - 1; ++j) {  // 枚举最后一次全选复制的位置 j（后面至少要留一次粘贴）
                dp[i] = max(dp[i], dp[j - 1] * (i - j));  // j 处全选并复制，之后 i-j 次按键每次粘贴放大一倍
            }
        }
        return dp[n];  // 返回按 n 次键能得到的最大 A 数
    }
};