// 题目：1708. 长度为 K 的最大子数组（Largest Subarray Length K）
// 思路：元素互不相同，长度相同的子数组字典序只由首元素决定；首元素只能取前 n-k+1 个位置，在其中找最大值位置，再从该位置连续取 k 个元素。
// 时间复杂度：O(n)，一次线性扫描找最大值；空间复杂度：O(1)，除返回值外只用一个迭代器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> largestSubarray(vector<int>& nums, int k) {  // nums：元素互不相同的输入数组；k：子数组长度
        auto i = max_element(nums.begin(), nums.end() - k + 1);  // 首元素只能落在前 n-k+1 个位置内，max_element 返回其中最大值所在位置
        return {i, i + k};  // 从该位置起连续取 k 个元素，即为字典序最大的子数组
    }  // 方法结束
};  // 类定义结束