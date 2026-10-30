# 题目：2906. 构造乘积矩阵（Construct Product Matrix）
# 核心思路：先逆序扫一遍，把每个格子「右下方所有元素」的乘积写进答案；再正序扫一遍乘上「左上方所有元素」的乘积，就得到除自身外全部元素之积，全程对 12345 取模。
# 时间复杂度：O(n*m)，每个格子常数次运算；空间复杂度：O(n*m)，额外只使用答案矩阵。
class Solution:  # LeetCode 约定的题解类
    def constructProductMatrix(self, grid: List[List[int]]) -> List[List[int]]:  # grid 是二维矩阵，返回同形状的乘积矩阵
        n, m = len(grid), len(grid[0])  # 求出行列数：n 行 m 列
        p = [[0] * m for _ in range(n)]  # 答案矩阵，先用 0 填充（不能写成 [[0]*m]*n，那样各行会共享同一个列表）
        mod = 12345  # 题目指定的取模常量
        suf = 1  # suf 记录「当前格子之后所有元素」的乘积，空乘积为 1
        for i in range(n - 1, -1, -1):  # 第一遍从最后一行倒着扫
            for j in range(m - 1, -1, -1):  # 列也倒着扫，这样 suf 天然就是右下方的乘积
                p[i][j] = suf  # 先写入后缀乘积，左侧部分稍后再补
                suf = suf * grid[i][j] % mod  # 再把当前元素并入后缀，供更靠左上的格子使用
        pre = 1  # pre 记录「当前格子之前所有元素」的乘积，空乘积为 1
        for i in range(n):  # 第二遍正序扫描，补上左侧乘积
            for j in range(m):  # 逐列正序遍历
                p[i][j] = p[i][j] * pre % mod  # 前缀乘后缀即除自身外的总积，边乘边取模
                pre = pre * grid[i][j] % mod  # 把当前元素并入前缀，供右侧格子使用
        return p  # 返回构造好的乘积矩阵
