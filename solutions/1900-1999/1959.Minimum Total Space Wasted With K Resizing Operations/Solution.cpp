// 题目：1959. K 次调整数组大小浪费的最小总空间（Minimum Total Space Wasted With K Resizing Operations）
// 思路：至多 k 次调整相当于把数组切成至多 k+1 段、每段共用一个容量（段内最大值）；预处理任意区间作为一段的浪费 g[i][j]，再做「前 i 个元素分 j 段」的区间 DP。
// 时间复杂度：O(n^2·k)，三层循环；空间复杂度：O(n^2 + n·k)，分别保存区间浪费与 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minSpaceWastedKResizing(vector<int>& nums, int k) {  // nums 是各阶段需要的元素个数，k 是允许调整大小的次数（可以少于 k 次）
        ++k;  // k 次调整把数组分成至多 k+1 段，段内使用同一个容量
        int n = nums.size();  // 元素个数
        vector<vector<int>> g(n, vector<int>(n));  // g[i][j]：把 nums[i..j] 当成一段（共用一个容量）时的浪费空间
        for (int i = 0; i < n; ++i) {  // 枚举每一段的左端点
            int s = 0, mx = 0;  // s 是段内元素和，mx 是段内最大值（也就是该段需要的最小容量）
            for (int j = i; j < n; ++j) {  // 枚举右端点，逐渐把这一段向右扩展
                mx = max(mx, nums[j]);  // 边扩展边维护最大值，保证容量不小于段内任何元素
                s += nums[j];  // 累加元素和，用于计算未使用的空间
                g[i][j] = mx * (j - i + 1) - s;  // 分配空间 mx*(j-i+1) 减去实际占用 s，即为浪费
            }
        }
        int inf = 0x3f3f3f3f;  // 足够大的哨兵值，充当「无穷大」
        vector<vector<int>> f(n + 1, vector<int>(k + 1, inf));  // f[i][j]：前 i 个元素分成 j 段时的最小浪费总和
        f[0][0] = 0;  // 边界：没有元素、没有段，浪费为 0
        for (int i = 1; i <= n; ++i) {  // 逐渐扩大已处理的前缀长度
            for (int j = 1; j <= k; ++j) {  // 枚举当前使用到的段数
                for (int h = 0; h < i; ++h) {  // 枚举最后一段的起点 h，即把 [h, i) 作为第 j 段
                    f[i][j] = min(f[i][j], f[h][j - 1] + g[h][i - 1]);  // 用「前 h 个元素分 j-1 段」加上最后一段的浪费来松弛当前状态
                }
            }
        }
        return f[n][k];  // 前 n 个元素分成至多 k+1 段的最小浪费即答案
    }
};