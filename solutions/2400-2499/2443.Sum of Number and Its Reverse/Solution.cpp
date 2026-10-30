// 题目：2443. 反转之后的数字和（Sum of Number and Its Reverse）
// 思路：枚举加数 x ∈ [0, num]，把 x 十进制反转得到 y，判断 x + y 是否等于 num，命中即返回 true。
// 时间复杂度：O(num·log num)，枚举 num+1 个数、每数反转 O(log num)；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool sumOfNumberAndReverse(int num) {  // 判断 num 是否能表示成「某个数与其反转数之和」
        for (int x = 0; x <= num; ++x) {  // 枚举较小的加数 x；两个非负整数之和为 num，所以 x 不超过 num
            int k = x;  // k 是 x 的副本，反转时会被反复除以 10
            int y = 0;  // y 用来累积 x 的反转结果
            while (k > 0) {  // 逐位剥离 k 的末位，直到 k 变成 0
                y = y * 10 + k % 10;  // 把 k 的末位接到 y 的末尾（y 整体左移一位再补末位）
                k /= 10;  // 丢掉 k 已经取出的末位
            }
            if (x + y == num) {  // 检查 x 与它的反转 y 之和是否等于目标
                return true;  // 存在这样的加数，返回真
            }
        }
        return false;  // 所有可能的加数都试过仍不成立，返回假
    }
};  // 类定义结束