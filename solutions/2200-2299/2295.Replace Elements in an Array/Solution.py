# 题目：2295. 替换数组中的元素（Replace Elements in an Array）
# 思路：用字典维护「值 → 下标」，每次替换靠它 O(1) 定位，并让新值接管旧下标。
# 时间复杂度：O(n + m)，n 为数组长度、m 为操作次数；空间复杂度：O(n)，字典存 n 个值。
class Solution:  # LeetCode 约定的题解类
    def arrayChange(self, nums: List[int], operations: List[List[int]]) -> List[int]:  # nums：初始数组；operations：若干「把 x 换成 y」的操作
        d = {x: i for i, x in enumerate(nums)}  # 字典推导式建立「值 → 下标」索引
        for x, y in operations:  # 按顺序执行每一次替换
            nums[d[x]] = y  # 用字典定位 x 的下标，把该位置改写成 y
            d[y] = d[x]  # y 继承 x 的下标，保证后续操作仍能定位到它
        return nums  # 返回最终数组
