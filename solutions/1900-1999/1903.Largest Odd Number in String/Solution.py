# 题目：1903. 字符串中的最大奇数（Largest Odd Number in String）
# 思路：数字是否是奇数只看末位，从右往左找到第一个奇数数字，以它结尾的前缀就是最大值。
# 时间复杂度：O(n)，最坏扫描整个字符串；空间复杂度：O(1)，切片结果除外只用常数空间。
class Solution:  # LeetCode 约定的题解类
    def largestOddNumber(self, num: str) -> str:  # num：只含数字字符的字符串
        for i in range(len(num) - 1, -1, -1):  # 从右往左扫描，找到的奇数位越靠右，前缀表示的数值越大
            if (int(num[i]) & 1) == 1:  # 当前位是奇数数字时，整个前缀就是奇数
                return num[: i + 1]  # 切出以 i 结尾的前缀，它就是最大的奇数
        return ''  # 没有奇数数字，返回空串
