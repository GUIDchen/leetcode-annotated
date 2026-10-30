# 题目：690. 员工的重要性（Employee Importance）
# 思路：先用字典建立「员工 id → 员工对象」索引，再从给定 id 出发 DFS 累加重要度并递归所有下属。
# 时间复杂度：O(n)，每个员工只被访问一次；空间复杂度：O(n)，字典与递归栈。
"""
# Definition for Employee.
class Employee:
    def __init__(self, id: int, importance: int, subordinates: List[int]):
        self.id = id
        self.importance = importance
        self.subordinates = subordinates
"""


class Solution:  # LeetCode 约定的题解类
    def getImportance(self, employees: List["Employee"], id: int) -> int:  # employees 是全体员工列表，id 是查询起点，返回该员工及其所有下属的重要度之和
        def dfs(i: int) -> int:  # 内层 dfs：计算以员工 i 为根的整个团队重要度
            return d[i].importance + sum(dfs(j) for j in d[i].subordinates)  # 自身重要度 + 所有直接下属团队重要度之和（惰性生成器交给 sum 求和）

        d = {e.id: e for e in employees}  # 先用字典把 id 映射到员工对象，避免每次递归都线性查找
        return dfs(id)  # 从给定 id 开始计算整个团队的重要度
