# 题目：1300. 转变数组后最接近目标值的数组和（Sum of Mutated Array Closest to Target）
# 思路：排序后枚举所有候选 value（0..max），用前缀和与 bisect_right 在 O(log n) 内算出该 value 下的数组和。
# 时间复杂度：O(n log n + max*log n)，max 为数组最大值；空间复杂度：O(n)，前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def findBestValue(self, arr: List[int], target: int) -> int:  # arr：输入数组；target：目标值
        arr.sort()  # 升序排序，便于前缀和与二分
        s = list(accumulate(arr, initial=0))  # 前缀和，长度 n+1，s[i] 表示前 i 个元素之和
        ans, diff = 0, inf  # ans：当前最优 value；diff：当前最小绝对差
        for value in range(max(arr) + 1):  # 枚举 0 到数组最大值之间的所有候选
            i = bisect_right(arr, value)  # 第一个大于 value 的下标，前 i 个不需要被截断
            d = abs(s[i] + (len(arr) - i) * value - target)  # 前 i 个保留原值，其余统一变成 value
            if diff > d:  # 严格大于，保证并列时保留更小的 value
                diff = d  # 更新最小绝对差
                ans = value  # 记录更优的 value
        return ans  # 返回使数组和最接近目标值的 value
