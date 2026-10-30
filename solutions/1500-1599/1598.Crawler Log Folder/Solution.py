# 题目：1598. 文件夹操作日志搜集器（Crawler Log Folder）
# 思路：维护当前目录深度，"../" 让深度减一（不低于 0），"./" 不变，其余目录名让深度加一。
# 时间复杂度：O(n)，只需扫一遍日志；空间复杂度：O(1)，只用一个深度变量。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, logs: List[str]) -> int:  # logs 为按时间顺序记录的日志
        ans = 0  # 当前目录深度，也正是回到主目录所需的最少操作数
        for v in logs:  # 逐条处理日志
            if v == "../":  # 返回父目录
                ans = max(0, ans - 1)  # 深度减一，但不能低于主目录 0
            elif v[0] != ".":  # 首字符不是句点，说明是普通子文件夹
                ans += 1  # 进入子文件夹，深度加一
        return ans  # 返回最终深度，即最少需要的操作次数
