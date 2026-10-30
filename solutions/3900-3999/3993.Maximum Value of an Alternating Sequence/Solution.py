# 题目：3993. Maximum Value of an Alternating Sequence（3993. 交替数列的最大元素）
# 核心思路：交替序列的每个峰顶相对上一个峰顶最多抬高 (m-1)——峰顶至多是前一个谷 + m，而谷顶多比峰低 1；长度为 n 的序列有 n//2 个峰，故答案为 s + (n//2)·(m-1) + 1，最后的 +1 对应末段由谷抬到峰的抬升。
# 复杂度：时间 O(1)，空间 O(1)。
class Solution:  # 定义题解类
    def maximumValue(self, n: int, s: int, m: int) -> int:  # 返回长度为 n、首项为 s、相邻差不超过 m 的交替序列中可能的最大元素
        if n == 1:  # 长度为 1 时序列只有首项
            return s  # 最大元素就是 s 本身
        return s + n // 2 * (m - 1) + 1  # n//2 个峰顶各最多比上一个峰顶高 (m-1)，再补上末段的 1
