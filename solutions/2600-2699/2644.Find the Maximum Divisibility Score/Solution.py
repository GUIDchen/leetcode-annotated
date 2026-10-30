# 题目：2644. 找出可整除性得分最大的整数（Find the Maximum Divisibility Score）
# 思路：对每个候选除数统计 nums 中能被它整除的个数，得分更高就替换，得分打平则取更小的除数。
# 时间复杂度：O(m * n)，m 为除数个数、n 为 nums 长度；空间复杂度：O(1)，只用几个计数变量。
class Solution:  # LeetCode 约定的题解类
    def maxDivScore(self, nums: List[int], divisors: List[int]) -> int:  # nums：被除数数组；divisors：候选除数
        ans, mx = divisors[0], 0  # ans：当前最优除数；mx：当前最高得分
        for div in divisors:  # 逐个尝试每个候选除数
            cnt = sum(x % div == 0 for x in nums)  # bool 求和，得到能被 div 整除的个数
            if mx < cnt:  # 得分更高，直接替换最优解
                mx, ans = cnt, div  # 同时更新最高得分与最优除数
            elif mx == cnt and ans > div:  # 得分打平且该除数更小
                ans = div  # 按题目要求取数值更小的除数
        return ans  # 返回可整除性得分最大的最小除数
