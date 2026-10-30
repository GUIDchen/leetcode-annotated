// 题目：3. 无重复字符的最长子串（Longest Substring Without Repeating Characters）
// 思路：滑动窗口 + 计数数组，右指针逐个入窗；若某字符出现两次，就移动左指针把重复字符挤出去。
// 时间复杂度：O(n)，每个字符最多进出窗口各一次；空间复杂度：O(1)，计数器大小固定为 128。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int lengthOfLongestSubstring(string s) {  // s 为输入字符串，返回最长无重复子串长度
        int cnt[128]{};  // 计数器，值初始化为 0；下标是字符的 ASCII 码
        int ans = 0, n = s.size();  // ans 保存最大窗口长度，n 为字符串长度
        for (int l = 0, r = 0; r < n; ++r) {  // l 为左边界，r 为右边界，右指针逐位右移扩张
            ++cnt[s[r]];  // 新字符进入窗口，计数加一
            while (cnt[s[r]] > 1) {  // 窗口内该字符重复，收缩左边界直到不重复
                --cnt[s[l++]];  // 左边界字符出窗后计数减一，左指针再右移
            }
            ans = max(ans, r - l + 1);  // 用当前窗口长度更新答案
        }
        return ans;  // 返回最大长度
    }
};
