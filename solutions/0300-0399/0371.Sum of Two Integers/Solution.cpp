// 题目：371. 两整数之和（Sum of Two Integers）
// 思路：不用 + 号，用异或求无进位和、用与运算左移一位求进位，循环把进位加回去直到没有进位。
// 时间复杂度：O(log n)，进位最多传播 32 轮（这里通常几轮）；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getSum(int a, int b) {  // a、b 是待相加的两个整数（可正可负）
        while (b) {  // b 非 0 说明还有进位待处理
            unsigned int carry = (unsigned int) (a & b) << 1;  // 进位：a & b 标出同为 1 的位，左移一位进到高位；转 unsigned 避免左移溢出
            a = a ^ b;  // 无进位和：异或得到不考虑进位的结果
            b = carry;  // 把进位当作新的加数继续迭代
        }  // 循环体闭合，直到进位为 0
        return a;  // 没有进位残留时 a 就是最终和
    }  // 方法结束
};  // 类定义结束