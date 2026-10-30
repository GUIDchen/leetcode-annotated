# 题目：1953. 你可以工作的最大周数（Maximum Number of Weeks for Which You Can Work）
# 思路：设最大里程碑为 mx、其余之和为 rest；若 mx > rest + 1 则最多做 2·rest+1 周，否则所有里程碑都能做完。
# 时间复杂度：O(n)，求最大值与求和各一遍；空间复杂度：O(1)，只用了几个临时变量。
class Solution:  # LeetCode 约定的题解类
    def numberOfWeeks(self, milestones: List[int]) -> int:  # milestones：每项工作剩余的里程碑数
        mx, s = max(milestones), sum(milestones)  # 最大的那一项里程碑数与全部里程碑之和
        rest = s - mx  # 除最大项之外其余里程碑之和
        return rest * 2 + 1 if mx > rest + 1 else s  # 最大项过多只能交替做，否则可以全部做完
