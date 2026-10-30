// 题目：2119. 反转两次的数字（A Number After a Double Reversal）
// 核心思路：反转两次能否还原只取决于末位——末位为 0 时第一次反转会丢位，只有 0 本身例外。
// 时间复杂度：O(1)，只做一次取模与比较；空间复杂度：O(1)，不使用额外空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isSameAfterReversals(int num) {  // num：待判断的整数
        return num == 0 || num % 10 != 0;  // 0 反转两次仍是 0；末位非 0 不会丢位，两次反转必然还原
    }  // 方法体结束
};  // 类定义结束