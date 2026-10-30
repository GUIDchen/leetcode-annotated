// 题目：2063. 所有子字符串中的元音（Vowels of All Substrings）
// 思路：按每个元音字符的贡献计数：下标 i 处的元音会被 (i+1)*(n-i) 个子串包含，逐位累加即可。
// 时间复杂度：O(n)，只扫一遍字符串；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countVowels(string word) {  // word：输入字符串；返回所有子串中的元音总数
        long long ans = 0;  // 元音总贡献，结果可能超过 int，所以用 long long
        for (int i = 0, n = word.size(); i < n; ++i) {  // i 是下标，n 是长度，顺带在初始化里求出
            char c = word[i];  // 取当前字符
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {  // 只统计元音字符
                ans += (i + 1LL) * (n - i);  // 以 i 为元音的子串数：左端点有 i+1 种，右端点有 n-i 种
            }
        }
        return ans;  // 返回所有子串里元音字符的总个数
    }
};