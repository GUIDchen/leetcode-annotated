// 题目：2956. 找到两个数组中的公共元素（Find Common Elements Between Two Arrays）
// 思路：用两个长度 101 的标记数组分别记下 nums1、nums2 中出现过的值，再各扫一遍，统计对方标记为 1 的元素个数。
// 时间复杂度：O(n + m)，两次标记加两次统计都是线性；空间复杂度：O(101)，两个固定大小的标记数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findIntersectionValues(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2 是输入数组，返回长度为 2 的结果：nums1 中能在 nums2 找到的个数、nums2 中能在 nums1 找到的个数
        int s1[101]{};  // 值域为 1..100，用下标直接标记 nums1 中出现过的值，{} 保证全部初始化为 0
        int s2[101]{};  // 同上，标记 nums2 中出现过的值
        for (int& x : nums1) {  // 遍历 nums1 的每个元素，用引用避免拷贝
            s1[x] = 1;  // 标记该值在 nums1 中出现过
        }  // 第一个标记循环结束
        for (int& x : nums2) {  // 遍历 nums2 的每个元素
            s2[x] = 1;  // 标记该值在 nums2 中出现过
        }  // 第二个标记循环结束
        vector<int> ans(2);  // 结果数组，两个计数器都从 0 开始
        for (int& x : nums1) {  // 再扫一遍 nums1
            ans[0] += s2[x];  // 若 x 在 nums2 中出现过（s2[x] 为 1），则第一个计数加一
        }  // 第一个统计循环结束
        for (int& x : nums2) {  // 再扫一遍 nums2
            ans[1] += s1[x];  // 若 x 在 nums1 中出现过，则第二个计数加一
        }  // 第二个统计循环结束
        return ans;  // 按题目要求返回 [nums1 的计数, nums2 的计数]
    }  // 方法体结束
};  // 题解类结束