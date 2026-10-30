# 题目：1605. 给定行和列的和求可行矩阵（Find Valid Matrix Given Row and Column Sums）
# 思路：逐格贪心，每格填 min(剩余行和, 剩余列和)，并在行、列两侧同时扣减，可保证始终不超出约束。
# 时间复杂度：O(mn)，每格只看一次；空间复杂度：O(mn)，存放答案矩阵。
class Solution:  # 题解类
    def restoreMatrix(self, rowSum: List[int], colSum: List[int]) -> List[List[int]]:  # rowSum 是每行元素之和，colSum 是每列元素之和
        m, n = len(rowSum), len(colSum)  # m 为行数，n 为列数
        ans = [[0] * n for _ in range(m)]  # 先构造一个 m×n 的全 0 矩阵作为答案
        for i in range(m):  # 逐行填充
            for j in range(n):  # 逐列填充
                x = min(rowSum[i], colSum[j])  # 贪心：该格最多填「本行剩余和」与「本列剩余和」中的较小值
                ans[i][j] = x  # 把取到的值写入矩阵
                rowSum[i] -= x  # 本行的剩余和扣掉已用掉的部分
                colSum[j] -= x  # 本列的剩余和扣掉已用掉的部分
        return ans  # 返回构造出的可行矩阵
