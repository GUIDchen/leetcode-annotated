// 题目：3232. 判断是否可以赢得数字游戏（Find if Digit Game Can Be Won）
// 思路：Alice 只能取一位数、Bob 只能取两位数，两人的可选集合固定；只要两组之和不等，Alice 选择较大的那一组即可获胜。
// 时间复杂度：O(n)，一次遍历求和；空间复杂度：O(1)，只用两个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canAliceWin(vector<int>& nums) {  // nums：可选数字；返回先手 Alice 是否能赢
        int a = 0, b = 0;  // a：一位数之和；b：两位数之和
        for (int x : nums) {  // 逐个数字累加到对应的和里
            if (x < 10) {  // 一位数只能归 Alice
                a += x;  // 累加到 Alice 的和
            } else {  // 否则是两位数，只能归 Bob
                b += x;  // 累加到 Bob 的和
            }  // 判断结束
        }  // 遍历结束
        return a != b;  // 两边之和不等时，Alice 选择较大的一组即可获胜
    }  // 方法结束
};  // 类定义结束