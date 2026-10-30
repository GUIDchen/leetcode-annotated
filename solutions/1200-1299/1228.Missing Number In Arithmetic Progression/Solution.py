# 题目：1228. 等差数列中缺失的数字（Missing Number In Arithmetic Progression）
# 思路：完整等差数列共 len(arr)+1 项，用 (首项 + 末项) × 项数 / 2 求总和，减去 sum(arr) 即得缺失值。
# 时间复杂度：O(n)，sum 扫一遍数组；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def missingNumber(self, arr: List[int]) -> int:  # arr：少了恰好一个元素的等差数列，返回缺失的那个数
        return (arr[0] + arr[-1]) * (len(arr) + 1) // 2 - sum(arr)  # 完整数列（len+1 项）的总和减去实际总和，差就是缺失数字；// 保证整除
