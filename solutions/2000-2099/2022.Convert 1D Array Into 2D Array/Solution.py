# 题目：2022. 将一维数组转变成二维数组（Convert 1D Array Into 2D Array）
# 思路：元素个数必须恰好等于 m * n，否则返回空列表；否则按长度为 n 的步长切片，每片正好是矩阵的一行。
# 时间复杂度：O(m * n)，每个元素只被复制一次；空间复杂度：O(m * n)，即结果矩阵本身。
class Solution:  # LeetCode 约定的题解类
    def construct2DArray(self, original: List[int], m: int, n: int) -> List[List[int]]:  # original：一维数组；m、n：目标矩阵的行数与列数
        if m * n != len(original):  # 元素个数不匹配时无法构造
            return []  # 返回空列表表示失败
        return [original[i : i + n] for i in range(0, m * n, n)]  # 以 n 为步长切片，每片正好对应一行
