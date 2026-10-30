# 题目：296. 最佳的碰头地点（Best Meeting Point）🔒
# 思路：曼哈顿距离的行、列两部分可分离，各自取中位数即最优；行号按行扫描天然有序，列号排序后取中位数。
# 时间复杂度：O(mn + k log k)，k 为人数；空间复杂度：O(k)，保存所有点的行、列坐标。
class Solution:  # LeetCode 约定的题解类
    def minTotalDistance(self, grid: List[List[int]]) -> int:  # grid：0/1 矩阵，1 表示该格有人
        def f(arr, x):  # 内部函数：计算数组 arr 中所有点到坐标 x 的距离之和
            return sum(abs(v - x) for v in arr)  # 生成器表达式求和，即该方向的总距离

        rows, cols = [], []  # 分别收集所有 1 的行号与列号
        for i, row in enumerate(grid):  # 枚举行
            for j, v in enumerate(row):  # 枚举该行的每一列
                if v:  # 该格有人
                    rows.append(i)  # 记录行号；按行扫描，所以 rows 天然递增有序
                    cols.append(j)  # 记录列号（此时尚未排序）
        cols.sort()  # 列号需要排序后才能取中位数
        i = rows[len(rows) >> 1]  # 行方向取中位数（>> 1 等价于整除 2）
        j = cols[len(cols) >> 1]  # 列方向取中位数
        return f(rows, i) + f(cols, j)  # 行、列可分离，两个方向的距离和相加即最小总距离
