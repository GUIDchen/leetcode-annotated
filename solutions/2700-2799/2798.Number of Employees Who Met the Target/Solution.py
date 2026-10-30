# 题目：2798. 满足目标工作时长的员工数目（Number of Employees Who Met the Target）
# 思路：用生成器表达式把每个工时与目标比较成布尔值，再用 sum 累加为人数。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，生成器不额外保存中间结果。
class Solution:  # LeetCode 约定的题解类
    def numberOfEmployeesWhoMetTarget(self, hours: List[int], target: int) -> int:  # hours：每位员工的工时；target：目标工时
        return sum(x >= target for x in hours)  # sum 把每个 True 当作 1 累加，正好是满足 h >= target 的员工人数
