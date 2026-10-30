// 题目：2769. 找出最大的可达成数字（Find the Maximum Achievable Number）
// 思路：每次操作同时让 num 加 1、让 x 减 1，一次操作把两者差距缩小 2，因此 t 次操作后 x 最大为 num + 2t。
// 时间复杂度：O(1)，只做一次乘加；空间复杂度：O(1)，不使用额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int theMaximumAchievableX(int num, int t) {  // num：初始数字；t：最多可以执行的操作次数
        return num + t * 2;  // 每次操作贡献 2 的差距，t 次操作后 x 的最大取值
    }  // 方法结束
};  // 类定义结束