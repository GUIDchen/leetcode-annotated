// 题目：3120. 统计特殊字母的数量 I（Count the Number of Special Characters I）
// 思路：先用布尔数组标记出现过的字符，再枚举 26 个字母，若某个字母的大小写都出现过就计数。
// 时间复杂度：O(n + 26)，n 为字符串长度；空间复杂度：O(1)，字符集大小固定。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfSpecialChars(string word) {  // word：输入字符串，返回大小写都出现过的字母个数
        vector<bool> s('z' + 1);  // s[c] 表示字符 c 是否出现过，下标直接用字符的 ASCII 值
        for (char& c : word) {  // 遍历字符串中的每个字符
            s[c] = true;  // 标记该字符已经出现
        }  // 结束遍历
        int ans = 0;  // 记录特殊字母的个数
        for (int i = 0; i < 26; ++i) {  // 枚举 26 个字母，i 为字母在字母表中的偏移
            ans += s['a' + i] && s['A' + i];  // 小写与大写都出现过时，布尔值相乘得 1，直接累加
        }  // 结束字母枚举
        return ans;  // 返回特殊字母的数量
    }  // 结束 numberOfSpecialChars
};  // 类定义结束