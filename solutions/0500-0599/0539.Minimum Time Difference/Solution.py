# 题目：539. 最小时间差（Minimum Time Difference）
# 思路：把每个 "HH:MM" 转成当天的分钟数并排序，最小差值只可能出现在相邻两项之间；再把首项 +1440 接到末尾以处理跨零点的环形差值。
# 时间复杂度：O(n log n)，瓶颈是排序；空间复杂度：O(n)，存放转换后的分钟数列表。
class Solution:  # LeetCode 约定的题解类
    def findMinDifference(self, timePoints: List[str]) -> int:  # timePoints 是若干 "HH:MM" 形式的时间点，返回两两之间的最小分钟差
        if len(timePoints) > 1440:  # 一天只有 1440 分钟：超过 1440 个时间点必有重复，最小差为 0
            return 0  # 存在重复时间点，直接返回 0
        nums = sorted(int(x[:2]) * 60 + int(x[3:]) for x in timePoints)  # x[:2] 是小时、x[3:] 是分钟（下标 2 处是冒号），换算成从 00:00 起算的分钟数并排序
        nums.append(nums[0] + 1440)  # 环形处理：末尾补上「首项 + 一天的分钟数」，表示跨过零点的那个时间点
        return min(b - a for a, b in pairwise(nums))  # pairwise 取相邻两项 (a, b)，求最小差值；排序后最小差必然出现在相邻两项之间
