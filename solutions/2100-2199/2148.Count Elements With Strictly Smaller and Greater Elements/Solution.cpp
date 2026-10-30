// 题目：2148. 元素计数（Count Elements With Strictly Smaller and Greater Elements）
// 思路：先用 ranges::minmax_element 一次求出最小值与最大值的迭代器，再统计严格大于最小值且严格小于最大值的元素个数。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只保存两个迭代器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countElements(vector<int>& nums) {  // nums：输入的整数数组
        auto [mi, mx] = ranges::minmax_element(nums);  // 结构化绑定取出指向最小值与最大值的迭代器
        return ranges::count_if(nums, [mi, mx](int x) { return *mi < x && x < *mx; });  // 统计满足 mi < x < mx 的元素个数并返回
    }
};  // 类定义结束
