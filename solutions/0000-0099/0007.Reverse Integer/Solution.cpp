// 题目：7. 整数反转（Reverse Integer）
// 思路：循环取末位拼到结果末尾；每轮用 INT_MIN/10、INT_MAX/10 预判溢出，越界直接返回 0。
// 时间复杂度：O(log|x|)，循环次数即十进制位数；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int reverse(int x) {  // x 为待反转的 32 位有符号整数
        int ans = 0;  // 反转结果累加器
        for (; x; x /= 10) {  // x 非 0 时循环，每轮末尾丢掉最后一位
            if (ans < INT_MIN / 10 || ans > INT_MAX / 10) {  // 预判下一步乘 10 是否溢出（用除法比较，避免真的溢出）
                return 0;  // 溢出按题意返回 0
            }
            ans = ans * 10 + x % 10;  // 取 x 的末位拼到 ans 末尾
        }
        return ans;  // 返回反转后的整数
    }
};