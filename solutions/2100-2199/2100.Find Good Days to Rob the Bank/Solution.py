# 题目：2100. 适合野炊的日子（Find Good Days to Rob the Bank）
# 思路：两遍递推求出每个位置向左、向右的「非递增连续天数」，再筛出左右都不少于 time 的日子。
# 时间复杂度：O(n)，三次线性扫描；空间复杂度：O(n)，left 与 right 两个计数数组。
class Solution:  # LeetCode 约定的题解类
    def goodDaysToRobBank(self, security: List[int], time: int) -> List[int]:  # security 是每天安保人数，time 是要求的连续天数
        n = len(security)  # 总天数
        if n <= time * 2:  # 天数不够左右各分 time 天，不可能有合法日子
            return []  # 直接返回空列表
        left, right = [0] * n, [0] * n  # left[i] / right[i] 分别记录以 i 结尾向左、以 i 开头向右的非递增天数
        for i in range(1, n):  # 从左往右递推左侧天数
            if security[i] <= security[i - 1]:  # 今天不多于昨天，才允许继续向左延伸
                left[i] = left[i - 1] + 1  # 在昨天的结果上加一
        for i in range(n - 2, -1, -1):  # 从右往左递推右侧天数
            if security[i] <= security[i + 1]:  # 今天不多于明天，才允许继续向右延伸
                right[i] = right[i + 1] + 1  # 在后一天的结果上加一
        return [i for i in range(n) if time <= min(left[i], right[i])]  # 列表推导筛出左右天数都不少于 time 的所有下标
