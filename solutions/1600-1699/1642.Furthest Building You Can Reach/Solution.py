# 题目：1642. 可以到达的最远建筑（Furthest Building You Can Reach）
# 思路：贪心 + 小顶堆，把上坡差值先记作「用梯子」，堆内数量超过梯子数时弹出最小差值改用砖块支付。
# 时间复杂度：O(n log n)，每个差值入堆出堆各一次；空间复杂度：O(n)，堆最多保存 n-1 个差值。
class Solution:  # LeetCode 约定的题解类
    def furthestBuilding(self, heights: List[int], bricks: int, ladders: int) -> int:  # heights：楼层高度；bricks：砖块数；ladders：梯子数，返回能到达的最远建筑下标
        h = []  # 小顶堆 h：存放当前交给梯子支付的上坡差值，堆顶最小
        for i, a in enumerate(heights[:-1]):  # 逐个检查相邻两栋楼（heights[:-1] 去掉最后一栋，它没有「下一栋」）
            b = heights[i + 1]  # b 是下一栋楼的高度
            d = b - a  # 高度差，正数表示需要往上爬
            if d > 0:  # 下坡或持平不消耗任何资源
                heappush(h, d)  # 先假设这一跳用梯子
                if len(h) > ladders:  # 梯子用超了，必须把最小的差值改用砖块支付
                    bricks -= heappop(h)  # 弹出最小差值并从砖块里扣除
                    if bricks < 0:  # 砖块为负说明到不了下一栋
                        return i  # 只能停在当前这栋楼
        return len(heights) - 1  # 所有跳跃都够用，能到达最后一栋楼
