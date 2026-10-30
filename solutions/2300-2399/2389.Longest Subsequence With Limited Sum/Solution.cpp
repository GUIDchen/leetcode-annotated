// 题目：2389. 和有限的最长子序列（Longest Subsequence With Limited Sum）
// 思路：先排序，再把数组原地改写成前缀和；对查询值 q 取 upper_bound 下标，即前缀和 ≤ q 的元素个数，也就是最长子序列长度。
// 时间复杂度：O(n log n + q log n)，排序 O(n log n)、每个查询二分 O(log n)；空间复杂度：O(q)，返回值数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {  // nums：候选数组；queries：每个查询的上限
        ranges::sort(nums);  // C++20 的范围排序：升序排列，取尽量多的数就应当优先取最小的数
        for (int i = 1; i < nums.size(); i++) {  // 从第二个元素开始，原地构造前缀和
            nums[i] += nums[i - 1];  // nums[i] 变为前 i+1 个最小元素之和
        }  // 前缀和构造完成
        vector<int> ans;  // 保存每个查询的答案
        for (const auto& q : queries) {  // 依次处理每个查询
            ans.emplace_back(upper_bound(nums.begin(), nums.end(), q) - nums.begin());  // 第一个前缀和 > q 的下标，正好等于能取的元素个数
        }  // 查询循环结束
        return ans;  // 返回所有答案
    }  // 方法结束
};
