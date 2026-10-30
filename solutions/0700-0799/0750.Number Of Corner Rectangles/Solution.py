# 题目：750. 角矩形的数量（Number Of Corner Rectangles）
# 核心思路：以列对 (i, j) 为键统计此前有多少行两列同时为 1，新行出现该列对时，与之前这些行两两组合成角矩形。
# 时间复杂度：O(m · n^2)，两层列枚举；空间复杂度：O(n^2)，最多保存 n(n-1)/2 个列对计数。
class Solution:  # LeetCode 约定的题解类
    def countCornerRectangles(self, grid: List[List[int]]) -> int:  # grid 是 0/1 矩阵，1 表示该位置有顶点
        ans = 0  # 角矩形计数
        cnt = Counter()  # 键是列对 (i, j)，值是此前两列同为 1 的行数
        n = len(grid[0])  # 列数
        for row in grid:  # 逐行扫描
            for i, c1 in enumerate(row):  # 枚举左侧列 i 及其取值
                if c1:  # 第 i 列有点，才可能构成矩形的左竖边
                    for j in range(i + 1, n):  # 只在右侧枚举 j，避免同一列对被重复统计
                        if row[j]:  # 第 j 列也是点，这一行可作为矩形的水平边
                            ans += cnt[(i, j)]  # 与之前同样包含这两点的每一行配对成一个角矩形
                            cnt[(i, j)] += 1  # 本行加入该列对的计数，供后续行配对
        return ans  # 返回角矩形总数
