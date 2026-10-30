# 题目：1131. 绝对值表达式的最大值（Maximum of Absolute Value Expression）
# 思路：把 |a1[i]-a1[j]| + |a2[i]-a2[j]| + |i-j| 展开成四种符号组合下 (a*a1 + b*a2 + i) 之差，符号取遍 (1,-1)、(-1,-1)、(-1,1)、(1,1)；每种组合只需维护表达式的最大值与最小值，其差就是该组合下的最大结果。
# 时间复杂度：O(n)，四种符号组合各扫一遍，常数因子为 4；空间复杂度 O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxAbsValExpr(self, arr1: List[int], arr2: List[int]) -> int:  # arr1、arr2：两个等长数组；返回绝对值表达式的最大值
        dirs = (1, -1, -1, 1, 1)  # 四种符号组合，相邻两项配对得 (1,-1)、(-1,-1)、(-1,1)、(1,1)
        ans = -inf  # ans 初始为负无穷
        for a, b in pairwise(dirs):  # 逐一枚举四种符号组合
            mx, mi = -inf, inf  # mx/mi 分别记录该组合表达式的最大值与最小值
            for i, (x, y) in enumerate(zip(arr1, arr2)):  # i 为下标，x、y 为两个数组的对应元素
                mx = max(mx, a * x + b * y + i)  # 更新该组合表达式的最大值
                mi = min(mi, a * x + b * y + i)  # 更新该组合表达式的最小值
                ans = max(ans, mx - mi)  # 最大值减最小值即为该组合下的最大结果
        return ans  # 返回四种组合中的最大结果
