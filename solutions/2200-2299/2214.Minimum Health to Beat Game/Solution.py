# 题目：2214. 通关游戏所需的最低生命值（Minimum Health to Beat Game）
# 思路：总伤害为 sum(damage)，护甲只能在承受某一次伤害时减免，所以一定把它用在最大的一次伤害上，实际减免 min(max(damage), armor)；生命值需严格大于总损失，故最后再加 1。
# 时间复杂度：O(n)，求总和与最大值各一趟线性扫描；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def minimumHealth(self, damage: List[int], armor: int) -> int:  # damage：每一关的伤害；armor：护甲值；返回通关所需的最低初始生命值
        return sum(damage) - min(max(damage), armor) + 1  # 总伤害减去护甲在最大一击上的减免上限，再 +1 使生命值严格大于总损失
