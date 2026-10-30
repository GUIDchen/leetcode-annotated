# 题目：2300. 咒语和药水的成功对数（Successful Pairs of Spells and Potions）
# 思路：药水排序后，对每个咒语用 bisect_left 找到第一个满足 spell * potion >= success 的下标，右侧长度即成功对数。
# 时间复杂度：O((n + m) log m)，排序加每个咒语一次二分；空间复杂度：O(n) 存放结果。
class Solution:  # LeetCode 约定的题解类
    def successfulPairs(  # 参数较多，分行书写更清晰
        self, spells: List[int], potions: List[int], success: int  # spells：咒语；potions：药水；success：成功阈值
    ) -> List[int]:  # 返回与 spells 等长的列表，每项是对应咒语的成功配对数
        potions.sort()  # 升序排序，二分的前提
        m = len(potions)  # 药水总数，用于把下标换算成成功个数
        return [m - bisect_left(potions, success / v) for v in spells]  # 二分出第一个 potions[j] 满足 v * potions[j] >= success 的下标，m 减去它即成功个数
