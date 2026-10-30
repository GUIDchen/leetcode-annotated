# 题目：1329. 将矩阵按对角线排序（Sort the Matrix Diagonally）
# 思路：同一左上→右下对角线上的元素 i-j 恒定，用 m-i+j 作桶编号收集；每条对角线降序排序后，再按原坐标 pop() 取最小值写回。
# 时间复杂度：O(m*n*log(min(m,n)))；空间复杂度：O(m*n)，桶里保存全部元素。
class Solution:  # 题解类
    def diagonalSort(self, mat: List[List[int]]) -> List[List[int]]:  # mat：m 行 n 列矩阵，返回按对角线排序后的矩阵
        m, n = len(mat), len(mat[0])  # m 为行数，n 为列数
        g = [[] for _ in range(m + n)]  # 为每条对角线准备一个桶，编号为 m-i+j，共 m+n 个
        for i, row in enumerate(mat):  # 枚举行下标 i 与整行
            for j, x in enumerate(row):  # 枚举列下标 j 与元素值 x
                g[m - i + j].append(x)  # 把元素放进它所在对角线的桶
        for e in g:  # 逐条对角线处理
            e.sort(reverse=True)  # 降序排序，这样 pop() 每次取到的都是当前最小值
        for i in range(m):  # 重新遍历矩阵，按原位置写回
            for j in range(n):  # 枚举列下标
                mat[i][j] = g[m - i + j].pop()  # pop() 取出降序桶的末尾，即当前最小值
        return mat  # 返回排序后的矩阵
