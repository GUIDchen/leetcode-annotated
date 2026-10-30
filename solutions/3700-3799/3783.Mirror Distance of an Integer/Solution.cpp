// 题目：3783. 整数的镜像距离（Mirror Distance of an Integer）
// 核心思路：用循环不断取最低位并累乘 10，得到十进制数字逆序后的整数，再与 n 相减取绝对值。
// 复杂度：时间 O(log n)，即 n 的十进制位数；空间 O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // public 区的方法供判题器调用
    int mirrorDistance(int n) {  // 返回 n 与其各位数字逆序后所得整数之差的绝对值
        auto reverse = [](int x) -> int {  // 定义一个 lambda，把整数 x 的十进制数字整体逆序
            int y = 0;  // y 用来累积逆序结果，初值 0
            for (; x; x /= 10) {  // 每次取 x 的最低位，直到 x 被除尽
                y = y * 10 + x % 10;  // y 左移一位（乘 10）后加上 x 的末位数字
            }  // 循环结束
            return y;  // 返回逆序后的整数
        };  // lambda 定义结束
        return abs(n - reverse(n));  // 镜像距离 = |n - reverse(n)|
    }  // 方法结束
};  // 类定义结束
