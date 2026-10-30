// 题目：1335. 工作计划的最低难度（Minimum Difficulty of a Job Schedule）
// 思路：区间划分型 DP。f[i][j] 表示把前 i 个任务按顺序分成 j 天的最小总难度；枚举最后一天的起点 k，该天难度为 jobDifficulty[k..i-1] 的最大值，转移 f[i][j] = min(f[k-1][j-1] + 区间最大值)。
// 时间复杂度：O(n^2 * d)，枚举 i、j、k 三层；空间复杂度：O(n * d)，DP 表大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDifficulty(vector<int>& jobDifficulty, int d) {  // jobDifficulty 是每天任务难度（必须按顺序做），d 是计划天数
        int n = jobDifficulty.size();  // 任务数量
        int f[n + 1][d + 1];  // f[i][j]：把前 i 个任务分成 j 天完成的最小难度和
        memset(f, 0x3f, sizeof(f));  // 初始化为 0x3f3f3f3f（视为无穷大），表示暂时不可行
        f[0][0] = 0;  // 边界：0 个任务分 0 天，总难度为 0
        for (int i = 1; i <= n; ++i) {  // 枚举任务前缀长度 i
            for (int j = 1; j <= min(d, i); ++j) {  // 枚举天数 j，最多 min(d, i) 天，因为每天至少要有一个任务
                int mx = 0;  // 记录最后一天（第 k..i 个任务）的最大难度
                for (int k = i; k; --k) {  // 倒序枚举最后一天的起点 k，边扩展边维护区间最大值
                    mx = max(mx, jobDifficulty[k - 1]);  // 把第 k 个任务并入最后一天，更新该天的最大难度
                    f[i][j] = min(f[i][j], f[k - 1][j - 1] + mx);  // 转移：前 k-1 个任务分 j-1 天的最优值 + 最后一天的最大难度
                }  // 起点枚举结束
            }  // 天数枚举结束
        }  // 任务前缀枚举结束
        return f[n][d] == 0x3f3f3f3f ? -1 : f[n][d];  // 仍为无穷大说明无法划分（如天数多于任务数），返回 -1
    }  // 方法结束
};  // 类定义结束