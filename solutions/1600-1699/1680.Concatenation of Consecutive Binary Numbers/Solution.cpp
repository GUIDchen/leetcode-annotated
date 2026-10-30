// 题目：1680. 连接连续二进制数字（Concatenation of Consecutive Binary Numbers）
// 思路：从左到右增量拼接；i 的二进制位数为 32 - __builtin_clz(i)，把当前结果左移这么多位再按位或上 i，然后取模。
// 时间复杂度：O(n)，每个 i 只做常数次位运算；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int concatenatedBinary(int n) {  // 把 1 到 n 的二进制串首尾相接，返回对 1e9+7 取模后的值
        const int mod = 1e9 + 7;  // 题目要求的取模数
        long long ans = 0;  // ans 保存当前拼接结果；用 long long 防止左移时溢出
        for (int i = 1; i <= n; ++i) {  // 依次把 1 到 n 的二进制串拼到已有结果后面
            ans = (ans << (32 - __builtin_clz(i)) | i) % mod;  // __builtin_clz 数出前导零个数，32 减它就是 i 的二进制位数：左移腾出低位，再按位或上 i，最后取模
        }
        return ans;  // 返回拼接结果
    }
};  // 题解类结束
