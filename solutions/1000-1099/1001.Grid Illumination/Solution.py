# 题目：1001. 网格照明（Grid Illumination）
# 思路：不逐格模拟，而是用计数器维护每条行、列、主对角线(i-j)、副对角线(i+j)上的灯数；查询时四者任一非零即被照亮，然后关掉 3×3 邻域内的灯并同步更新计数。
# 时间复杂度：O(m + q)，m 为灯数、q 为查询数；空间复杂度：O(m)。
class Solution:  # LeetCode 约定的题解类
    def gridIllumination(  # n：网格边长；lamps：灯的坐标；queries：查询坐标；返回每个查询位置是否被照亮
        self, n: int, lamps: List[List[int]], queries: List[List[int]]  # 参数：网格边长、灯坐标列表、查询坐标列表
    ) -> List[int]:  # 返回与 queries 等长的 0/1 数组
        s = {(i, j) for i, j in lamps}  # 用集合去重，保存所有亮着的灯坐标
        row, col, diag1, diag2 = Counter(), Counter(), Counter(), Counter()  # 四个方向的灯数计数器：行、列、主对角线(i-j)、副对角线(i+j)
        for i, j in s:  # 遍历去重后的灯（重复坐标只统计一次）
            row[i] += 1  # 该行灯数加一
            col[j] += 1  # 该列灯数加一
            diag1[i - j] += 1  # 主对角线灯数加一
            diag2[i + j] += 1  # 副对角线灯数加一
        ans = [0] * len(queries)  # 答案数组，初始 0 表示未被照亮
        for k, (i, j) in enumerate(queries):  # 同时取出查询下标 k 与查询坐标 (i, j)
            if row[i] or col[j] or diag1[i - j] or diag2[i + j]:  # 同行、同列或同对角线还有灯，则该格被照亮
                ans[k] = 1  # 记为照亮
            for x in range(i - 1, i + 2):  # 枚举以查询点为中心的 3 行
                for y in range(j - 1, j + 2):  # 枚举对应的 3 列
                    if (x, y) in s:  # 该位置确实有灯才需要关掉（越界坐标不可能在集合里）
                        s.remove((x, y))  # 把这盏灯从集合中移除
                        row[x] -= 1  # 行灯数减一
                        col[y] -= 1  # 列灯数减一
                        diag1[x - y] -= 1  # 主对角线灯数减一
                        diag2[x + y] -= 1  # 副对角线灯数减一
        return ans  # 返回全部查询的结果数组
