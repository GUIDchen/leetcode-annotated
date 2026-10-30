// 题目：633. 平方数之和（Sum of Square Numbers）
// 思路：双指针夹逼：a 从 0 递增、b 从 floor(sqrt(c)) 递减，比较 a^2 + b^2 与 c，小了增大 a，大了减小 b。
// 时间复杂度：O(sqrt c)，两指针总共移动 O(sqrt c) 次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool judgeSquareSum(int c) {  // 判断 c 能否写成两个整数的平方和
        long long a = 0, b = sqrt(c);  // 双指针：a 取最小 0，b 取最大 floor(sqrt(c))；用 long long 防止平方和超出 int
        while (a <= b) {  // a 超过 b 说明已尝试完所有组合
            long long s = a * a + b * b;  // 当前两数的平方和
            if (s == c) {  // 正好等于 c，找到答案
                return true;  // 返回 true
            }  // 相等分支结束
            if (s < c) {  // 平方和偏小，需要增大 a
                ++a;  // 右移左指针
            } else {  // 平方和偏大，需要减小 b
                --b;  // 左移右指针
            }  // 分支结束
        }  // 循环结束，没有找到组合
        return false;  // 返回 false
    }  // 方法结束
};  // 类定义结束