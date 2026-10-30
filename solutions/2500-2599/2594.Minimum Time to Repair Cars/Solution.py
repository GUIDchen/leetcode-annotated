# 题目：2594. 修车的最少时间（Minimum Time to Repair Cars）
# 思路：对时间二分，判定函数为「每位修理工 r 在 t 分钟内能修 floor(sqrt(t // r)) 辆，总和是否达到 cars」，利用 bisect_left 找第一个满足条件的时间。
# 时间复杂度：O(n log(maxTime))，二分约 log 次、每次 O(n) 判断；空间复杂度：O(1)，只用到常数个变量。
class Solution:  # LeetCode 约定的题解类
    def repairCars(self, ranks: List[int], cars: int) -> int:  # ranks 是各修理工的工级，cars 是待修车辆数
        def check(t: int) -> bool:  # 判定函数：t 分钟内能否修完所有车
            return sum(int(sqrt(t // r)) for r in ranks) >= cars  # 工级 r 耗时 r*n^2，故 t 分钟内可修 floor(sqrt(t//r)) 辆，累加后与 cars 比较

        return bisect_left(range(ranks[0] * cars * cars), True, key=check)  # 在 [0, 最快工级修完全部车的时间] 上二分，找到第一个使 check 为 True 的时间
