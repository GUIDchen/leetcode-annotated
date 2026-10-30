# 题目：961. 在长度 2N 的数组中找出重复 N 次的元素（N-Repeated Element in Size 2N Array）
# 思路：遍历数组，用集合记录见过的元素；第一个第二次出现的元素就是答案。
# 时间复杂度：O(n)，最多遍历一遍数组；空间复杂度：O(n)，集合最多保存 n 个不同元素。
class Solution:  # LeetCode 约定的题解类
    def repeatedNTimes(self, nums: List[int]) -> int:  # nums 中有一个元素重复了 N 次，返回这个元素
        s = set()  # 集合记录已经出现过的元素
        for x in nums:  # 依次遍历数组中的每个元素
            if x in s:  # 这个元素之前已经出现过
                return x  # 它就是重复 N 次的那个元素
            s.add(x)  # 第一次见到，先记录下来
