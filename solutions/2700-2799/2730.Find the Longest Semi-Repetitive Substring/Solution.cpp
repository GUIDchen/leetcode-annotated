// 题目：2730. 找到最长的半重复子字符串（Find the Longest Semi-Repetitive Substring）
// 思路：滑动窗口 [j, i]，用 cnt 记录窗口内相邻相等对的数量，超过 1 就右移左端点收缩。
// 时间复杂度：O(n)，左右指针各只前进一次；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestSemiRepetitiveSubstring(string s) {  // 返回最长的半重复子串长度
        int ans = 1, n = s.size();  // ans 记录最长长度（单个字符也满足），n 为字符串长度
        for (int i = 1, j = 0, cnt = 0; i < n; ++i) {  // 滑动窗口：[j, i] 是当前半重复子串，cnt 记录窗口内相邻相等对的数量
            cnt += s[i] == s[i - 1] ? 1 : 0;  // 新加入的 s[i] 如果与左邻相等，就多一个相邻相等对
            for (; cnt > 1; ++j) {  // 半重复要求相等对至多 1 个，超了就不断右移左端点收缩窗口
                cnt -= s[j] == s[j + 1] ? 1 : 0;  // 移出 s[j] 时，若它与 s[j+1] 相等，则相应减少一个相等对
            }
            ans = max(ans, i - j + 1);  // 用当前窗口长度更新答案
        }
        return ans;  // 返回最长半重复子串长度
    }
};