# 题目：2761. 和等于目标值的质数对（Prime Pairs With Target Sum）
# 思路：先用埃氏筛标记 [2, n - 1] 内的质数，再在 x <= n // 2 的范围枚举 x，检查 n - x 是否也是质数，是就记录 [x, n - x]。
# 时间复杂度：O(n log log n)，筛法加上 O(n) 的枚举；空间复杂度：O(n)，需要一个长度 n 的质数标记数组。
class Solution:  # LeetCode 约定的题解类
    def findPrimePairs(self, n: int) -> List[List[int]]:  # n 是目标和，返回所有和为 n 的质数对
        primes = [True] * n  # 长度 n 的布尔表，下标 0 到 n - 1，先全部当作质数
        for i in range(2, n):  # 埃氏筛：i 从 2 枚举到 n - 1
            if primes[i]:  # i 仍被标记为质数，说明它没被更小的质数筛掉
                for j in range(i + i, n, i):  # 从 2 * i 开始，步长 i，遍历 i 的所有倍数
                    primes[j] = False  # 倍数 i * k 一定不是质数，标记成合数
        ans = []  # ans 收集所有满足 x + y = n 的质数对
        for x in range(2, n // 2 + 1):  # x 只枚举到 n // 2，避免把 (x, y) 和 (y, x) 重复统计
            y = n - x  # 另一个加数 y 由 n - x 唯一确定
            if primes[x] and primes[y]:  # x >= 2 且 y <= n - 2，下标安全；再判断两个加数是否都是质数
                ans.append([x, y])  # 找到一组合法质数对，按 x 递增的顺序加入答案
        return ans  # 返回所有质数对
