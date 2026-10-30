// 题目：1877. 数组中最大数对和的最小值（Minimize Maximum Pair Sum in Array）
// 思路：先升序排序，再让最小元素配最大元素（贪心：一大一小配对才能把每对和压平），所有配对和中取最大值即为答案。
// 时间复杂度：O(n log n)，由排序决定；空间复杂度：O(log n)，排序所需的递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minPairSum(vector<int>& nums) {  // nums：长度为偶数的整数数组；返回所有配对方案中最小的「最大数对和」
        ranges::sort(nums);  // 升序排序，便于让最小值与最大值两两配对（C++20 的 std::ranges::sort）
        int ans = 0, n = nums.size();  // ans：目前见过的最大数对和；n：数组长度
        for (int i = 0; i < n >> 1; ++i) {  // 只枚举前一半下标（n >> 1 即 n / 2），每一轮处理一对
            ans = max(ans, nums[i] + nums[n - i - 1]);  // 当前最小值 nums[i] 配当前最大值 nums[n-i-1]，维护配对和的最大值
        }  // 一半的配对全部处理完
        return ans;  // 返回最小的最大数对和
    }  // 方法结束
};  // 类定义结束
