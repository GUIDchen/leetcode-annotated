// 题目：340. 至多包含 K 个不同字符的最长子串（Longest Substring with At Most K Distinct Characters）
// 核心思路：滑动窗口 + 哈希计数，右边界不断右移，窗口内不同字符数超过 k 时把左边界右移一格收缩。
// 时间复杂度：O(n)，两个指针都只前进；空间复杂度：O(min(n, σ))，哈希表最多保存 k+1 种字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int lengthOfLongestSubstringKDistinct(string s, int k) {  // s 是输入字符串，k 是允许的不同字符数上限，返回最长子串长度
        unordered_map<char, int> cnt;  // 哈希表：窗口内每个字符 → 出现次数，用 size() 代表不同字符数
        int l = 0;  // 滑动窗口的左边界，初始在 0
        for (char& c : s) {  // 右边界随遍历右移，把当前字符纳入窗口
            ++cnt[c];  // 当前字符的计数加一
            if (cnt.size() > k) {  // 窗口内不同字符数超过 k，需要从左侧收缩
                if (--cnt[s[l]] == 0) {  // 左边界字符计数减一；恰好减到 0 说明该字符已完全离开窗口
                    cnt.erase(s[l]);  // 从哈希表中删除该键，保证 cnt.size() 如实反映不同字符数
                }  // if 分支结束
                ++l;  // 左边界右移一格，窗口收缩（每次只收缩一格就能恢复合法）
            }  // if 分支结束
        }  // for 循环结束
        return s.size() - l;  // 循环结束时 l 是最长合法窗口的左边界，长度等于 n - l
    }  // 方法结束
};  // 类定义结束