# 题目：779. 第K个语法符号（K-th Symbol in Grammar）
# 思路：第 n 行的前半段等于第 n-1 行，后半段是前半段的逐位取反；判断 k 落在哪一半，后半段就把对应位置的结果异或 1。
# 时间复杂度：O(n)，每层把问题规模减半；空间复杂度：O(n)，递归调用栈深度为 n。
class Solution:  # LeetCode 约定的题解类
    def kthGrammar(self, n: int, k: int) -> int:  # n：行号（从 1 开始）；k：该行第 k 个字符（从 1 开始）
        if n == 1:  # 第一行只有单个 0，作为递归出口
            return 0  # 直接返回 0
        if k <= (1 << (n - 2)):  # 前半段长度为 2^(n-2)，k 落在前半段时答案与第 n-1 行第 k 位相同
            return self.kthGrammar(n - 1, k)  # 递归到上一行的同一个位置
        return self.kthGrammar(n - 1, k - (1 << (n - 2))) ^ 1  # 落在后半段：先映射到前半段的对应位置，再把结果异或 1 取反
