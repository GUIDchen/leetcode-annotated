// 题目：3101. 交替子数组计数（Count Alternating Subarrays）
// 思路：一次遍历的计数型 DP，用 s 记录以当前元素结尾的交替子数组个数：相邻元素不同则 s 加一，相同则重置为 1，同时把 s 累加进答案。
// 时间复杂度：O(n)，只需一趟扫描；空间复杂度：O(1)，只用两个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countAlternatingSubarrays(vector<int>& nums) {  // nums：输入数组，返回其中所有交替子数组的个数
        long long ans = 1, s = 1;  // ans 是总答案；s 是以当前元素结尾的交替子数组个数，单个元素自身算 1 个
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始，逐个检查它与前一个元素是否不同
            s = nums[i] != nums[i - 1] ? s + 1 : 1;  // 相邻不同则交替段可以延续，s 加一；相同则只能从当前元素重新开始，s 重置为 1
            ans += s;  // 以当前元素结尾的这 s 个交替子数组都是新增的，累加进答案
        }  // 结束遍历
        return ans;  // 返回交替子数组总数
    }  // 结束题解方法
};  // 结束题解类