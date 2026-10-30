// 题目：3075. 幸福值最大化的选择方案（Maximize Happiness of Selected Children）
// 思路：贪心。降序排序后第 i 轮选当前幸福值最大的孩子，此时它已被前面 i 轮各减 1，实际贡献为 happiness[i] - i，负数按 0 计。
// 时间复杂度：O(n log n)，排序是瓶颈；空间复杂度：O(1)，排序在原数组上进行。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumHappinessSum(vector<int>& happiness, int k) {  // happiness：每个孩子的幸福值；k：需要选出的孩子数量；返回选中孩子的幸福值之和的最大值
        sort(happiness.rbegin(), happiness.rend());  // 幸福值从大到小排序，让越大的值越早被选到、被减的次数越少
        long long ans = 0;  // 累加答案，幸福值之和可能超出 int，所以用 long long
        for (int i = 0, n = happiness.size(); i < k; ++i) {  // 只选 k 个孩子；n 提前取出，避免每轮重复计算 size
            int x = happiness[i] - i;  // 第 i 轮选中的孩子已被前面 i 轮各削减 1，实际幸福值是 happiness[i] - i
            ans += max(x, 0);  // 幸福值不能为负，按 0 计入总和
        }
        return ans;  // 返回 k 个孩子幸福值之和的最大值
    }
};