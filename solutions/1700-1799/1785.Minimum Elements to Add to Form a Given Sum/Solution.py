# 题目：1785. 构成特定和需要添加的最少元素（Minimum Elements to Add to Form a Given Sum）
# 思路：先算出数组和与目标值 goal 的差值，每个可加元素的绝对值不超过 limit，最少个数就是差值的向上取整。
# 时间复杂度：O(n)，一次遍历求和；空间复杂度：O(1)，只用到常数个变量。
class Solution:  # LeetCode 约定的题解类
    def minElements(self, nums: List[int], limit: int, goal: int) -> int:  # nums 是原数组，limit 是绝对值上限，goal 是目标和
        d = abs(sum(nums) - goal)  # 还差的绝对值，Python 整数不会溢出
        return (d + limit - 1) // limit  # 向上取整的整数写法：(d + limit - 1) // limit
