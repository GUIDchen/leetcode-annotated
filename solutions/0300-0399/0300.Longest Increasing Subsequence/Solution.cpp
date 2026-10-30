// 题目：300. 最长递增子序列（Longest Increasing Subsequence）
// 思路：动态规划，f[i] 表示以 nums[i] 结尾的最长严格递增子序列长度，从前向后用 j 枚举所有可接在后面的前驱。
// 时间复杂度：O(n^2)，两层循环枚举数对；空间复杂度：O(n)，保存长度为 n 的 DP 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int lengthOfLIS(vector<int>& nums) {  // nums：输入数组；返回最长严格递增子序列的长度
        int n = nums.size();  // 数组长度
        vector<int> f(n, 1);  // f[i]：以 nums[i] 结尾的最长递增子序列长度，每项至少为 1（只含自己）
        for (int i = 1; i < n; ++i) {  // 从第二个元素开始递推
            for (int j = 0; j < i; ++j) {  // 枚举 i 之前的所有位置作为前驱
                if (nums[j] < nums[i]) {  // 严格递增：前驱值必须小于当前值才能接上
                    f[i] = max(f[i], f[j] + 1);  // 接上 j 之后长度是 f[j]+1，与现有 f[i] 取较大者
                }  // if 块结束
            }  // 内层循环结束
        }  // 外层循环结束
        return *max_element(f.begin(), f.end());  // 答案不一定在末尾，要取整张 DP 表的最大值
    }  // 方法结束
};  // 类定义结束