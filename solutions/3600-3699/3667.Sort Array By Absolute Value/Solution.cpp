// 3667. Sort Array By Absolute Value（3667. 按绝对值排序数组）🔒
// 核心思路：直接用自定义比较器把数组按绝对值升序排序。
// 复杂度：时间 O(n log n)，空间 O(log n)（排序栈开销）。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    vector<int> sortByAbsoluteValue(vector<int>& nums) {  // 按绝对值升序排列数组并返回
        sort(nums.begin(), nums.end(), [](int a, int b) {  // 调用标准排序，传入自定义比较器
            return abs(a) < abs(b);  // 绝对值小的排在前面
        });  // 结束比较器并结束 sort 调用
        return nums;  // 返回排序后的数组
    }  // 结束方法
};  // 结束题解类
