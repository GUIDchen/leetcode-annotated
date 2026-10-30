# 题目：3071. 在矩阵上写出字母 Y 所需的最少操作次数（Minimum Operations to Write the Letter Y on a Grid）
# 核心思路：先按「Y 的三条笔画」把格子分成 Y 区域与非 Y 区域，分别统计 0/1/2 的出现次数；再枚举两区域各自的目标颜色（必须不同），用「总数 - 已符合的格数」得到改动次数并取最小。
# 时间复杂度：O(n²)，一次遍历统计 n² 个格子，之后只有 9 种颜色组合；空间复杂度：O(1)，只用两个最多 3 个键的计数器。
class Solution:  # LeetCode 约定的题解类
    def minimumOperationsToWriteY(self, grid: List[List[int]]) -> int:  # grid：n×n 且只含 0、1、2 的矩阵；返回写出字母 Y 的最少操作次数
        n = len(grid)  # 矩阵边长 n
        cnt1 = Counter()  # cnt1：属于 Y 区域的格子按颜色计数（Counter 缺键时默认为 0）
        cnt2 = Counter()  # cnt2：不属于 Y 区域的格子按颜色计数
        for i, row in enumerate(grid):  # 枚举行下标 i 与整行 row
            for j, x in enumerate(row):  # 枚举列下标 j 与该格的值 x
                a = i == j and i <= n // 2  # 笔画一：左上到中心的主对角线，且只取上半部分
                b = i + j == n - 1 and i <= n // 2  # 笔画二：右上到中心的反对角线，且只取上半部分
                c = j == n // 2 and i >= n // 2  # 笔画三：从中心向下的竖线，且只取下半部分；中心格重叠命中也只算一次
                if a or b or c:  # 命中任一笔画即为 Y 区域
                    cnt1[x] += 1  # 累加 Y 区域的颜色计数
                else:  # else：属于 Y 以外的区域
                    cnt2[x] += 1  # 累加非 Y 区域的颜色计数
        return min(  # 生成器里枚举两区域的目标颜色 i、j 且要求 i != j，用「总格数 - 已匹配数」得到要改的格子数，min 取最优
            n * n - cnt1[i] - cnt2[j] for i in range(3) for j in range(3) if i != j  # 表达式主体：n*n 个格子减去两个区域里不用改动的格子数
        )  # 多重 for 生成全部合法颜色组合，交给外层 min 求最小值
