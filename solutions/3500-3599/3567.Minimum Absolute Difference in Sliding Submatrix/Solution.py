# 题目：3567. 子矩阵的最小绝对差（Minimum Absolute Difference in Sliding Submatrix）
# 思路：对每个 k×k 子矩阵把元素取出并排序，最小绝对差一定出现在排序后的相邻元素之间；用 pairwise 遍历相邻对并跳过数值相等的组合，若子矩阵内元素全相同则 default=0 取 0。
# 时间复杂度：O(m * n * k^2 log k)，共 (m-k+1)(n-k+1) 个子矩阵，每个收集 O(k^2) 个元素并排序；空间复杂度：O(k^2)，每个子矩阵的临时列表。
class Solution:  # LeetCode 约定的题解类
    def minAbsDiff(self, grid: List[List[int]], k: int) -> List[List[int]]:  # grid：原矩阵；k：滑动子矩阵的边长；返回每个 k×k 子矩阵中不同元素的最小绝对差
        m, n = len(grid), len(grid[0])  # 矩阵的行数与列数
        ans = [[0] * (n - k + 1) for _ in range(m - k + 1)]  # 预分配答案矩阵，共 (m-k+1) 行 (n-k+1) 列
        for i in range(m - k + 1):  # 枚举子矩阵左上角的行号
            for j in range(n - k + 1):  # 枚举子矩阵左上角的列号
                nums = []  # 收集当前子矩阵内的全部元素
                for x in range(i, i + k):  # 遍历子矩阵的每一行
                    for y in range(j, j + k):  # 遍历子矩阵的每一列
                        nums.append(grid[x][y])  # 把元素收进一维列表
                nums.sort()  # 排序后最小绝对差一定出现在相邻元素之间
                d = min((abs(a - b) for a, b in pairwise(nums) if a != b), default=0)  # 跳过数值相等的相邻对，其余取差的最小值；毫无不同元素时用 default 取 0
                ans[i][j] = d  # 写入当前子矩阵的答案
        return ans  # 返回答案矩阵
