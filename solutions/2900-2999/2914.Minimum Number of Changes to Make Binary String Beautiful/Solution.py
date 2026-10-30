# 题目：2914. 使二进制字符串变美丽的最少修改次数（Minimum Number of Changes to Make Binary String Beautiful）
# 思路：按长度 2 分块，每块内两个字符不同就要改一个，各块独立，答案即这些块的个数。
# 时间复杂度：O(n)，只扫一遍；空间复杂度：O(1)，生成器不额外占空间。
class Solution:  # LeetCode 约定的题解类
    def minChanges(self, s: str) -> int:  # s 长度保证为偶数；返回『00/11』分块所需的最少修改次数
        return sum(s[i] != s[i - 1] for i in range(1, len(s), 2))  # 用步长 2 取每组的第二个下标，布尔值相加即为不相等的组数
