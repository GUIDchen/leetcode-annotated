# 题目：1090. 受标签影响的最大值（Largest Values From Labels）
# 思路：把所有 (值, 标签) 按值从大到小排序后贪心选取，用 Counter 记录每个标签已选次数，未超过 useLimit 就选，选满 numWanted 个立即停止。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，排序结果与标签计数表。
class Solution:  # LeetCode 约定的题解类
    def largestValsFromLabels(  # values 与 labels 一一对应，numWanted 为最多选几个，useLimit 为每个标签最多选几次
        self, values: List[int], labels: List[int], numWanted: int, useLimit: int
    ) -> int:
        ans = num = 0  # ans 累加所选值之和，num 记录已选元素个数
        cnt = Counter()  # Counter 记录每个标签已被选中的次数
        for v, l in sorted(zip(values, labels), reverse=True):  # 把值与标签配对后按元组降序排列，从最大值开始贪心
            if cnt[l] < useLimit:  # 该标签的配额还没用完
                cnt[l] += 1  # 该标签已选次数加一
                num += 1  # 已选个数加一
                ans += v  # 累加当前值到答案
                if num == numWanted:  # 已经选够题目要求的个数
                    break  # 提前结束：后面的值不会再让总和变大
        return ans  # 返回所选值之和的最大值
