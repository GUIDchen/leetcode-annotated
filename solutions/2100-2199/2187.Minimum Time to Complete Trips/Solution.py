# 题目：2187. 完成旅途的最少时间（Minimum Time to Complete Trips）
# 思路：把「时间 x 内能完成的趟数」写成关于 x 单调不减的 key 函数，再用 bisect_left 二分出第一个满足趟数够的位置。
# 时间复杂度：O(n·log(mx))，每次比较要遍历 n 辆车；空间复杂度：O(1)（range 为惰性对象）。
class Solution:  # LeetCode 约定的题解类
    def minimumTime(self, time: List[int], totalTrips: int) -> int:  # time：每辆车单趟耗时；totalTrips：需要的总趟数
        mx = min(time) * totalTrips  # 上界：只用最快的车连续跑完所有趟数所需的时间，答案一定不超过它
        return bisect_left(  # 在 [0, mx) 上二分，找第一个「趟数 >= totalTrips」的位置
            range(mx), totalTrips, key=lambda x: sum(x // v for v in time)  # key 给出单调不减的趟数函数，bisect_left 按它对每个候选时间求值比较
        )  # 返回找到的最小时间
