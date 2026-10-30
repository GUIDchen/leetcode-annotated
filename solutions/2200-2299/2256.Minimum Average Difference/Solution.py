# 题目：2256. 最小平均差（Minimum Average Difference）
# 思路：维护前缀和 pre 与后缀和 suf，逐下标求「前半段平均值」与「后半段平均值」之差的绝对值，取最小值。
# 时间复杂度：O(n)，只遍历一次数组；空间复杂度：O(1)，除输入外只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minimumAverageDifference(self, nums: List[int]) -> int:  # nums：输入数组；返回使平均差最小的下标
        pre, suf = 0, sum(nums)  # pre 为前缀和（初值 0），suf 为后缀和（初值是整个数组的总和）
        n = len(nums)  # 数组长度，算除数和判断后半段是否为空都要用到
        ans, mi = 0, inf  # ans 记录答案下标；mi 记录当前最小平均差，先置为正无穷
        for i, x in enumerate(nums):  # 同时取出下标 i 与元素值 x
            pre += x  # 把当前元素并入前缀和
            suf -= x  # 从后缀和中扣掉当前元素
            a = pre // (i + 1)  # 前半段（0..i）的平均值，// 即题目要求的下取整除法
            b = 0 if n - i - 1 == 0 else suf // (n - i - 1)  # 后半段为空时平均值记 0，否则求整除平均值
            if (t := abs(a - b)) < mi:  # 海象运算符：先算出两段平均值之差的绝对值 t，再与当前最优值比较
                ans = i  # 出现了更小的平均差，更新答案下标
                mi = t  # 同步更新当前最小值
        return ans  # 返回使平均差最小的下标
