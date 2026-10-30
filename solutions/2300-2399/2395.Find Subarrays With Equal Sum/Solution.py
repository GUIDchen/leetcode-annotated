# 题目：2395. 和相等的子数组（Find Subarrays With Equal Sum）
# 思路：pairwise 依次取出相邻的两个元素，用集合记录它们的和，某个和第二次出现即说明存在两段和相等的子数组。
# 时间复杂度：O(n)，每个相邻对只处理一次；空间复杂度：O(n)，集合最多保存 n-1 个不同的和。
class Solution:  # LeetCode 约定的题解类
    def findSubarrays(self, nums: List[int]) -> bool:  # nums：输入数组；返回值表示是否存在两段和相等的长度为 2 的子数组
        vis = set()  # 集合：记录已经出现过的相邻两元素之和
        for a, b in pairwise(nums):  # 依次取出一对相邻元素，a 在前、b 在后，二者构成一段长度为 2 的子数组
            if (x := a + b) in vis:  # 海象运算符：先算出这一对的和 x，再判断它是否已经出现过
                return True  # 出现过相同的和，说明存在两段和相等的子数组
            vis.add(x)  # 把当前和加入集合，供后面的子数组比较
        return False  # 遍历结束没有出现重复的和，返回 False
