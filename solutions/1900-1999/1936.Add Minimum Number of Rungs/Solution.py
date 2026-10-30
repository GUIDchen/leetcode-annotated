# 题目：1936. 新增的最少台阶数（Add Minimum Number of Rungs）
# 思路：相邻高度差 gap 超过 dist 时，需要插入 (gap-1)//dist 级新台阶，逐段累加即可。
# 时间复杂度：O(n)；空间复杂度：O(n)，补上地面 0 之后的新列表。
class Solution:  # LeetCode 约定的题解类
    def addRungs(self, rungs: List[int], dist: int) -> int:  # 返回到达顶端所需新增的最少台阶数
        rungs = [0] + rungs  # 把地面高度 0 补到最前面，统一成「相邻两高度差」的同一套计算
        return sum((b - a - 1) // dist for a, b in pairwise(rungs))  # pairwise 逐对取出相邻高度，整除把「最后一步不算」的边界一并处理掉后求和
