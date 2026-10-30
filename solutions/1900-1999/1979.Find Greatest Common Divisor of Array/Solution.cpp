// 题目：1979. 找出数组的最大公约数（Find Greatest Common Divisor of Array）
// 思路：数组的最大值与最小值一定都在数组中，答案就是这两个数的最大公约数，直接一次遍历取极值再求 gcd。
// 时间复杂度：O(n)，一次遍历找极值；空间复杂度：O(1)，只用两个迭代器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findGCD(vector<int>& nums) {  // nums：输入数组，返回其最大值与最小值的最大公约数
        auto [min, max] = ranges::minmax_element(nums);  // C++20 结构化绑定：一次遍历同时取到最小值与最大值的迭代器
        return gcd(*min, *max);  // 解引用得到两个极值，再用 std::gcd 求它们的最大公约数
    }  // 方法结束
};  // 类定义结束
