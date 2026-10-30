# 题目：1304. 和为零的 N 个不同整数（Find N Unique Integers Sum up to Zero）
# 思路：成对追加 i 与 -i 相互抵消；若 n 为奇数，最后再补一个 0。
# 时间复杂度：O(n)，每个数只追加一次；空间复杂度：O(1)，除返回列表外只用常数变量。
class Solution:  # LeetCode 约定的题解类
    def sumZero(self, n: int) -> List[int]:  # n：需要生成的整数个数
        ans = []  # 结果列表
        for i in range(n >> 1):  # n >> 1 即 n // 2，成对生成整数
            ans.append(i + 1)  # 追加正数 i+1
            ans.append(-(i + 1))  # 追加对应的负数，与正数相互抵消
        if n & 1:  # n 为奇数时，两两配对会多出一位
            ans.append(0)  # 补一个 0，不影响总和
        return ans  # 返回和为 0 的 n 个互不相同整数
