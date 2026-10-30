# 题目：1456. 定长子串中元音的最大数目（Maximum Number of Vowels in a Substring of Given Length）
# 思路：滑动窗口，先算出首个长度 k 窗口内的元音数，之后每右移一格就加上新字符、减去离开窗口的字符，边走边更新最大值。
# 时间复杂度：O(n)，每个字符只被进出窗口各一次；空间复杂度：O(1)，只有常数个额外变量（元音集合大小固定为 5）。
class Solution:  # LeetCode 约定的题解类
    def maxVowels(self, s: str, k: int) -> int:  # s：原字符串；k：固定窗口长度
        vowels = set("aeiou")  # 元音集合，使 in 判断为 O(1)
        ans = cnt = sum(c in vowels for c in s[:k])  # sum 统计首个窗口里的元音数；ans 与 cnt 同时初始化为它
        for i in range(k, len(s)):  # i 是窗口右端点，从 k 开始逐位右移
            cnt += int(s[i] in vowels) - int(s[i - k] in vowels)  # int(True)=1、int(False)=0，加上新字符的贡献再减去移出窗口字符的贡献
            ans = max(ans, cnt)  # 更新历史最大元音数
        return ans  # 返回长度 k 子串中元音数的最大值
