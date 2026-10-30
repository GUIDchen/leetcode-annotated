# 题目：1957. 删除字符使字符串变好（Delete Characters to Make Fancy String）
# 思路：一次遍历贪心保留字符，只有当它会造成末尾三连相同时才丢弃。
# 时间复杂度：O(n)，每个字符看一次；空间复杂度：O(n)，答案列表最多存 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def makeFancyString(self, s: str) -> str:  # s 为原字符串，返回删除若干字符后的好字符串
        ans = []  # 用列表收集字符，避免反复做字符串拼接带来的 O(n^2) 开销
        for i, c in enumerate(s):  # enumerate 同时取得下标 i 与字符 c
            if i < 2 or c != s[i - 1] or c != s[i - 2]:  # 前两个字符一定保留；之后要求与前面两个字符都不同
                ans.append(c)  # 该字符不会造成三连相同，加入答案
        return "".join(ans)  # 拼接成字符串返回
