# 题目：2390. 从字符串中移除星号（Removing Stars From a String）
# 思路：用列表模拟栈；遇到普通字符就入栈，遇到 '*' 就弹出栈顶，等价于删除它左边最近的未被删除字符。
# 时间复杂度：O(n)，每个字符最多进出栈一次；空间复杂度：O(n)，栈最多保存 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def removeStars(self, s: str) -> str:  # s：只含小写字母和 '*' 的字符串
        ans = []  # 用列表作为栈，保存已保留的字符
        for c in s:  # 从左到右扫描每个字符
            if c == '*':  # 星号：删除左边最近的未被删除字符
                ans.pop()  # 弹出栈顶，即被这个星号删掉的字符（题目保证不会弹空）
            else:  # 普通字母：保留它
                ans.append(c)  # 压入栈顶
        return ''.join(ans)  # 栈内剩余字符按原顺序拼接即为答案
