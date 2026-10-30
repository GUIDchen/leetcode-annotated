# 题目：2536. 子矩阵元素加 1（Increment Submatrices by One）
# 思路：二维差分。每条查询只在矩形四角打标记，最后统一做一次二维前缀和还原每格的覆盖次数。
# 时间复杂度：O(n^2 + q)，q 为查询数；空间复杂度：O(n^2)，返回的矩阵本身占用。
class Solution:  # LeetCode 约定的题解类
    def rangeAddQueries(self, n: int, queries: List[List[int]]) -> List[List[int]]:  # n 为矩阵边长，queries 每项是 [x1, y1, x2, y2]
        mat = [[0] * n for _ in range(n)]  # n×n 全 0 矩阵作为差分数组；用列表推导为每一行新建列表，避免各行共享同一对象
        for x1, y1, x2, y2 in queries:  # 遍历每个要整体加 1 的子矩阵
            mat[x1][y1] += 1  # 差分：左上角 +1，标记区间从这里开始
            if x2 + 1 < n:  # 下边界 x2+1 未越界时
                mat[x2 + 1][y1] -= 1  # 下方同列 -1，抵消离开子矩阵后的贡献
            if y2 + 1 < n:  # 右边界 y2+1 未越界时
                mat[x1][y2 + 1] -= 1  # 右侧同行 -1
            if x2 + 1 < n and y2 + 1 < n:  # 行列都还有下/右邻格时
                mat[x2 + 1][y2 + 1] += 1  # 右下角 +1，把多减的部分补回（二维差分容斥）

        for i in range(n):  # 逐行做前缀和，还原真实覆盖次数
            for j in range(n):  # 逐列处理
                if i:  # i 非 0 说明上方还有行
                    mat[i][j] += mat[i - 1][j]  # 叠加上方格子的值，向下传递差分
                if j:  # j 非 0 说明左侧还有列
                    mat[i][j] += mat[i][j - 1]  # 叠加左方格子的值，向右传递差分
                if i and j:  # i 和 j 都非 0 时
                    mat[i][j] -= mat[i - 1][j - 1]  # 减掉被重复累加一次的左上角
        return mat  # 返回还原后的矩阵
