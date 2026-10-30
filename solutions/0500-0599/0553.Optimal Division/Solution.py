# 题目：553. 最优除法（Optimal Division）
# 核心思路：第一个数当被除数，从第二个数起整体加括号当除数，后面的数都变成分母因子，值最大。
# 时间复杂度：O(n)，一次线性拼接；空间复杂度：O(n)，用于保存结果字符串。
class Solution:  # LeetCode 约定的题解类
    def optimalDivision(self, nums: List[int]) -> str:  # nums 为正整数列表，返回使结果最大的除法表达式
        n = len(nums)  # 元素个数，决定走哪个分支
        if n == 1:  # 只有一个数时无需括号
            return str(nums[0])  # 直接转成字符串返回
        if n == 2:  # 两个数时括号无意义，固定写成 a/b
            return f'{nums[0]}/{nums[1]}'  # 用 f-string 拼出 a/b
        return f'{nums[0]}/({"/".join(map(str, nums[1:]))})'  # 多个数：首个数除以括号内其余数的连除，值最大
