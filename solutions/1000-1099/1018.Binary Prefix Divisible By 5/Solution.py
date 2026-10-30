# 题目：1018. 可被 5 整除的二进制前缀（Binary Prefix Divisible By 5）
# 思路：从左到右滚动维护前缀值对 5 的余数：x = (x << 1 | v) % 5，余数为 0 就说明该前缀能被 5 整除。
# 时间复杂度：O(n)，一趟遍历；空间复杂度：O(n)，用于存放每个前缀的判断结果。
class Solution:  # LeetCode 约定的题解类
    def prefixesDivBy5(self, nums: List[int]) -> List[bool]:  # nums：由 0 和 1 组成的数组
        ans = []  # 逐个前缀的判断结果
        x = 0  # 当前前缀值对 5 取模后的余数
        for v in nums:  # 依次把每个比特接到前缀的末尾
            x = (x << 1 | v) % 5  # 左移一位并加上新比特（等价于原值乘 2 加 v），同时取模防溢出
            ans.append(x == 0)  # 余数为 0 说明这个前缀能被 5 整除，记录 True，否则 False
        return ans  # 返回所有前缀的判断结果
