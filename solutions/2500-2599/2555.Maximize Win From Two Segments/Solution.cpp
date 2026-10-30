// 题目：2555. 两个线段获得的最多奖品（Maximize Win From Two Segments）
// 思路：DP + 二分。f[i] 表示只在前 i 个奖品中放一条线段能覆盖的最多奖品数；枚举第二条线段的右端点 i，二分出它最左能覆盖到的 j，答案是 f[j] + (i - j)。
// 时间复杂度：O(n log n)，每个 i 做一次二分；空间复杂度：O(n)，f 数组保存前缀最优。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximizeWin(vector<int>& prizePositions, int k) {  // prizePositions 是递增的奖品坐标，k 是每条线段的长度
        int n = prizePositions.size();  // n 是奖品个数
        vector<int> f(n + 1);  // f[i] 表示只在前 i 个奖品里放一条线段时能覆盖的最多奖品数
        int ans = 0;  // ans 记录两条线段一起最多能覆盖多少奖品
        for (int i = 1; i <= n; ++i) {  // i 是右端点（1 基），枚举第二条线段的右端
            int x = prizePositions[i - 1];  // 取出第 i 个奖品的坐标（换成 0 基下标）
            int j = lower_bound(prizePositions.begin(), prizePositions.end(), x - k) - prizePositions.begin();  // 二分找第一个坐标 >= x - k 的位置 j，则 [j, i) 这些奖品能被一条长 k 的线段覆盖
            ans = max(ans, f[j] + i - j);  // 前 j 个奖品里放第一条线段，[j, i) 放第二条，两者不重叠
            f[i] = max(f[i - 1], i - j);  // 更新前缀最优：要么不用第 i 个奖品，要么用覆盖 i - j 个奖品的这条线段
        }  // 枚举结束
        return ans;  // 返回最多能拿到的奖品数
    }  // maximizeWin 方法结束
};  // Solution 类定义结束