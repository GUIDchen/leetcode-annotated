# 题目：3185. 构成整天的下标对数目 II（Count Pairs That Form a Complete Day II）
# 思路：与第 I 题相同，用 Counter 记录已出现余数，遍历时累加补数余数的出现次数。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，余数只有 24 种。
class Solution:  # LeetCode 约定的题解类
    def countCompleteDayPairs(self, hours: List[int]) -> int:  # hours 是耗时列表，返回相加为 24 整数倍的下标对数目
        cnt = Counter()  # 计数器：键是耗时模 24 的余数，值是已出现的次数
        ans = 0  # 满足条件的下标对总数（Python 整数天然无溢出）
        for x in hours:  # 顺序遍历，保证每个下标对只在后一个元素处被统计一次
            ans += cnt[(24 - (x % 24)) % 24]  # 补数余数在表中已出现的次数，就是本次新增的合法对数
            cnt[x % 24] += 1  # 把当前耗时的余数计入表，供后面的元素配对
        return ans  # 返回总对数
