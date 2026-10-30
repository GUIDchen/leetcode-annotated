// 题目：2309. 兼具大小写的最好英文字母（Greatest English Letter in Upper and Lower Case）
// 思路：先把所有字符放进哈希集合，再从 Z 向 A 倒序枚举，第一个大小写都出现过的字母就是答案。
// 时间复杂度：O(n + 26)，n 为字符串长度；空间复杂度：O(26)，集合最多存 52 个不同字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string greatestLetter(string s) {  // s 是只含英文字母的字符串
        unordered_set<char> ss(s.begin(), s.end());  // 把出现过的字符全部存入哈希集合，便于 O(1) 判断某字符是否存在
        for (char c = 'Z'; c >= 'A'; --c) {  // 从最大的字母开始倒序枚举，保证第一个满足条件的就是字典序最大者
            if (ss.count(c) && ss.count(char(c + 32))) {  // 大写 c 与它的小写形式 c + 32 都出现过，则 c 有效
                return string(1, c);  // 用 c 构造长度为 1 的字符串返回
            }
        }
        return "";  // 没有任何字母同时以大小写出现，返回空串
    }
};  // 类定义结束，最后一个分号收尾