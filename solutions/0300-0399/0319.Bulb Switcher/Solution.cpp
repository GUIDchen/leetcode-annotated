// 题目：319. 灯泡开关（Bulb Switcher）
// 思路：第 i 个灯泡被切换 i 的约数个数次，只有完全平方数的约数个数为奇数，故答案就是 sqrt(n) 向下取整。
// 时间复杂度：O(1)，只做一次开方；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int bulbSwitch(int n) {  // n：灯泡总数；返回最后仍然亮着的灯泡个数
        return (int) sqrt(n);  // 1..n 中的完全平方数个数就是 floor(sqrt(n))，也就是最终亮着的灯泡数
    }  // 方法结束
};  // 类定义结束