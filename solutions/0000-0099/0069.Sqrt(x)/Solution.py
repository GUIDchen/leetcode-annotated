# 题目：69. x 的平方根（Sqrt(x)）
# 思路：在 [0, x] 上二分答案，找最大的 mid 满足 mid*mid <= x；取上中位数配合 l = mid 的写法避免死循环。
# 时间复杂度：O(log x)，区间每次折半；空间复杂度：O(1)，只使用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def mySqrt(self, x: int) -> int:  # x：待求平方根的非负整数
        l, r = 0, x  # 答案的闭区间上下界，平方根必在 [0, x] 中
        while l < r:  # 区间还没缩成一个点就继续二分
            mid = (l + r + 1) >> 1  # 取上中位数（+1 后右移一位即除以 2），保证 l = mid 时区间仍会缩小
            if mid > x // mid:  # 用整除代替 mid*mid 比较，结果等价且在其它语言里也不会溢出；成立说明 mid 偏大
                r = mid - 1  # 答案在左半边，把右界收缩到 mid 左侧
            else:
                l = mid  # mid*mid <= x，mid 可能是答案，保留并继续往更大处找
        return l  # 收敛后 l 即向下取整的平方根
