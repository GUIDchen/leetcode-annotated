// 题目：1636. 按照频率将数组升序排序（Sort Array by Increasing Frequency）
// 思路：先统计每个值的出现次数，再按「频率升序、频率相同则值降序」的规则重排数组。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，计数数组大小固定为 201（值域 -100~100）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> frequencySort(vector<int>& nums) {  // nums 是输入数组，返回按频率升序（同频时值降序）排好的数组
        vector<int> cnt(201);  // 计数数组：下标 = 值 + 100，长度 201 覆盖 -100~100 的值域
        for (int v : nums) {  // 遍历每个元素统计频次
            ++cnt[v + 100];  // 偏移 100 把负数映射到非负下标，对应位置计数加一
        }  // 频次统计循环结束
        sort(nums.begin(), nums.end(), [&](const int a, const int b) {  // 自定义比较器：按频次升序，频次相同时按值降序（[&] 捕获 cnt 的引用）
            if (cnt[a + 100] == cnt[b + 100]) return a > b;  // 频次相同则值大的排前面
            return cnt[a + 100] < cnt[b + 100];  // 频次不同则频次小的排前面
        });  // sort 调用结束
        return nums;  // 原地排好序后直接返回该数组
    }  // frequencySort 方法结束
};  // 题解类定义结束