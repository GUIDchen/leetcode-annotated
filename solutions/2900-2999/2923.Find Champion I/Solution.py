# 题目：2923. 找到冠军 I（Find Champion I）
# 思路：冠军要战胜其余所有队伍，逐行检查除自己以外是否全为 1，全部为 1 的队伍就是冠军。
# 时间复杂度：O(n^2)，最坏检查整张矩阵；空间复杂度：O(1)，只用生成器逐个判断。
class Solution:  # LeetCode 约定的题解类
    def findChampion(self, grid: List[List[int]]) -> int:  # grid[i][j]==1 表示 i 比 j 强
        for i, row in enumerate(grid):  # 逐支队伍检查
            if all(x == 1 for j, x in enumerate(row) if i != j):  # 去掉自己后，对其余队伍全部获胜
                return i  # 找到冠军直接返回
