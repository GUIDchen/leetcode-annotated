// 题目：3332. 旅客可以得到的最多点数（Maximum Points Tourist Can Earn）
// 思路：按天做动态规划，f[i][j] 表示第 i 天结束停在第 j 个城市的最大得分；转移时枚举前一天城市 h，h == j 取 stayScore，否则取 travelScore。
// 时间复杂度：O(k·n^2)，三重循环；空间复杂度：O(k·n)，dp 表大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxScore(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore) {  // n 是城市数，k 是天数，两个得分表分别是停留与移动的收益
        int f[k + 1][n];  // f[i][j]：第 i 天结束停在第 j 个城市能取得的最大点数（变长数组）
        memset(f, 0xc0, sizeof(f));  // 0xc0 逐字节填充相当于置为很小的负数，表示尚未到达
        memset(f[0], 0, sizeof(f[0]));  // 第 0 天还没出发，任何城市的得分都是 0，作为递推起点
        for (int i = 1; i <= k; ++i) {  // 逐天递推
            for (int j = 0; j < n; ++j) {  // 枚举第 i 天结束时所在的城市 j
                for (int h = 0; h < n; ++h) {  // 枚举第 i-1 天所在的城市 h
                    f[i][j] = max(f[i][j], f[i - 1][h] + (j == h ? stayScore[i - 1][j] : travelScore[h][j]));  // h == j 表示留在原地拿 stayScore，否则从 h 移动到 j 拿 travelScore
                }  // h 枚举结束
            }  // j 枚举结束
        }  // 天数递推结束
        return *max_element(f[k], f[k] + n);  // 第 k 天可在任意城市收尾，取全局最大值
    }  // 方法结束
};  // 类定义结束
