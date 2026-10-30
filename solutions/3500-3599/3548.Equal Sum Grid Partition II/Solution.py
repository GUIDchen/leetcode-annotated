# 题目：3548. 等和矩阵分割 II（Equal Sum Grid Partition II）
# 思路：先按行切分，用两个哈希表记录上下两侧的取值频次，靠两侧差值判断能否删掉一个格子；再把矩阵转置重复同样的逻辑，以覆盖按列切分。
# 时间复杂度：O(m * n)，check 与转置各遍历一次矩阵；空间复杂度：O(m * n)，哈希表最多保存矩阵中所有不同的取值。
class Solution:  # LeetCode 约定的题解类
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:  # grid：m 行 n 列的整数矩阵
        def check(g: List[List[int]]) -> bool:  # 只考虑水平切割：允许在上方块中去掉至多一个格子
            m, n = len(g), len(g[0])  # m：行数；n：列数
            s1 = s2 = 0  # s1：上方部分的和；s2：下方部分的和
            cnt1 = defaultdict(int)  # 统计上方各取值的出现次数
            cnt2 = defaultdict(int)  # 统计下方各取值的出现次数
            for i, row in enumerate(g):  # 初始时整张表都属于下方
                for j, x in enumerate(row):  # 遍历该行元素
                    s2 += x  # 累加下方和
                    cnt2[x] += 1  # 下方该取值的计数加一
            for i, row in enumerate(g[: m - 1]):  # 枚举切割线：第 0~i 行归上方，并保证下方至少剩一行
                for x in row:  # 把第 i 行整行从下方搬到上方
                    s1 += x  # 上方和增加
                    s2 -= x  # 下方和减少
                    cnt1[x] += 1  # 上方该取值的计数加一
                    cnt2[x] -= 1  # 下方该取值的计数减一
                if s1 == s2:  # 两侧已经相等，不需要再删格子
                    return True  # 找到合法切割线
                if s1 < s2:  # 上方偏小，只能从下方删掉一个值等于差值的格子
                    diff = s2 - s1  # 需要补上的差值
                    if cnt2[diff]:  # 下方确实存在值等于 diff 的格子
                        if (
                            (m - i - 1 > 1 and n > 1)
                            or (
                                i == m - 2
                                and (g[i + 1][0] == diff or g[i + 1][-1] == diff)
                            )
                            or (n == 1 and (g[i + 1][0] == diff or g[-1][0] == diff))
                        ):
                            return True  # 删掉该格子后下方被切走的部分仍非空且不割裂
                else:  # 下方偏小，只能从上方删掉一个值等于差值的格子
                    diff = s1 - s2  # 需要补上的差值
                    if cnt1[diff]:  # 上方确实存在值等于 diff 的格子
                        if (
                            (i + 1 > 1 and n > 1)
                            or (i == 0 and (g[0][0] == diff or g[0][-1] == diff))
                            or (n == 1 and (g[0][0] == diff or g[i][0] == diff))
                        ):
                            return True  # 删掉该格子后上方剩余部分仍非空且不割裂
            return False  # 所有切割线都无法通过删掉一个格子配平

        return check(grid) or check(list(zip(*grid)))  # 先试水平切割，再转置后试垂直切割
