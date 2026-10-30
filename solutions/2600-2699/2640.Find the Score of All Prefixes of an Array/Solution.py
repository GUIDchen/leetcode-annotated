# 题目：2640. 一个数组所有前缀的分数（Find the Score of All Prefixes of an Array）
# 思路：一遍扫描，维护前缀最大值 mx 与前一个前缀的分数，按定义递推出当前前缀的分数。
# 时间复杂度：O(n)，只遍历一次；空间复杂度：O(n)，答案数组本身就是返回值。
class Solution:  # LeetCode 约定的题解类
    def findPrefixScore(self, nums: List[int]) -> List[int]:  # nums 是输入的整数数组
        n = len(nums)  # 数组长度
        ans = [0] * n  # 预先分配答案数组，逐个前缀填充
        mx = 0  # 当前前缀内的最大值；元素非负，所以初值取 0
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
            mx = max(mx, x)  # 把 x 纳入后更新前缀最大值
            ans[i] = x + mx + (0 if i == 0 else ans[i - 1])  # 当前分数 = x + 前缀最大值 + 前一个前缀的分数
        return ans  # 返回所有前缀的分数
