# 题目：2718. 查询后矩阵的和（Sum of Matrix After Queries）
# 思路：倒序处理查询，每个格子只由最后一次覆盖它的查询决定；用两个集合记录已被更晚查询占用的行与列。
# 时间复杂度：O(n+q)，q 为查询数；空间复杂度：O(n)，两个集合最多各存 n 个下标。
class Solution:  # LeetCode 约定的题解类
    def matrixSumQueries(self, n: int, queries: List[List[int]]) -> int:  # n 为矩阵边长，queries 为 [类型, 下标, 值] 的覆盖操作列表
        row = set()  # 记录已被更晚查询覆盖过的行号
        col = set()  # 记录已被更晚查询覆盖过的列号
        ans = 0  # ans 为最终矩阵元素和，Python 整数不会溢出
        for t, i, v in queries[::-1]:  # 倒序遍历查询，保证每个位置最后一次赋的值先被计入
            if t == 0:  # t 为类型（0 整行、1 整列）
                if i not in row:  # 该行没被更晚的查询覆盖过，这次才真正生效
                    ans += v * (n - len(col))  # 生效格子数为 n 减去已被覆盖的列数，乘 v 累加
                    row.add(i)  # 标记这一行已被占用
            else:  # 否则是类型 1：整列覆盖
                if i not in col:  # 该列没被更晚的查询覆盖过，这次才真正生效
                    ans += v * (n - len(row))  # 生效格子数为 n 减去已被覆盖的行数，乘 v 累加
                    col.add(i)  # 标记这一列已被占用
        return ans  # 返回倒序累加得到的矩阵总和
