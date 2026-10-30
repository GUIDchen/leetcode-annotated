// 题目：1403. 非递增顺序的最小子序列（Minimum Subsequence in Non-Increasing Order）
// 思路：降序排序后从大到小累加子序列和 t，用总和 s 判断剩余元素和 s - t；一旦 t > s - t 就停止，得到的子序列元素最少且字典序最大。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，存放结果的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> minSubsequence(vector<int>& nums) {  // nums 为输入数组
        sort(nums.rbegin(), nums.rend());  // 用反向迭代器原地降序排序
        int s = accumulate(nums.begin(), nums.end(), 0);  // s 为整个数组的元素总和
        int t = 0;  // t 为已选子序列的元素和
        vector<int> ans;  // 存放最终子序列
        for (int x : nums) {  // 按从大到小的顺序逐个选取
            t += x;  // 把当前元素并入子序列并更新子序列和
            ans.push_back(x);  // 记录到结果中
            if (t > s - t) {  // s - t 是剩余元素之和，严格大于即满足题目要求
                break;  // 已满足条件，及时收手保证元素最少
            }  // 判定分支结束
        }  // 遍历结束
        return ans;  // 返回满足条件的子序列
    }  // minSubsequence 方法结束
};  // Solution 类结束