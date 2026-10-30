# 题目：2829. k-avoiding 数组的最小总和（Determine the Minimum Sum of a k-avoiding Array）
# 思路：贪心，从 1 开始按升序尝试每个数能取就取；取走 i 之后立刻把搭档 k-i 放进禁用集合，保证之后不会再选出和为 k 的两个数。
# 时间复杂度：O(n)，每轮至少选出一个数并让 i 前进；空间复杂度：O(n)，禁用集合最多存 n 个数。
class Solution:  # LeetCode 约定的题解类
    def minimumSum(self, n: int, k: int) -> int:  # n：需要选出几个数；k：禁止出现和为 k 的两个数；返回满足条件的 n 个数的最小总和
        s, i = 0, 1  # s 是已经选出的数之和，i 是当前尝试的最小候选数，从 1 开始
        vis = set()  # 禁用集合：存放当前不能再选的数，被选走的数则通过 i 自增直接跳过
        for _ in range(n):  # 一共要挑 n 个数，循环次数与具体取值无关
            while i in vis:  # 跳过已被放进禁用集合的候选
                i += 1  # 换下一个候选数
            vis.add(k - i)  # 把 i 的搭档记入禁用集合，之后不能选它，否则两数之和恰为 k；k - i 可能为 0 或负数，但 i 只增不减且始终为正，不会再次访问到，因此无害
            s += i  # 把 i 计入总和
            i += 1  # 候选数前移，i 本身已被选走，保证不重复选
        return s  # 返回这 n 个数的最小总和
