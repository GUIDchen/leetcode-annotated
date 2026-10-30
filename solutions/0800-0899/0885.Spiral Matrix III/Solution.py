# 题目：885. 螺旋矩阵 III（Spiral Matrix III）
# 思路：从起点开始按「右、下、左、上」走，每圈步长依次为 1、1、2、2、3、3……，只把落在矩阵内的坐标加入答案。
# 时间复杂度：O(rows × cols)，每个格子只记录一次（另有少量界外行走）；空间复杂度：O(rows × cols)，保存答案。
class Solution:  # LeetCode 约定的题解类
    def spiralMatrixIII(  # 形参分多行书写：矩阵行数、列数，起点行列
        self, rows: int, cols: int, rStart: int, cStart: int  # 形参依次为行数 rows、列数 cols、起点行 rStart、起点列 cStart
    ) -> List[List[int]]:  # 返回值是按螺旋顺序排列的坐标列表
        ans = [[rStart, cStart]]  # 起点先放入答案
        if rows * cols == 1:  # 只有一个格子
            return ans  # 直接返回起点即可
        k = 1  # 当前圈的步长，从 1 开始
        while True:  # 不断画圈，直到收集完所有格子
            for dr, dc, dk in [[0, 1, k], [1, 0, k], [0, -1, k + 1], [-1, 0, k + 1]]:  # 右、下、左、上四段的步数（后两段多走一步）
                for _ in range(dk):  # 沿当前方向走 dk 步
                    rStart += dr  # 行坐标前进
                    cStart += dc  # 列坐标前进
                    if 0 <= rStart < rows and 0 <= cStart < cols:  # 只有落在矩阵内的格子才记录
                        ans.append([rStart, cStart])  # 合法格子加入答案
                        if len(ans) == rows * cols:  # 已经收集完所有格子
                            return ans  # 立即返回
            k += 2  # 下一圈步长增加 2
