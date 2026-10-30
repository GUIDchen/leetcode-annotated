# 题目：1992. 找到所有的农场组（Find All Groups of Farmland）
# 思路：每个农场组都是互不重叠的矩形，只有「左上角」格子值得当起点（它左侧与上方都不是农田）；从左上角沿列向下、再沿行向右各推到底，就得到右下角。
# 时间复杂度：O(m*n)，每个格子最多被检查常数次；空间复杂度：O(1)（不计返回结果）。
class Solution:  # LeetCode 约定的题解类
    def findFarmland(self, land: List[List[int]]) -> List[List[int]]:  # land：0/1 矩阵，1 表示农田；返回每组农场地的 [左上x, 左上y, 右下x, 右下y]
        m, n = len(land), len(land[0])  # 行数与列数
        ans = []  # 收集所有农场组的答案
        for i in range(m):  # 枚举可能的左上角行
            for j in range(n):  # 枚举可能的左上角列
                if (  # 判断当前格子不是左上角的三种情况（条件分多行书写）
                    land[i][j] == 0  # 情况一：非农田，不可能作为起点
                    or (j > 0 and land[i][j - 1] == 1)  # 情况二：左侧也是农田，说明它属于某个组的内部
                    or (i > 0 and land[i - 1][j] == 1)  # 情况三：上方也是农田，说明它属于某个组的内部
                ):  # 任一情况成立即说明不是左上角
                    continue  # 不是左上角，直接跳过该格子
                x, y = i, j  # 先假定右下角与左上角重合，再逐步向外扩张
                while x + 1 < m and land[x + 1][j] == 1:  # 矩形：沿同一列向下延伸到不是 1 为止
                    x += 1  # 下边界下移一行
                while y + 1 < n and land[x][y + 1] == 1:  # 沿最下面一行向右延伸到不是 1 为止
                    y += 1  # 右边界右移一列
                ans.append([i, j, x, y])  # 记录该组的左上角与右下角
        return ans  # 按题目要求的顺序返回所有农场组
