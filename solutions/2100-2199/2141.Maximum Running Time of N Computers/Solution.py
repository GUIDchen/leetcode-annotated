# 题目：2141. 同时运行 N 台电脑的最长时间（Maximum Running Time of N Computers）
# 思路：二分答案时长 mid，每块电池最多贡献 min(电量, mid)，若所有贡献之和 >= n * mid 说明 mid 可行。
# 时间复杂度：O(m log(sum))，m 为电池数，sum 为总电量；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def maxRunTime(self, n: int, batteries: List[int]) -> int:  # n：电脑台数；batteries：每块电池的电量
        l, r = 0, sum(batteries)  # 二分下界 0，上界取总电量（所有电脑总时长不可能超过总电量）
        while l < r:  # 整数二分：区间非空就继续
            mid = (l + r + 1) >> 1  # 中点向上取整，配合下面的 l = mid 避免死循环
            if sum(min(x, mid) for x in batteries) >= n * mid:  # 每块电池最多贡献 mid 小时，总贡献够 n 台电脑跑 mid 小时即可行
                l = mid  # 抬高下界
            else:  # 总电量不足，说明 mid 偏大
                r = mid - 1  # 上界收缩到 mid-1
        return l  # l 就是最大可行时长
