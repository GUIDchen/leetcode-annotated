// 题目：908. 最小差值 I（Smallest Range I）
// 核心思路：只有最大值和最小值决定差值，两者各自最多向中间调整 k，所以最小差值就是 max(0, max - min - 2k)。
// 时间复杂度：O(n)，一次遍历求最值；空间复杂度：O(1)，只用两个迭代器。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int smallestRangeI(vector<int>& nums, int k) {  // nums：输入数组；k：每个元素最多可加减的幅度；返回最小的最大差值
        auto [mi, mx] = minmax_element(nums.begin(), nums.end());  // 结构化绑定：一次遍历同时得到最小值和最大值的迭代器
        return max(0, *mx - *mi - k * 2);  // 最大值减 k、最小值加 k 后差值缩小 2k，且结果不能为负
    }  // 结束 smallestRangeI
};  // 结束 Solution 类