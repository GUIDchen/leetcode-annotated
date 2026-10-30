# 题目：2491. 划分技能点相等的团队（Divide Players Into Teams of Equal Skill）
# 思路：排序后双指针「最小配最大」，每组和都必须等于 skill[0]+skill[-1]，可行则累加每组乘积，否则返回 -1。
# 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(n)，排序产生的临时空间。
class Solution:  # LeetCode 约定的题解类
    def dividePlayers(self, skill: List[int]) -> int:  # skill 是每个人的技能点数组，返回各团队技能乘积之和
        skill.sort()  # 升序排序，之后用双指针让最小配最大
        t = skill[0] + skill[-1]  # 由最小值和最大值先确定唯一可能的团队技能和
        i, j = 0, len(skill) - 1  # i 指向最小、j 指向最大，向中间夹逼组队
        ans = 0  # 累加各组技能乘积
        while i < j:  # 两队还没相遇就继续配对
            if skill[i] + skill[j] != t:  # 某组技能和不等于 t 就不可能划分成和相等的团队
                return -1  # 当前组不合法，按题目要求返回 -1
            ans += skill[i] * skill[j]  # 累加当前团队的技能乘积
            i, j = i + 1, j - 1  # 同时移动两个指针，进入下一对
        return ans  # 返回全部团队的技能乘积之和
