# 题目：2198. 单因数三元组 🔒（Number of Single Divisor Triplets）
# 思路：把值域 1..100 的频次统计出来后枚举三个「值」，再用频次乘积公式直接算出对应的有序下标三元组个数。
# 时间复杂度：O(n + V^3)，V 为值域上界 100；空间复杂度：O(V)，Counter 最多存 100 个键。
class Solution:  # LeetCode 约定的题解类
    def singleDivisorTriplet(self, nums: List[int]) -> int:  # nums：输入数组；返回单因数三元组的个数
        cnt = Counter(nums)  # 统计每个值出现的次数：键是值，值是频次
        ans = 0  # 累加答案
        for a, x in cnt.items():  # 枚举第一个数的取值 a 及其频次 x（按值枚举，避免对下标做三重循环）
            for b, y in cnt.items():  # 枚举第二个数的取值 b 及其频次 y
                for c, z in cnt.items():  # 枚举第三个数的取值 c 及其频次 z
                    s = a + b + c  # 三个值之和
                    if sum(s % v == 0 for v in (a, b, c)) == 1:  # 生成器对三个值分别判断能否整除 s，求和恰为 1 说明是单因数三元组
                        if a == b:  # 前两个值相同：两个不同下标取到同一个值 a
                            ans += x * (x - 1) * z  # 有序选两个不同下标的 a（x*(x-1) 种），再选一个 c：x*(x-1)*z
                        elif a == c:  # 第一和第三个值相同
                            ans += x * (x - 1) * y  # 有序选两个不同下标的 a，再选一个 b：x*(x-1)*y
                        elif b == c:  # 后两个值相同
                            ans += x * y * (y - 1)  # 选一个 a，再有序选两个不同下标的 b：x*y*(y-1)
                        else:  # 三个值互不相同
                            ans += x * y * z  # 各取一个下标相乘：x*y*z，值组合的不同排列会被分别枚举累加
        return ans  # 返回符合条件的三元组总数
