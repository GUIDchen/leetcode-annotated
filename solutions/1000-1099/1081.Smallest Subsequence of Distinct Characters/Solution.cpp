// 题目：1081. 不同字符的最小子序列（Smallest Subsequence of Distinct Characters）
// 思路：先记录每个字符在原串中最后出现的位置，再用单调栈构造答案：当前字符若已在栈中则跳过；否则不断把「比当前字符大、且后面还会再出现」的栈顶弹出，保证字典序最小并能去重。
// 时间复杂度：O(n)，每个字符最多入栈、出栈各一次；空间复杂度：O(1)，栈与标记最多只含 26 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string smallestSubsequence(string s) {  // s 是原字符串（全小写字母）
        int n = s.size();  // 原串长度
        int last[26] = {0};  // last[c] 记录字符 c 在原串中最后一次出现的下标
        for (int i = 0; i < n; ++i) {  // 从左到右扫描一遍
            last[s[i] - 'a'] = i;  // 用当前下标不断覆盖，循环结束后即为最后出现位置
        }
        string ans;  // 单调栈：保存当前构造出的、字典序尽量小的子序列
        int mask = 0;  // 位掩码，第 c 位为 1 表示字符 c 已经在栈中
        for (int i = 0; i < n; ++i) {  // 从左到右逐个处理原串字符
            char c = s[i];  // 当前字符
            if ((mask >> (c - 'a')) & 1) {  // 该字符已经在栈中，重复加入会破坏「每个字符恰好一次」
                continue;  // 直接跳过这个字符
            }
            while (!ans.empty() && ans.back() > c && last[ans.back() - 'a'] > i) {  // 栈顶更大且后面还会再次出现，就可以先弹掉换成更小的 c
                mask ^= 1 << (ans.back() - 'a');  // 清掉被弹出字符的已用标记
                ans.pop_back();  // 弹出栈顶字符
            }
            ans.push_back(c);  // 把当前字符压入栈
            mask |= 1 << (c - 'a');  // 标记该字符已进入答案
        }
        return ans;  // 栈内字符顺序即字典序最小的不同字符子序列
    }
};