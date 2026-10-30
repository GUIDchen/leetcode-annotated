# 题目：2171. 拿出最少数目的魔法豆（Removing Minimum Number of Magic Beans）
# 思路：排序后枚举最终统一保留的数量 x = beans[i]，代价为总和减去 x*(n-i)，取所有方案的最小值。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，只用了几个标量（生成器不缓存结果）。
class Solution:  # LeetCode 约定的题解类
    def minimumRemoval(self, beans: List[int]) -> int:  # beans 是每袋豆子的数量；返回拿出的最少豆子数
        beans.sort()  # 升序排序，使 beans[i] 可以当作「保留下来的统一数量」
        s, n = sum(beans), len(beans)  # s 是豆子总数，n 是袋子个数
        return min(s - x * (n - i) for i, x in enumerate(beans))  # 生成器表达式枚举每个 i：保留的豆子为 x*(n-i) 个，其余 s - x*(n-i) 个都要拿走
