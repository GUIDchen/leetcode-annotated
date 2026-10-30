// 题目：2514. 统计同位异构字符串数目（Count Anagrams）
// 思路：每个单词内部的字母可以任意重排，各单词彼此独立，答案就是各单词方案数之积；长度为 L、各字母出现次数为 c 的单词有 L! / ∏c! 种排列。
// 时间复杂度：O(|s| + log mod)，一遍扫描加一次快速幂；空间复杂度：O(1)，除 stringstream 缓冲外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    const int mod = 1e9 + 7;  // 取模常数，题目要求答案对 1e9+7 取余

    int countAnagrams(string s) {  // s 是由空格分隔的若干单词
        stringstream ss(s);  // 用字符串流按空白逐个取出单词
        string w;  // 当前正在处理的单词
        long ans = 1, mul = 1;  // ans 累积所有单词长度阶乘；mul 累积所有「重复字母计数阶乘」
        while (ss >> w) {  // 逐个读取单词，读完为止
            int cnt[26] = {0};  // 记录当前单词里每个字母出现了多少次
            for (int i = 1; i <= w.size(); ++i) {  // 用 1 基下标遍历，i 同时充当阶乘的乘数
                int c = w[i - 1] - 'a';  // 把字符映射成 0~25 的下标
                ++cnt[c];  // 该字母出现次数加一
                ans = ans * i % mod;  // 累乘 1·2·…·L，得到长度阶乘 L!
                mul = mul * cnt[c] % mod;  // 该字母第几次出现就乘几次，最终得到 ∏c!
            }
        }
        return ans * pow(mul, mod - 2) % mod;  // 费马小定理：除以 mul 等价于乘 mul^(mod-2)
    }

    long pow(long x, int n) {  // 快速幂：计算 x^n mod mod
        long res = 1L;  // 累乘结果，初始为 1
        for (; n; n /= 2) {  // 指数每次折半，直到变为 0
            if (n % 2) res = res * x % mod;  // 当前二进制最低位为 1，就把这一项乘进结果
            x = x * x % mod;  // 底数平方，对应下一位二进制
        }
        return res;  // 返回 x^n mod mod
    }
};