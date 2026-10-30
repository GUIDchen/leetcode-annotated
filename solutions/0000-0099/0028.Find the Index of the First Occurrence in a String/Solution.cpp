// 题目：28. 找出字符串中第一个匹配项的下标（Find the Index of the First Occurrence in a String）
// 思路：朴素枚举所有可能的起点 i（最多 n-m 个），用 substr 截出长度 m 的子串与 needle 直接比较；由于 i 从小到大枚举，第一个相等的就是答案。
// 时间复杂度：O((n-m+1)·m)，最坏情况每次比较都要看完整个 needle；空间复杂度：O(m)，substr 会创建临时子串（不计入则 O(1)）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int strStr(string haystack, string needle) {  // haystack：主串；needle：模式串；返回第一次出现的下标，找不到返回 -1
        int n = haystack.size(), m = needle.size();  // n、m 分别是主串和模式串的长度
        for (int i = 0; i + m <= n; ++i) {  // 起点 i 从 0 枚举到 n-m，保证子串不越界
            if (haystack.substr(i, m) == needle) {  // 从 i 开始截取长度 m 的子串，与模式串逐字符比较（string 的 == 是内容比较）
                return i;  // 相等说明找到了第一个匹配项，直接返回起点下标
            }
        }
        return -1;  // 所有起点都试过仍不匹配，按题目要求返回 -1
    }
};
