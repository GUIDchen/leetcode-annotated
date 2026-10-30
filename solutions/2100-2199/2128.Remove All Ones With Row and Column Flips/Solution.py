# 题目：2128. 通过翻转行或列来去除所有的 1（Remove All Ones With Row and Column Flips）
# 核心思路：以第一行首元素为基准做归一化，每行要么保持、要么整行取反；所有行归一化后相同即可消除。
# 时间复杂度：O(m·n)，每格处理一次；空间复杂度：O(m·n)，集合保存每行的归一化元组。
class Solution:  # LeetCode 约定的题解类
    def removeOnes(self, grid: List[List[int]]) -> bool:  # grid 是只含 0/1 的矩阵；返回能否通过翻整行或整列把所有 1 变成 0
        s = set()  # 用集合收集每行归一化后的元组，等价的行只保留一份
        for row in grid:  # 逐行处理
            t = tuple(row) if row[0] == grid[0][0] else tuple(x ^ 1 for x in row)  # 首元素与第一行首元素相同则保持原样，否则整行取反（x ^ 1）
            s.add(t)  # 归一化结果放入集合
        return len(s) == 1  # 集合大小为 1 说明所有行形态一致，可以翻列翻行清掉所有 1
