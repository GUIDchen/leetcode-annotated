# 题目：2513. 最小化两个数组中的最大值（Minimize the Maximum of Two Arrays）
# 思路：可行性与上界 x 单调相关，因此在 [0, 10^10) 上二分第一个满足条件的位置；判定时用整除计数算出一段区间内可用的数字个数。
# 时间复杂度：O(log 10^10)，每次判定 O(1)；空间复杂度：O(1)，只用到常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimizeSet(  # 返回两个数组最大值的最小可能值
        self, divisor1: int, divisor2: int, uniqueCnt1: int, uniqueCnt2: int  # 两个约数与两个数组各需的元素个数
    ) -> int:  # 返回最小的可行上界
        def f(x):  # 判定上界 x 是否可行
            cnt1 = x // divisor1 * (divisor1 - 1) + x % divisor1  # [1, x] 中不能被 divisor1 整除的个数
            cnt2 = x // divisor2 * (divisor2 - 1) + x % divisor2  # [1, x] 中不能被 divisor2 整除的个数
            cnt = x // divisor * (divisor - 1) + x % divisor  # [1, x] 中两个约数都不能整除的个数
            return (  # 三个条件同时成立才说明 x 可行
                cnt1 >= uniqueCnt1  # 第一个数组能凑够 uniqueCnt1 个互异元素
                and cnt2 >= uniqueCnt2  # 第二个数组能凑够 uniqueCnt2 个互异元素
                and cnt >= uniqueCnt1 + uniqueCnt2  # 两个数组合起来也不冲突
            )

        divisor = lcm(divisor1, divisor2)  # 先算最小公倍数，供内层函数 f 通过闭包使用
        return bisect_left(range(10**10), True, key=f)  # 在单调布尔序列上二分出第一个 True 的下标
