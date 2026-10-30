// 题目：1671. 得到山形数组的最少删除次数（Minimum Number of Removals to Make Mountain Array）
// 思路：分别求以每个位置结尾的最长严格递增子序列长度 left、以每个位置开头的最长严格递减子序列长度 right，再枚举峰顶取 left+right-1 的最大值。
// 时间复杂度：O(n²)，两重循环求两个 LIS；空间复杂度：O(n)，left 与 right 两个数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumMountainRemovals(vector<int>& nums) {  // 求最少删除次数，使剩余数组成为山形数组
        int n = nums.size();  // 数组长度
        vector<int> left(n, 1), right(n, 1);  // left[i] 是以 i 结尾的最长递增子序列长度，right[i] 是以 i 开头的最长递减子序列长度
        for (int i = 1; i < n; ++i) {  // 正序遍历，自左向右递推 left
            for (int j = 0; j < i; ++j) {  // 枚举 i 之前的所有位置 j
                if (nums[i] > nums[j]) {  // nums[i] 能接在 nums[j] 后面继续上升
                    left[i] = max(left[i], left[j] + 1);  // 用 j 的最优解加 1 更新 left[i]
                }  // if 分支结束
            }  // 内层循环结束
        }  // 外层循环结束
        for (int i = n - 2; i >= 0; --i) {  // 逆序遍历，自右向左递推 right
            for (int j = i + 1; j < n; ++j) {  // 枚举 i 之后的所有位置 j
                if (nums[i] > nums[j]) {  // nums[i] 能接在 nums[j] 前面继续下降
                    right[i] = max(right[i], right[j] + 1);  // 用 j 的最优解加 1 更新 right[i]
                }  // if 分支结束
            }  // 内层循环结束
        }  // 外层循环结束
        int ans = 0;  // 记录最长山形子序列的长度
        for (int i = 0; i < n; ++i) {  // 枚举山峰位置 i
            if (left[i] > 1 && right[i] > 1) {  // 峰顶左右都至少有一个元素，才是合法山形
                ans = max(ans, left[i] + right[i] - 1);  // 峰顶被左右两段各算一次，所以减 1
            }  // if 分支结束
        }  // 枚举结束
        return n - ans;  // 总长度减去最长山形子序列长度，就是最少删除次数
    }  // 方法结束
};  // 类定义结束