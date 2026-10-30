# 题目：1738. 找出第 K 大的异或坐标值（Find Kth Largest XOR Coordinate Value）
# 思路：用二维前缀异或 s[i+1][j+1] = s[i+1][j] ^ s[i][j+1] ^ s[i][j] ^ matrix[i][j] 递推，把每个坐标值收集起来后用堆取第 k 大。
# 时间复杂度：O(mn log k)，nlargest 维护大小为 k 的堆；空间复杂度：O(mn)，前缀异或表与结果列表。
class Solution:  # LeetCode 约定的题解类
    def kthLargestValue(self, matrix: List[List[int]], k: int) -> int:  # matrix 是输入矩阵，k 是要求的排名
        m, n = len(matrix), len(matrix[0])  # 矩阵的行数与列数
        s = [[0] * (n + 1) for _ in range(m + 1)]  # 多一行一列的前缀异或表，避免处理边界
        ans = []  # 收集每个坐标对应的异或值
        for i in range(m):  # 遍历每一行
            for j in range(n):  # 遍历每一列
                s[i + 1][j + 1] = s[i + 1][j] ^ s[i][j + 1] ^ s[i][j] ^ matrix[i][j]  # 容斥：左侧与上侧异或，重叠的左上角异或两次抵消，再并上当前格
                ans.append(s[i + 1][j + 1])  # 记录当前坐标的异或值
        return nlargest(k, ans)[-1]  # 取出前 k 大的元素，最后一个即第 k 大
