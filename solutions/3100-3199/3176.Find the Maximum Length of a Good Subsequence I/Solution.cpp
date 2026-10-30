// 题目：3176. 求出最长好子序列 I（Find the Maximum Length of a Good Subsequence I）
// 思路：动态规划，f[i][h] 表示以 nums[i] 结尾、相邻不相等次数不超过 h 的最长好子序列长度，枚举前驱 j 转移。
// 时间复杂度：O(n^2 k)，n 为数组长度；空间复杂度：O(n k)，即状态表 f 的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumLength(vector<int>& nums, int k) {  // nums：输入数组；k：允许的相邻不相等次数上限
        int n = nums.size();  // 记录数组长度，后面循环与建表都要用
        int f[n][k + 1];  // 状态表：f[i][h] 表示以 i 结尾、坏对数不超过 h 的最长长度
        memset(f, 0, sizeof(f));  // 全部置 0，作为「尚未拼接前驱」的初始状态
        int ans = 0;  // 记录全局最优答案
        for (int i = 0; i < n; ++i) {  // 枚举子序列的最后一个位置 i
            for (int h = 0; h <= k; ++h) {  // 枚举已使用的相邻不相等次数上限 h
                for (int j = 0; j < i; ++j) {  // 枚举前驱位置 j，尝试把 nums[i] 接在 nums[j] 之后
                    if (nums[i] == nums[j]) {  // 相邻元素相等，不消耗坏对额度
                        f[i][h] = max(f[i][h], f[j][h]);  // 直接继承 j 处相同额度 h 的最优长度
                    } else if (h) {  // 相邻元素不相等，需要消耗一次坏对额度，且额度必须还有剩余
                        f[i][h] = max(f[i][h], f[j][h - 1]);  // 从 j 处额度 h-1 的状态转移过来
                    }
                }
                ++f[i][h];  // 无论有无前驱，都要把 nums[i] 本身计入长度
            }
            ans = max(ans, f[i][k]);  // 用「额度恰好用到上限 k」的状态更新答案
        }
        return ans;  // 返回最长好子序列的长度
    }
};