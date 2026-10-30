# 题目：3307. 找出第 K 个字符 II（Find the K-th Character in String Game II）
# 思路：先翻倍求出覆盖下标 k 需要的最少操作次数，再从最终长度逆推：k 位于后半段时映射回前半段，并按该次操作是否为「复制并加一」累加偏移。
# 复杂度：时间 O(log k)，翻倍与回溯各 O(log k) 步；空间 O(1)，只用几个整数变量。
class Solution:  # LeetCode 约定的题解类
    def kthCharacter(self, k: int, operations: List[int]) -> str:  # k 为 1 起始的目标下标，operations[i] 表示第 i 次操作是否为「复制并整体加一」
        n, i = 1, 0  # n：当前串长（初始为 1）；i：已执行的操作次数
        while n < k:  # 翻倍直到长度覆盖第 k 个字符
            n *= 2  # 每次操作长度翻倍
            i += 1  # 操作次数加一
        d = 0  # d：目标字符相对 'a' 的累计偏移量
        while n > 1:  # 从最终长度逐层回溯到长度 1
            if k > n // 2:  # 落在后半段，说明由前半段复制（可能再整体加一）而来
                k -= n // 2  # 换算回上一轮前半段中的对应位置
                d += operations[i - 1]  # 该次操作若是「复制并加一」，偏移量加一
            n //= 2  # 长度回退一半
            i -= 1  # 操作下标同步回退
        return chr(d % 26 + ord("a"))  # 偏移对 26 取模实现字母循环，再转成字符
