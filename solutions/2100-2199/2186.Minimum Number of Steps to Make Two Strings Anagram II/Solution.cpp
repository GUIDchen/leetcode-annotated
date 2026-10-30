// 题目：2186. 制造字母异位词的最小步骤数 II（Minimum Number of Steps to Make Two Strings Anagram II）
// 思路：统计 s 与 t 中每个字母的出现次数差；s 多出的字母要删掉，t 多出的字母要给 s 补上，步数就是全部差值绝对值之和。
// 时间复杂度：O(|s| + |t| + 26)；空间复杂度：O(26) = O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minSteps(string s, string t) {  // s、t：两个待比较的字符串
        vector<int> cnt(26);  // 26 个小写字母的差值计数数组，初始全为 0
        for (char& c : s) ++cnt[c - 'a'];  // s 中出现的字母计数加一
        for (char& c : t) --cnt[c - 'a'];  // t 中出现的字母计数减一，最终 cnt 表示 s 相对 t 的净多出次数
        int ans = 0;  // 累加所需的最小操作步数
        for (int& v : cnt) ans += abs(v);  // 多出的要删除、缺少的要补充，两边步数都是 |差值|，故直接累加绝对值
        return ans;  // 返回总步数
    }  // 方法结束
};  // 类定义结束