// 题目：242. 有效的字母异位词（Valid Anagram）
// 思路：长度不同直接判否；否则用长度 26 的计数表，s 的字符加一、t 的字符减一，最后检查计数是否全为 0。
// 时间复杂度：O(n)，只遍历两串各一次；空间复杂度：O(1)，计数表固定 26 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isAnagram(string s, string t) {  // s、t：待比较的两个字符串
        if (s.size() != t.size()) {  // 长度不同一定不是异位词
            return false;  // 直接返回失败
        }
        vector<int> cnt(26);  // 26 个小写字母的计数差表，初值全为 0
        for (int i = 0; i < s.size(); ++i) {  // 一次遍历同时统计两个串
            ++cnt[s[i] - 'a'];  // s 中该字符的计数加一
            --cnt[t[i] - 'a'];  // t 中该字符的计数减一
        }
        return all_of(cnt.begin(), cnt.end(), [](int x) { return x == 0; });  // 所有计数都归零说明两串字符频次完全相同
    }
};  // 题解类定义结束