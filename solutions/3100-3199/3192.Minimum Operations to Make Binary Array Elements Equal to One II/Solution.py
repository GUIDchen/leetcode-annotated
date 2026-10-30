# 题目：3192. 使二进制数组全部等于 1 的最少操作次数 II（Minimum Operations to Make Binary Array Elements Equal to One II）
# 思路：每次操作翻转的是下标 i 开始的后缀，所以用一个标记 v 记录至今累积的后缀翻转次数奇偶性，逐位判断真实值。
# 时间复杂度：O(n)，遍历数组一次；空间复杂度：O(1)，只使用 ans 与 v 两个整数。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int]) -> int:  # nums：0/1 数组，返回最少操作次数
        ans = v = 0  # ans 记录操作次数；v 记录后缀翻转的累积奇偶性，0 表示未翻、1 表示已翻
        for x in nums:  # 从左到右遍历每个元素
            x ^= v  # 异或累积标记，还原出这个位置的当前真实值
            if x == 0:  # 真实值为 0，需要以当前位置为起点翻转一次后缀
                ans += 1  # 操作次数加一
                v ^= 1  # 后缀翻转标记取反，后续元素都要按相反状态读取
        return ans  # 返回最少操作次数
