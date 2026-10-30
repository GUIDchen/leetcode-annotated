// 3689. Maximum Total Subarray Value I（3689. 最大子数组总值 I）
// 核心思路：子数组的值等于最大值减最小值，取 k 份时的最大总和就是 k 乘以全局最大值与全局最小值之差。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 题解类
public:  // 公有接口，供判题器调用
    long long maxTotalValue(vector<int>& nums, int k) {  // 返回 k 个子数组值的最大总和
        auto [mn, mx] = minmax_element(nums.begin(), nums.end());  // 同时取到最小值和最大值的迭代器
        return 1LL * k * (*mx - *mn);  // 每个子数组都能取到全局极差，乘 k 即可，用 1LL 防止溢出
    }
};
