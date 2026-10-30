# 题目：1750. 删除字符串两端相同字符后的最短长度（Minimum Length of String After Deleting Similar Ends）
# 核心思路：双指针 i、j 从两端夹逼，两端字符相同时先把左右各自整段相同字符跳完，再让 i 右移、j 左移各删掉一段，直到两端不同或指针相遇。
# 时间复杂度：O(n)，两个指针合计最多扫描整个字符串；空间复杂度：O(1)，只使用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumLength(self, s: str) -> int:  # s 是输入字符串，返回删除两端相同字符后能得到的最短长度
        i, j = 0, len(s) - 1  # i 是左端点，j 是右端点，初始指向字符串两端
        while i < j and s[i] == s[j]:  # 两端字符相同才允许继续删除
            while i + 1 < j and s[i] == s[i + 1]:  # 跳过左端与 s[i] 相同的整段字符，只停在最后一个相同字符上
                i += 1  # 左指针右移一格
            while i < j - 1 and s[j - 1] == s[j]:  # 跳过右端与 s[j] 相同的整段字符，只停在第一个相同字符上
                j -= 1  # 右指针左移一格
            i, j = i + 1, j - 1  # 两端各删除一整段后同时向中间收缩
        return max(0, j - i + 1)  # 指针交叉时长度为负，用 0 兜底
