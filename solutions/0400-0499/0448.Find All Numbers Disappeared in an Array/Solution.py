# 题目：448. 找到所有数组中消失的数字（Find All Numbers Disappeared in an Array）
# 思路：先把数组转成集合以便 O(1) 判断某数字是否存在，再在 1..n 范围内筛出不在集合中的数字。
# 时间复杂度：O(n)，建集合与遍历范围各一遍；空间复杂度：O(n)，集合最多存 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def findDisappearedNumbers(self, nums: List[int]) -> List[int]:  # nums：长度为 n、元素在 1..n 内的数组；返回其中缺失的数字列表
        s = set(nums)  # 用集合替代数组标记，判断某个数字是否出现过只需 O(1)
        return [x for x in range(1, len(nums) + 1) if x not in s]  # 在 1..n 中筛出不在集合里的数，列表推导保证结果升序
