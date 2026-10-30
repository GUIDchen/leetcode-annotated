# 题目：2561. 重排水果（Rearranging Fruits）
# 核心思路：统计两筐各类水果的净差值，奇差值直接无解；把需要转移的水果值收集排序，每个取「直接交换」与「用全局最小值中转两次」的较小代价。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，存放计数器与待交换水果值。
class Solution:  # LeetCode 约定的题解类
    def minCost(self, basket1: List[int], basket2: List[int]) -> int:  # basket1、basket2：两个等长果篮
        cnt = Counter()  # 计数器：键是水果值，值是 basket1 相对 basket2 的净多出数量
        for a, b in zip(basket1, basket2):  # 同步遍历两筐的同位置元素
            cnt[a] += 1  # 第一筐出现，计数加一
            cnt[b] -= 1  # 第二筐出现，计数减一
        mi = min(cnt)  # 计数器的键就是出现过的最小水果值，用作中转的最小代价
        nums = []  # 收集需要转移的水果值
        for x, v in cnt.items():  # 遍历每种水果值的净差值
            if v % 2:  # 净差值为奇数说明总个数为奇数，无法平分
                return -1  # 无解，返回 -1
            nums.extend([x] * (abs(v) // 2))  # 多出 |v| 个，只把其中一半记入待交换列表
        nums.sort()  # 升序排序，优先使用便宜的水果交换
        m = len(nums) // 2  # 每个交换消掉两个元素，共需 m 次交换
        return sum(min(x, mi * 2) for x in nums[:m])  # 每次取「直接交换 x」与「两倍最小值中转」中的较小代价求和
