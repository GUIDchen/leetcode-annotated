// 3732. 一次替换后的三元素最大乘积 / Maximum Product of Three Elements After One Replacement
// 核心思路：把其中一个元素替换成上界 x 后，最大乘积只会来自三种组合：两个最小值乘 x、两个最大值乘 x、最大正数与最小负数相乘再乘 x。排序后直接比较这三者。
// 复杂度：时间 O(n log n)，空间 O(1)（排序所需空间除外）。
class Solution {  // 定义 LeetCode 解法类
public:  // 公有接口
    long long maxProduct(vector<int>& nums) {  // 返回替换一个元素后的三数最大乘积
        sort(nums.begin(), nums.end());  // 升序排序，方便取两端极值
        int n = nums.size();  // 数组长度
        long long a = nums[0], b = nums[1];  // a、b 为最小的两个元素（可能为负数）
        long long c = nums[n - 2], d = nums[n - 1];  // c、d 为最大的两个元素
        const int x = 100000;  // 替换值的上界
        return max({a * b * x, c * d * x, -a * d * x});  // 三种候选取最大：两个最小值乘 x、两个最大值乘 x、最大正数与最小负数相乘再乘 x
    }  // 方法结束
};  // 类定义结束
