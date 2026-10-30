# 题目：2105. 给植物浇水 II（Watering Plants II）
# 思路：双指针从数组两端向中间推进，Alice 负责左端、Bob 负责右端，浇水前水量不足就补满并计数，最后处理相遇的那一株。
# 时间复杂度：O(n)，每株植物最多被判一次；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumRefill(self, plants: List[int], capacityA: int, capacityB: int) -> int:  # plants 是每株植物所需水量，capacityA/capacityB 是两人的水壶容量
        a, b = capacityA, capacityB  # a、b 表示两人壶中当前剩余水量，初始为满壶
        ans = 0  # ans 记录补水次数
        i, j = 0, len(plants) - 1  # i、j 是左右两个指针，从两端相向而行
        while i < j:  # 两人尚未相遇时继续
            if a < plants[i]:  # Alice 的水不够浇左端这株
                ans += 1  # 补水次数加一
                a = capacityA  # 把水壶补满
            a -= plants[i]  # 扣掉这株植物消耗的水
            if b < plants[j]:  # Bob 的水不够浇右端这株
                ans += 1  # 补水次数加一
                b = capacityB  # 把水壶补满
            b -= plants[j]  # 扣掉这株植物消耗的水
            i, j = i + 1, j - 1  # 两个指针同时向中间收缩一格
        ans += i == j and max(a, b) < plants[i]  # 若还剩中间一株，就由剩水多的人去浇，水不够则再补一次（布尔值相加）
        return ans  # 返回最少补水次数
