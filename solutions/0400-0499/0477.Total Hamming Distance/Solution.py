# 题目：477. 汉明距离总和（Total Hamming Distance）
# 思路：逐位统计。第 i 位上若有 a 个数为 1、b 个数为 0，则这一位对总距离的贡献就是 a*b（一 0 一 1 的配对都会产生一次差异）。
# 时间复杂度：O(32n)，即 O(n)，每个数只被扫描 32 次；空间复杂度：O(1)，只用若干计数变量。
class Solution:  # LeetCode 约定的题解类
    def totalHammingDistance(self, nums: List[int]) -> int:  # nums 是给定的整数数组，返回两两汉明距离之和
        ans, n = 0, len(nums)  # ans 累加答案，n 是元素个数
        for i in range(32):  # 依次处理二进制的第 0~31 位
            a = sum(x >> i & 1 for x in nums)  # 统计所有数字在当前位上为 1 的个数
            b = n - a  # b 是当前位上 0 的个数
            ans += a * b  # 这一位的贡献 = 1 的个数 × 0 的个数
        return ans  # 32 位贡献之和即总汉明距离
