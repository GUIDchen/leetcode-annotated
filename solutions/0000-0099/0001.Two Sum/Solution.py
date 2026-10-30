# 题目：1. 两数之和（Two Sum）
# 思路：一次遍历，用哈希表记录「已经见过的值 → 下标」；遍历到 x 时先查补数 target - x 是否出现过。
# 时间复杂度：O(n)，每个元素只访问一次；空间复杂度：O(n)，哈希表最多保存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def twoSum(self, nums: List[int], target: int) -> List[int]:  # nums 是输入数组，target 是目标和
        d = {}  # 哈希表：键是元素值，值是它在数组中的下标
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
            if (y := target - x) in d:  # 海象运算符：先算出补数 y，再判断它是否已经出现过
                return [d[y], i]  # 找到答案，按题目要求返回两个下标
            d[x] = i  # 补数还没出现，把当前值和下标记入哈希表，供后续元素查询
