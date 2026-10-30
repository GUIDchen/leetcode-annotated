// 题目：1768. 交替合并字符串（Merge Strings Alternately）
// 思路：以同一个下标 i 同时访问两个串，只要任一串还有第 i 个字符就继续循环，依次把 word1[i]、word2[i] 追加到答案串后面。
// 时间复杂度：O(m + n)，每个字符只追加一次；空间复杂度：O(m + n)，返回的合并串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string mergeAlternately(string word1, string word2) {  // word1、word2 是待交替合并的两个字符串
        int m = word1.size(), n = word2.size();  // m、n 分别是两个字符串的长度
        string ans;  // 答案串，逐字符追加
        for (int i = 0; i < m || i < n; ++i) {  // 两个串只要有任意一个还没取完就继续循环
            if (i < m) ans += word1[i];  // word1 还有第 i 个字符，就先追加它
            if (i < n) ans += word2[i];  // word2 还有第 i 个字符，再追加它；两个 if 保证交替且不越界
        }
        return ans;  // 返回合并后的字符串
    }  // 方法结束
};  // 类定义结束