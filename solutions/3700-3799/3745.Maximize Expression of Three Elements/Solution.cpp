// 题目：3745. 三元素表达式的最大值（Maximize Expression of Three Elements）
// 核心思路：表达式的正号落在两个元素上、负号落在一个元素上，因此答案必然是「最大的两个数之和减去最小的一个数」；一次遍历同时维护最大值 a、次大值 b 与最小值 c 即可。
// 复杂度：时间 O(n)，只扫描一遍数组；空间 O(1)，只用三个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximizeExpressionOfThree(vector<int>& nums) {  // nums：整数数组；返回 nums[i] + nums[j] - nums[k] 的最大值（三个下标互不相同）
        const int inf = 1 << 30;  // 用一个足够大的数表示无穷
        int a = -inf, b = -inf, c = inf;  // a、b 分别是最大值与次大值；c 是最小值
        for (int x : nums) {  // 一遍扫描同时维护两个最大值和一个最小值
            if (x < c) {  // 出现更小的值
                c = x;  // 更新最小值
            }  // 最小值更新结束
            if (x >= a) {  // 出现不小于当前最大值的元素
                b = a;  // 原来的最大值降为次大值
                a = x;  // 更新最大值
            } else if (x > b) {  // 没有刷新最大值，但比次大值大
                b = x;  // 更新次大值
            }  // 最值更新结束
        }  // 扫描结束
        return a + b - c;  // 最大两数之和减去最小值即答案
    }  // 方法结束
};  // 类定义结束
