# 题目：2358. 分组的最大数量（Maximum Number of Groups Entering a Competition）
# 思路：成绩无关，只需凑人数；x 组至少需要 x*(x+1)/2 人，用 bisect_right 在 0..n 上二分最大的 x。
# 时间复杂度：O(log n)，二分找上界；空间复杂度：O(1)，range 只是惰性序列。
class Solution:  # LeetCode 约定的题解类
    def maximumGroups(self, grades: List[int]) -> int:  # grades：学生成绩数组；返回最多可以分成的组数
        n = len(grades)  # n 为学生总数，分组只看人数，成绩本身不参与计算
        return bisect_right(range(n + 1), n * 2, key=lambda x: x * x + x) - 1  # key=x*x+x 单调递增，bisect_right 找到第一个超过 2n 的位置，减 1 即最大可行组数
