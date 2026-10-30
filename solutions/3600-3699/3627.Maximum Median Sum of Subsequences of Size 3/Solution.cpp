// 3627. Maximum Median Sum of Subsequences of Size 3（3627. 中位数之和的最大值）
// 核心思路：排序后把最小的 n/3 个数留作各三元组的最小值，剩余的 2n/3 个数两两成组，每组中位数取其中较大者，即从下标 n/3 起每隔 2 取一个累加。
// 复杂度：时间 O(n log n)（排序），空间 O(1)（不计排序内部开销）。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    long long maximumMedianSum(vector<int>& nums) {  // 求所有三元组中位数之和的最大值
        ranges::sort(nums);  // 升序排序，便于贪心分组
        int n = nums.size();  // 数组长度
        long long ans = 0;  // 累加中位数
        for (int i = n / 3; i < n; i += 2) {  // 从 n/3 起每隔 2 取一个作为中位数
            ans += nums[i];  // 累加当前中位数
        }
        return ans;  // 返回最大中位数之和
    }
};