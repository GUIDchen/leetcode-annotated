// 题目：2707. 字符串中的额外字符（Extra Characters in a String）
// 思路：动态规划，f[i] 表示前 i 个字符中最少剩下多少额外字符；要么第 i 个字符单独作废，要么枚举 j 让 s[j..i) 恰好是一个字典单词。
// 时间复杂度：O(n^3)，两层枚举加子串复制，n 为串长；空间复杂度：O(n + D)，f 数组与字典哈希集合，D 为字典总字符数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minExtraChar(string s, vector<string>& dictionary) {  // s：原字符串；dictionary：可用的单词表
        unordered_set<string> ss(dictionary.begin(), dictionary.end());  // 把单词表转成哈希集合，方便 O(1) 判断某个子串是不是字典单词
        int n = s.size();  // 原串长度
        int f[n + 1];  // f[i]：前 i 个字符中能产生的最少额外字符数
        f[0] = 0;  // 边界：空串没有额外字符
        for (int i = 1; i <= n; ++i) {  // 按前缀长度从小到大递推
            f[i] = f[i - 1] + 1;  // 最坏情况：第 i 个字符无法匹配，单独算一个额外字符
            for (int j = 0; j < i; ++j) {  // 枚举单词起点 j，尝试用某个单词覆盖 s[j..i)
                if (ss.count(s.substr(j, i - j))) {  // 若 s[j..i) 正好是字典中的一个单词
                    f[i] = min(f[i], f[j]);  // 这一段不产生额外字符，尝试用 f[j] 更新答案
                }
            }
        }
        return f[n];  // 整个串的最少额外字符数
    }
};