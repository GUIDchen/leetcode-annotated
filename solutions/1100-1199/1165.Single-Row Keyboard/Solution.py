# 题目：1165. 单行键盘（Single-Row Keyboard）
# 思路：先建立「字母 → 键盘下标」映射，再逐个字符累加手指移动距离。
# 时间复杂度：O(|keyboard| + |word|)；空间复杂度：O(1)（26 个字母的映射表）。
class Solution:  # LeetCode 约定的题解类
    def calculateTime(self, keyboard: str, word: str) -> int:  # keyboard 是一行键盘的字母顺序，word 是要敲出的字符串
        pos = {c: i for i, c in enumerate(keyboard)}  # 字母 → 键盘下标的映射
        ans = i = 0  # ans 是总移动距离；i 是手指当前下标（初始在 0）
        for c in word:  # 逐个敲击字符
            ans += abs(pos[c] - i)  # 累加手指从 i 移动到目标位置的距离
            i = pos[c]  # 手指停在新位置
        return ans  # 返回总移动距离
