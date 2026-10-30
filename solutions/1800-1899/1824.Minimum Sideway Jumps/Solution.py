# 题目：1824. 最少侧跳次数（Minimum Sideway Jumps）
# 核心思路：动态规划，f[j] 表示到达当前列第 j+1 条跑道的最少侧跳次数；先把被障碍占据的跑道置为无穷，再用三条跑道最小值 +1 更新可落脚的跑道。
# 时间复杂度：O(n)，每列只处理 3 条跑道；空间复杂度：O(1)，只维护长度 3 的列表。
class Solution:  # LeetCode 约定的题解类
    def minSideJumps(self, obstacles: List[int]) -> int:  # obstacles[i] 表示第 i 个位置的障碍跑道，0 表示无障碍
        f = [1, 0, 1]  # f[j]：到达当前列第 j+1 条跑道的最少侧跳次数，起点在第 2 条跑道
        for v in obstacles[1:]:  # 从下标 1 开始逐列推进，下标 0 是起点且没有障碍
            for j in range(3):  # 三条跑道逐一检查是否被障碍占据
                if v == j + 1:  # v == j + 1 说明第 j 条跑道在这一列被堵
                    f[j] = inf  # 该跑道不可达，置为无穷大
                    break  # 一列最多只有一个障碍，跳出内层循环
            x = min(f) + 1  # 到达当前列任意跑道最多是从最优跑道再侧跳一次
            for j in range(3):  # 用基准值更新三条跑道
                if v != j + 1:  # 没有被堵住的跑道才能落脚
                    f[j] = min(f[j], x)  # 原地不动与侧跳一次取较小者
        return min(f)  # 三条跑道的最小代价即为答案
