# 题目：1337. 矩阵中战斗力最弱的 K 行（The K Weakest Rows in a Matrix）
# 思路：每行都是「若干个 1 后接全 0」，把行反转后用 bisect_right 数出 0 的个数，再用 n 减去它得到 1 的个数；然后按 1 的个数对行号做稳定排序，稳定排序保证数量相同时行号小的在前，最后取前 k 个。
# 时间复杂度：O(m log n + m log m)，m 行 n 列；空间复杂度：O(m)，存放每行 1 的个数与行号列表。
class Solution:  # LeetCode 约定的题解类
    def kWeakestRows(self, mat: List[List[int]], k: int) -> List[int]:  # mat 为 0/1 矩阵，k 为要返回的行数，返回最弱的 k 行行号
        m, n = len(mat), len(mat[0])  # m 为行数，n 为列数
        ans = [n - bisect_right(row[::-1], 0) for row in mat]  # 行反转后 0 都在前面，bisect_right 得到 0 的个数，n 减去它就是 1 的个数
        idx = list(range(m))  # 行号列表，初始为 0..m-1
        idx.sort(key=lambda i: ans[i])  # 按每行 1 的个数升序排序；sort 稳定，所以数量相同时保持行号升序
        return idx[:k]  # 取最弱的前 k 行行号
