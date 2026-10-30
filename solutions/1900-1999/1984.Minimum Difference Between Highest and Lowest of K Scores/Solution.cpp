// 题目：1984. 学生分数的最小差值（Minimum Difference Between Highest and Lowest of K Scores）
// 思路：排序后，最优的 k 个分数必定是连续的一段；再用长度为 k 的滑动窗口求 nums[i+k-1] - nums[i] 的最小值。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(log n)，排序使用的递归栈（原地排序）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumDifference(vector<int>& nums, int k) {  // nums：分数数组；k：要选出的学生人数
        sort(nums.begin(), nums.end());  // 升序排序，让「取 k 个」变成「取连续的一段」
        int ans = 1e5;  // 差值上界（分数不超过 1e5），保证第一次比较一定被更新
        for (int i = 0; i < nums.size() - k + 1; ++i) {  // i 是窗口左端点，右端点为 i+k-1，必须保证不越界
            ans = min(ans, nums[i + k - 1] - nums[i]);  // 排序后窗口内最大值减最小值，就是这 k 个分数的极差
        }  // 窗口枚举结束
        return ans;  // 返回最小的极差
    }  // 方法结束
};  // 类定义结束