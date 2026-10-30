# 题目：4083. 使相邻元素按位异或非零的最少删除次数（Minimum Deletions to Make Array Sharp）
# 核心思路：数组已有序，相邻两元素按位异或为 0 当且仅当二者相等；要让所有相邻异或都不为零，每出现一对相等相邻元素删掉其中一个即可，故答案为相等相邻对的个数。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minDeletions(self, nums: list[int]) -> int:  # nums：已排序数组；返回使相邻异或全非零的最少删除次数
        return sum(x == y for x, y in pairwise(nums))  # pairwise 依次给出相邻对，布尔值之和即为需要删除的元素个数
