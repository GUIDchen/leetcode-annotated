// 题目：2535. 数组元素和与数字和的绝对差（Difference Between Element Sum and Digit Sum of an Array）
// 思路：范围 for 遍历数组，一边累加元素和 x，一边把每个元素逐位拆成数位和 y，返回 x - y。
// 时间复杂度：O(n log M)，M 为元素最大值；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int differenceOfSum(vector<int>& nums) {  // nums 为输入数组，返回元素和与数字和之差
        int x = 0, y = 0;  // x 存元素和，y 存数位和
        for (int v : nums) {  // 范围 for 按值取出每个元素（拷贝一份便于原地除 10 拆位）
            x += v;  // 累加元素和
            for (; v; v /= 10) {  // for 的初始化与条件都留空：循环体里 v 逐位除 10，v 变成 0 时自然结束
                y += v % 10;  // 把最低位数字累加到数位和
            }  // 循环体结束
        }  // 外层遍历结束
        return x - y;  // 返回元素和与数位和之差
    }  // 方法结束
};  // 类定义结束
