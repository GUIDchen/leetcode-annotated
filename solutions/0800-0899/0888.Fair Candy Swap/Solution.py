# 题目：888. 公平的糖果交换（Fair Candy Swap）
# 思路：交换后总量相等要求 a - b = (sum(alice) - sum(bob)) / 2；枚举 Alice 的糖果 a，在 Bob 的集合里查 b = a - diff。
# 时间复杂度：O(n + m)，求和、建集合、遍历各一次；空间复杂度：O(m)，Bob 糖果值的集合。
class Solution:  # LeetCode 约定的题解类
    def fairCandySwap(self, aliceSizes: List[int], bobSizes: List[int]) -> List[int]:  # aliceSizes / bobSizes 分别是两人每颗糖的大小
        diff = (sum(aliceSizes) - sum(bobSizes)) >> 1  # 总量差的一半：交换后必须满足 a - b = diff，右移一位即除以 2
        s = set(bobSizes)  # 把 Bob 的糖果大小放进集合，便于 O(1) 判断是否存在
        for a in aliceSizes:  # 枚举 Alice 要换出的那颗糖 a
            if (b := (a - diff)) in s:  # 海象运算符先算出所需的 b = a - diff，再判断 Bob 是否拥有它；有则直接返回这对答案（题目保证有解）
                return [a, b]  # 返回换出的 a 与换入的 b，题目保证一定有解
