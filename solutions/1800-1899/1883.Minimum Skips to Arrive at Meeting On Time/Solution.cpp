// 题目：1883. 准时抵达会议现场的最小跳过休息次数（Minimum Skips to Arrive at Meeting On Time）
// 思路：动态规划，f[i][j] 表示走完前 i 段、跳过 j 次等待时的最小耗时；每段在「向上取整等待整点」与「跳过等待」之间转移取最小。
// 时间复杂度：O(n^2)，两层循环各 n 次；空间复杂度：O(n^2)，二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minSkips(vector<int>& dist, int speed, int hoursBefore) {  // dist 是各段距离，speed 是速度，hoursBefore 是剩余时限（小时）
        int n = dist.size();  // 路段数量，也是 DP 规模
        vector<vector<double>> f(n + 1, vector<double>(n + 1, 1e20));  // DP 表初始化为 1e20，表示该状态不可达
        f[0][0] = 0;  // 边界：一段都没走、跳过 0 次，耗时为 0
        double eps = 1e-8;  // 浮点误差容限，避免向上取整把整数误加一
        for (int i = 1; i <= n; ++i) {  // 枚举已经走过前 i 段
            for (int j = 0; j <= i; ++j) {  // 枚举跳过的次数，最多不超过已走的段数
                if (j < i) {  // 本次不跳过：必须等到整点才能进入下一段
                    f[i][j] = min(f[i][j], ceil(f[i - 1][j] + dist[i - 1] * 1.0 / speed - eps));  // 先减 eps 再向上取整，模拟整点等待
                }
                if (j) {  // 本次跳过休息：上一状态只跳了 j - 1 次
                    f[i][j] = min(f[i][j], f[i - 1][j - 1] + dist[i - 1] * 1.0 / speed);  // 直接累加耗时，不做取整
                }
            }
        }
        for (int j = 0; j <= n; ++j) {  // 从少到多枚举跳过次数，找最小的可行解
            if (f[n][j] <= hoursBefore + eps) {  // 加 eps 抵消误差后判断能否准时抵达
                return j;  // 第一个满足条件的 j 就是答案
            }
        }
        return -1;  // 无论怎么跳过都赶不上，返回 -1
    }
};