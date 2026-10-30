// 3865. 反转 K 个子数组 / Reverse K Subarrays
// 核心思路：每段长度 m = n / k，以 m 为步长枚举 k 段的左端点，对每段用左右双指针从两端向中间交换，完成原地反转。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution {  // LeetCode 题解类
public:  // 公有成员
    vector<int> reverseSubarrays(vector<int>& nums, int k) {  // 把 nums 均分为 k 段并逐段反转
        int n = nums.size();  // 数组长度 n
        int m = n / k;  // 每段的长度（题目保证 n 能被 k 整除）
        for (int i = 0; i < n; i += m) {  // 以 m 为步长遍历每一段的左端点
            int l = i, r = i + m - 1;  // 当前段的左指针与右指针
            while (l < r) {  // 双指针未相遇时继续交换
                swap(nums[l++], nums[r--]);  // 交换两端元素，两指针同时向中间收缩
            }  // 当前段反转完毕
        }  // k 段全部处理完毕
        return nums;  // 返回反转后的数组
    }  // 方法结束
};  // 类结束
