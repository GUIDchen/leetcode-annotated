// 题目：3107. 使数组中位数等于 K 的最少操作数（Minimum Operations to Make Median of Array Equal to K）
// 思路：先排序，定位上中位数 m；把 nums[m] 调到 k，再向左扫掉所有大于 k 的元素、或向右扫掉所有小于 k 的元素，逐个补齐差值。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，只在原数组上原地排序（不计排序内部栈空间）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minOperationsToMakeMedianK(vector<int>& nums, int k) {  // nums：输入数组；k：目标中位数；返回最少操作数
        sort(nums.begin(), nums.end());  // 先排序，中位数才有确定的下标
        int n = nums.size();  // 数组长度
        int m = n >> 1;  // 上中位数下标，偶数个元素时取右侧那个
        long long ans = abs(nums[m] - k);  // 先把中位数本身调整到 k 所需的代价
        if (nums[m] > k) {  // 中位数偏大，左侧可能也有偏大的数需要一起下调
            for (int i = m - 1; i >= 0 && nums[i] > k; --i) {  // 从 m 向左扫，遇到不大于 k 的就停
                ans += nums[i] - k;  // 这个大于 k 的元素必须降到 k
            }
        } else {  // 中位数偏小，右侧可能也有偏小的数需要一起上调
            for (int i = m + 1; i < n && nums[i] < k; ++i) {  // 从 m 向右扫，遇到不小于 k 的就停
                ans += k - nums[i];  // 这个小于 k 的元素必须升到 k
            }
        }
        return ans;  // 返回最少操作次数
    }
};