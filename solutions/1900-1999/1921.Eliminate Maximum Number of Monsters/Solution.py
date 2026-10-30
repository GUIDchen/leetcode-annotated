# 题目：1921. 消灭怪物的最大数量（Eliminate Maximum Number of Monsters）
# 思路：贪心。第 i 只怪物的截止时刻为 (dist-1)//speed，按截止时刻升序排序后，第 i 只必须在第 i 分钟前消灭，否则立即返回 i。
# 时间复杂度：O(n log n)，排序为瓶颈；空间复杂度：O(n)，保存截止时刻列表。
class Solution:  # LeetCode 约定的题解类
    def eliminateMaximum(self, dist: List[int], speed: List[int]) -> int:  # dist 是初始距离，speed 是速度；返回能消灭的怪物最大数量
        times = sorted((d - 1) // s for d, s in zip(dist, speed))  # 用整除算出每只怪物的最晚消灭时刻（0 起），并升序排序
        for i, t in enumerate(times):  # 第 i 分钟最多消灭一只，i 同时也是一路处理到的序号
            if t < i:  # 截止时刻早于 i，说明这一分钟它已经到达
                return i  # 只能消灭前 i 只，直接返回
        return len(times)  # 全部按时消灭，返回怪物总数
