# 题目：365. 水壶问题（Water and Jug Problem）
# 思路：把 (i, j) 两壶水量当作状态做 DFS，枚举装满、倒空、互相倒六种转移，用集合去重，任一状态达到 z 即可行。
# 时间复杂度：O(x·y)，状态数上限；空间复杂度：O(x·y)，访问集合与递归栈。
class Solution:  # LeetCode 题解类
    def canMeasureWater(self, x: int, y: int, z: int) -> bool:  # 两壶容量分别为 x、y，目标是量出水量 z
        def dfs(i: int, j: int) -> bool:  # 内层 DFS：i、j 为当前两壶水量
            if (i, j) in vis:  # 该状态已经访问过
                return False  # 剪枝，避免重复搜索
            vis.add((i, j))  # 标记为已访问
            if i == z or j == z or i + j == z:  # 任一壶或两壶合计等于目标即可
                return True  # 找到可行方案
            if dfs(x, j) or dfs(i, y) or dfs(0, j) or dfs(i, 0):  # 依次尝试装满/倒空两壶
                return True  # 任一分支成功即成功
            a = min(i, y - j)  # 第一壶能倒入第二壶的量
            b = min(j, x - i)  # 第二壶能倒入第一壶的量
            return dfs(i - a, j + a) or dfs(i + b, j - b)  # 尝试两种互相倒水的转移

        vis = set()  # 记录已访问的状态
        return dfs(0, 0)  # 从两壶皆空的初始状态开始搜索
