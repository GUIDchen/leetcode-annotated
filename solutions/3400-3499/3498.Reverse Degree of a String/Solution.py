# 题目：3498. 字符串的反转度（Reverse Degree of a String）
# 思路：正向下标 i（从 1 开始）乘以字母的反转度 26 - (c - 'a')，逐字符累加得到总和。
# 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def reverseDegree(self, s: str) -> int:  # s：输入字符串，返回它的反转度
        ans = 0  # ans 累加每个字符的「下标 × 反转度」
        for i, c in enumerate(s, 1):  # 枚举下标 i（从 1 开始）与字符 c
            x = 26 - (ord(c) - ord("a"))  # 字母越靠前反转度越大：'a' 得 26，'z' 得 1
            ans += i * x  # 第 i 个字符的贡献为 i 乘反转度 x
        return ans  # 返回总反转度
