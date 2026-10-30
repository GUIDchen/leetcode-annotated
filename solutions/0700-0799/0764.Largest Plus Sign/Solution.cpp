// 题目：764. 最大加号标志（Largest Plus Sign）
// 思路：以每个格子为中心做四方向「连续可用长度」的 DP，一次双向扫描同时更新左右上下四个方向，再取所有中心的最小臂长最大值。
// 时间复杂度：O(n^2)，每个格子常数次更新；空间复杂度：O(n^2)，dp 矩阵。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {  // n 是边长，mines 是地雷坐标
        vector<vector<int>> dp(n, vector<int>(n, n));  // dp[i][j] 表示以 (i,j) 为臂长的候选上界，先全部填 n
        for (auto& e : mines) dp[e[0]][e[1]] = 0;  // 地雷格子臂长置 0，不能参与构成加号
        for (int i = 0; i < n; ++i) {  // 逐行、逐列作为中心线进行扫描
            int left = 0, right = 0, up = 0, down = 0;  // 四个方向上当前的连续可用长度
            for (int j = 0, k = n - 1; j < n; ++j, --k) {  // j 从左往右、k 从右往左，一次循环完成双向 DP
                left = dp[i][j] ? left + 1 : 0;  // 行内自左向右的连续长度，遇 0 清零
                right = dp[i][k] ? right + 1 : 0;  // 行内自右向左的连续长度
                up = dp[j][i] ? up + 1 : 0;  // 列内自上而下的连续长度
                down = dp[k][i] ? down + 1 : 0;  // 列内自下而上的连续长度
                dp[i][j] = min(dp[i][j], left);  // 用左臂长度收紧该中点的臂长
                dp[i][k] = min(dp[i][k], right);  // 用右臂长度收紧该中点的臂长
                dp[j][i] = min(dp[j][i], up);  // 用上臂长度收紧该中点的臂长
                dp[k][i] = min(dp[k][i], down);  // 用下臂长度收紧该中点的臂长
            }
        }
        int ans = 0;  // 记录最大的加号阶数
        for (auto& e : dp) ans = max(ans, *max_element(e.begin(), e.end()));  // 在所有格子的臂长中取最大值
        return ans;  // 返回最大加号标志的阶
    }
};  // 类定义结束（源文件末尾无换行）