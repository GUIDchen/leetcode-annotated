# 题目：3300. 替换为数位和以后的最小元素（Minimum Element After Replacement With Digit Sum）
# 思路：把每个元素替换成它的数位和，再取最小值（写成一个生成器表达式）。
# 时间复杂度：O(n log M)，每个元素需逐位拆分（M 为元素大小）；空间复杂度：O(1)，不额外存数组。
class Solution:  # LeetCode 约定的题解类
    def minElement(self, nums: List[int]) -> int:  # nums：输入数组；返回替换后的最小元素
        return min(sum(int(b) for b in str(x)) for x in nums)  # 对每个元素把十进制字符串的每位数字转成整数求和，最后取所有数位和的最小值
