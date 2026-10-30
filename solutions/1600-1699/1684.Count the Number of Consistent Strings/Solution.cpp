// 题目：1684. 统计一致字符串的数目（Count the Number of Consistent Strings）
// 思路：用 26 位的 bitset 记下 allowed 里出现过哪些字母，再用 lambda 逐个单词检查，每个字符都在集合中才计入答案。
// 时间复杂度：O(|allowed| + Σ|word|)，每个字符只检查一次；空间复杂度：O(1)，只用一个 26 位的 bitset。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countConsistentStrings(string allowed, vector<string>& words) {  // allowed：允许的字符集合；words：待检查的单词；返回一致字符串的数目
        bitset<26> s;  // bitset<26> 的每一位对应一个小写字母，1 表示该字母允许出现
        for (auto& c : allowed) s[c - 'a'] = 1;  // 标记 allowed 中出现过的每个字母
        int ans = 0;  // ans 累计一致的单词个数
        auto check = [&](string& w) {  // 定义判定函数：单词里只要有字符不被允许就返回 false
            for (auto& c : w)  // 逐个字符检查该单词
                if (!s[c - 'a']) return false;  // 该字符不在 allowed 中，说明单词不一致，立即返回 false
            return true;  // 所有字符都通过检查，该单词一致
        };
        for (auto& w : words) ans += check(w);  // 逐词判定，布尔值直接加到答案上（true 记 1，false 记 0）
        return ans;  // 返回一致字符串的数目
    }
};  // 题解类结束