# 题目：2455. 可被三整除的偶数的平均值（Average Value of Even Numbers That Are Divisible by Three）
# 思路：被 2 和 3 同时整除等价于被 6 整除，一次遍历筛选 %6==0 的数并累加、计数，最后求整数平均。
# 时间复杂度：O(n)，遍历一遍数组；空间复杂度：O(1)，只用两个计数变量。
class Solution:  # LeetCode 约定的题解类
    def averageValue(self, nums: List[int]) -> int:  # nums：输入数组，返回满足条件的数的平均值
        s = n = 0  # 同时初始化：s 为满足条件的数之和，n 为满足条件的数的个数
        for x in nums:  # 依次遍历数组中的每个元素
            if x % 6 == 0:  # 能被 6 整除即“能被三整除的偶数”
                s += x  # 把当前数累加进总和
                n += 1  # 满足条件的个数加一
        return 0 if n == 0 else s // n  # 个数为 0 时按题意返回 0，否则用整除得到向下取整的平均值
