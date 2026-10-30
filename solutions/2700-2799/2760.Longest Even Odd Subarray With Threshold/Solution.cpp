// 题目：2760. 最长奇偶子数组（Longest Even Odd Subarray With Threshold）
// 思路：枚举左端点，只在 nums[l] 是偶数且不超过 threshold 时向右扩展；扩展条件是与前一个元素奇偶性不同且值不超过 threshold，用 r - l 更新答案。
// 时间复杂度：O(n^2)，最坏情况每个左端点都要向右扫一遍；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestAlternatingSubarray(vector<int>& nums, int threshold) {  // nums：输入数组；threshold：子数组元素允许的最大值
        int ans = 0, n = nums.size();  // ans 记录最长长度，n 是数组长度
        for (int l = 0; l < n; ++l) {  // 枚举子数组的左端点 l
            if (nums[l] % 2 == 0 && nums[l] <= threshold) {  // 合法子数组必须从偶数开始，而且这个偶数不能超过 threshold
                int r = l + 1;  // 右端点从 l + 1 开始试探，因为 l 本身已经是一个合法子数组
                while (r < n && nums[r] % 2 != nums[r - 1] % 2 && nums[r] <= threshold) {  // 向右多看一个元素：下标不越界、奇偶性必须交替、值不能超过 threshold
                    ++r;  // 三个条件都满足，右端点右移一位
                }  // 扩展结束，[l, r - 1] 就是以 l 开头的最长奇偶交替子数组
                ans = max(ans, r - l);  // r - l 是这段子数组的长度，用它更新答案
            }  // 换成下一个左端点试试
        }  // 所有左端点都枚举完了
        return ans;  // 返回最长长度，没有合法子数组时保持 0
    }  // 方法结束
};  // 类定义结束