# 题目：1180. 统计只含单一字母的子串（Count Substrings with Only One Distinct Letter）
# 思路：扫描出每一段连续相同字母，长度为 len 的段内只含单一字母的子串数为 len*(len+1)//2，累加即答案。
# 时间复杂度：O(n)，每个下标只被访问常数次；空间复杂度：O(1)，只用几个计数变量。
class Solution:  # LeetCode 约定的题解类
    def countLetters(self, s: str) -> int:  # s 为输入字符串
        n = len(s)  # 字符串长度
        i = ans = 0  # i 为当前连续段起点，ans 累计答案
        while i < n:  # 按段推进，直到扫描完整串
            j = i  # j 从段起点出发，寻找当前段的右开边界
            while j < n and s[j] == s[i]:  # 向右扩展，直到越界或字母发生变化
                j += 1  # 右边界后移
            ans += (1 + j - i) * (j - i) // 2  # 长度 len=j-i 的段贡献 len*(len+1)//2 个子串，用等差求和公式替代逐个枚举
            i = j  # 直接跳到下一段开头，段内元素不再重复访问
        return ans  # 返回总数
