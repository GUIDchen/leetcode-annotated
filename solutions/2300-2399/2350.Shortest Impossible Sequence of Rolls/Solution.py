# 题目：2350. 不可能得到的最短骰子序列（Shortest Impossible Sequence of Rolls）
# 思路：顺序扫描，用集合收集当前段出现过的点数；一旦集合凑满 1..k 就把答案加一并清空集合。
# 时间复杂度：O(n)，只遍历一次；空间复杂度：O(k)，集合最多保存 k 个不同点数。
class Solution:  # LeetCode 约定的题解类
    def shortestSequence(self, rolls: List[int], k: int) -> int:  # rolls：骰子序列；k：骰子面数
        ans = 1  # 答案初值为 1：长度为 1 的序列至少有一种可能拿不到
        s = set()  # 记录当前段里已经出现过的点数
        for v in rolls:  # 顺序扫描每一次掷出的结果
            s.add(v)  # 把当前点数记入本段
            if len(s) == k:  # 本段已集齐全部 k 种点数
                ans += 1  # 可构造的长度上界加一
                s.clear()  # 清空集合，开始统计下一段
        return ans  # 完整段数 + 1，即不可能得到的最短序列长度
