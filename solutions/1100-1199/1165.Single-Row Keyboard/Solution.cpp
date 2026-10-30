// 题目：1165. 单行键盘（Single-Row Keyboard）
// 思路：先建立「字母 → 键盘下标」映射，再逐个字符累加手指移动距离。
// 时间复杂度：O(|keyboard| + |word|)；空间复杂度：O(1)（26 个字母的映射表）。
class Solution {  // LeetCode 题解类
public:  // 解题方法对外公开
    int calculateTime(string keyboard, string word) {  // keyboard 是一行键盘的字母顺序，word 是要敲出的字符串
        int pos[26];  // pos[c] 记录字母 c 在键盘上的下标
        for (int i = 0; i < 26; ++i) {  // 遍历键盘的 26 个位置
            pos[keyboard[i] - 'a'] = i;  // 建立「字母 → 键盘下标」的映射
        }  // 结束映射建立
        int ans = 0, i = 0;  // ans 累计手指移动距离；i 是手指当前下标（初始在 0）
        for (char& c : word) {  // 逐个敲击字符
            int j = pos[c - 'a'];  // 目标字符在键盘上的下标
            ans += abs(i - j);  // 累加手指从 i 到 j 的移动距离
            i = j;  // 手指停在新位置
        }  // 结束字符遍历
        return ans;  // 返回总移动距离
    }  // 方法结束
};  // 类定义结束