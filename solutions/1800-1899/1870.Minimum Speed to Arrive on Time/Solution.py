# 题目：1870. 准时到达的列车最小时速（Minimum Speed to Arrive on Time）
# 思路：判定函数对「非末段向上取整、末段保留小数」累计耗时；可行性关于速度单调，故用 bisect_left 在布尔序列上二分最小可行速度。
# 时间复杂度：O(n log 1e7)，二分约 24 次、每次 O(n) 判定；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minSpeedOnTime(self, dist: List[int], hour: float) -> int:  # dist：各段距离；hour：允许的总时间（小时）
        def check(v: int) -> bool:  # 判定函数：速度为 v 时能否在 hour 小时内到达
            s = 0  # 累计总耗时
            for i, d in enumerate(dist):  # 逐段累加耗时
                t = d / v  # 第 i 段在速度 v 下的实际耗时
                s += t if i == len(dist) - 1 else ceil(t)  # 只有末段能保留小数，其余段必须等到整数小时才能发车
            return s <= hour  # 总耗时不超过 hour 即说明速度 v 可行

        if len(dist) > ceil(hour):  # 每段至少耗 1 小时（末段除外），段数超过可用整数小时就必然来不及
            return -1  # 无解
        r = 10**7 + 1  # 二分右边界（不含），答案只在 [1, 1e7] 内
        ans = bisect_left(range(1, r), True, key=check) + 1  # 在有序布尔序列上二分：找第一个判定为 True 的速度，下标 +1 还原成速度值
        return -1 if ans == r else ans  # 落到边界之外说明 1e7 也不够快，返回 -1
