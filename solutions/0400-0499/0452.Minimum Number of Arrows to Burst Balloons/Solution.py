# 题目：452. 用最少数量的箭引爆气球（Minimum Number of Arrows to Burst Balloons）
# 思路：把气球按右端点升序排序，贪心地让每支箭都落在当前未覆盖气球的最右端点；一旦某气球左端点超过该位置，就必须再补一支箭。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，排序生成的列表副本。
class Solution:  # LeetCode 约定的题解类
    def findMinArrowShots(self, points: List[List[int]]) -> int:  # points：每个气球的闭区间 [左端点, 右端点]；返回引爆全部气球的最少箭数
        ans, last = 0, -inf  # ans：已用箭数；last：上一支箭的落点，初值 -inf 保证第一支箭必被发射
        for a, b in sorted(points, key=lambda x: x[1]):  # 按右端点升序排序后逐个处理气球
            if a > last:  # 该气球的左端点超过上一支箭的落点，说明它没有被覆盖
                ans += 1  # 需要再射一支箭
                last = b  # 新箭落在当前气球的右端点，能覆盖尽可能多的后续气球
        return ans  # 返回最少箭数
