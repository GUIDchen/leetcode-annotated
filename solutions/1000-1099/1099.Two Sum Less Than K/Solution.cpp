// 题目：1099. 小于 K 的两数之和（Two Sum Less Than K）
// 思路：先排序，再对每个 nums[i] 二分出最后一个满足 nums[j] < k - nums[i] 的下标 j，用两数之和更新最大值。
// 时间复杂度：O(n log n)，排序 O(n log n) 加 n 次二分；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int twoSumLessThanK(vector<int>& nums, int k) {  // nums：候选数组（会被原地排序）；k：两数之和必须严格小于它
        sort(nums.begin(), nums.end());  // 排序后才有单调性，二分与「下标越大值越大」的贪心才成立
        int ans = -1, n = nums.size();  // ans 初始 -1 表示不存在合法数对；n 为数组长度
        for (int i = 0; i < n; ++i) {  // 枚举较小的那个数的下标 i
            int j = lower_bound(nums.begin() + i + 1, nums.end(), k - nums[i]) - nums.begin() - 1;  // lower_bound 找到第一个 >= k - nums[i] 的位置，再减 1 就是最后一个合法的 j
            if (i < j) {  // j 必须严格大于 i，避免同一个元素被用两次
                ans = max(ans, nums[i] + nums[j]);  // 用这对数的和更新最大值
            }  // if 结束
        }  // for 结束
        return ans;  // 返回最大和，没有合法数对时保持 -1
    }  // 方法结束
};  // 类定义结束