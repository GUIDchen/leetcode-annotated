# 3457. 吃披萨 / Eat Pizzas!
# 核心思路：排序后让奇数天（第 1、3、5... 天）各占一份最大的披萨作为当天最大值，剩下的偶数天再从后往前隔一个取一份次大值。
# 复杂度：时间复杂度 O(n log n)，空间复杂度 O(1)（不计排序开销）。
class Solution:  # 题解类
    def maxWeight(self, pizzas: List[int]) -> int:  # 求所有天吃掉的披萨重量之和的最大值
        days = len(pizzas) // 4  # 每天吃 4 个，所以天数为总数除以 4
        pizzas.sort()  # 升序排序，便于从最大的开始分配
        odd = (days + 1) // 2  # 奇数编号的天数（第 1、3、5... 天）
        even = days - odd  # 偶数编号的天数
        ans = sum(pizzas[-odd:])  # 奇数天直接各取最大的一个，和为末尾 odd 个
        i = len(pizzas) - odd - 2  # 偶数天要从剩余最大的第 2 大开始取
        for _ in range(even):  # 依次分配每个偶数天
            ans += pizzas[i]  # 累加该天能吃到的最大值
            i -= 2  # 因为每天要吃掉 4 个，等价于每次向前跳过 2 个
        return ans  # 返回最大总重量
