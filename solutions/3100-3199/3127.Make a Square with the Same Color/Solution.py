# 题目：3127. 构造相同颜色的正方形（Make a Square with the Same Color）
# 思路：枚举所有 2×2 子方阵，只要某个子方阵里黑白格数量不相等（即 3:1 或 4:0），改一个格子就能变成同色。
# 时间复杂度：O(m * n)，每个 2×2 区域只做常数次比较；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def canMakeSquare(self, grid: List[List[str]]) -> bool:  # 判断能否只改一个格子，就让某个 2×2 区域里出现 3 个同色格
        for i in range(0, 2):  # 枚举 2×2 区域左上角的行号
            for j in range(0, 2):  # 枚举左上角的列号
                cnt1 = cnt2 = 0  # cnt1 统计白格数，cnt2 统计黑格数
                for a, b in pairwise((0, 0, 1, 1, 0)):  # pairwise 依次给出四个角的偏移：(0,0)、(0,1)、(1,1)、(1,0)
                    x, y = i + a, j + b  # 由偏移得到格子的实际坐标
                    cnt1 += grid[x][y] == "W"  # 是 W 色就累加到 cnt1
                    cnt2 += grid[x][y] == "B"  # 是 B 色就累加到 cnt2
                if cnt1 != cnt2:  # 两色数量不等，改一个格子即可统一成同色
                    return True  # 找到可行区域，返回 True
        return False  # 所有 2×2 区域都是 2:2，无法只改一个格子
