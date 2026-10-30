// 题目：2529. 正整数和负整数的最大计数（Maximum Count of Positive Integer and Negative Integer）
// 核心思路：遍历一遍统计正数个数 a 与负数个数 b，0 不属于任何一边，答案就是 max(a, b)。
// 时间复杂度：O(n)，数组只扫描一次；空间复杂度：O(1)，只用了两个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumCount(vector<int>& nums) {  // nums 是升序数组，返回正整数个数与负数个数中的较大值
        int a = 0, b = 0;  // a 统计正数个数，b 统计负数个数
        for (int x : nums) {  // 范围 for 逐个取出数组元素
            if (x > 0) {  // 当前元素是正数
                ++a;  // 正数计数器加一
            } else if (x < 0) {  // 当前元素是负数
                ++b;  // 负数计数器加一
            }  // 等于 0 时不计入任何一方
        }  // 遍历完毕，两个计数都已就绪
        return max(a, b);  // 取较大者返回
    }  // 方法结束
};  // 类定义结束