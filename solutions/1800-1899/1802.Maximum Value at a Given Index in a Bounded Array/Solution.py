# 题目：1802. 有界数组中指定下标处的最大值（Maximum Value at a Given Index in a Bounded Array）
# 思路：二分峰值 x，用等差数列求和快速算出「两侧逐 1 递减且不小于 1」时的最小总和，判断是否不超过 maxSum，从而收敛到最大值。
# 时间复杂度：O(log maxSum)，二分次数为对数级；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxValue(self, n: int, index: int, maxSum: int) -> int:  # n 为数组长度，index 为目标下标，maxSum 为元素总和上限
        def sum(x, cnt):  # 计算 cnt 个位置以 x 为峰值、逐 1 递减时所需的最少元素和
            return (  # 求和表达式开始：结果由下面的三元表达式决定
                (x + x - cnt + 1) * cnt // 2 if x >= cnt else (x + 1) * x // 2 + cnt - x  # x >= cnt 时用等差公式；否则先减到 1，剩余位置全填 1
            )  # 求和表达式结束

        left, right = 1, maxSum  # 答案下界为 1，上界为 maxSum
        while left < right:  # 二分查找满足总和限制的最大峰值
            mid = (left + right + 1) >> 1  # 取上中位数，避免 left = mid 时出现死循环
            if sum(mid - 1, index) + sum(mid, n - index) <= maxSum:  # 左侧 index 个位置与右侧 n-index 个位置的最小和不超过 maxSum
                left = mid  # 可行：记下 mid 并继续向右找更大的值
            else:  # 否则 mid 太大
                right = mid - 1  # 把上界压到 mid - 1
        return left  # 循环结束 left == right，即最大可行峰值
