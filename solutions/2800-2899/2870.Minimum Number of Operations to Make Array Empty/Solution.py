# 题目：2870. 使数组为空的最少操作次数（Minimum Number of Operations to Make Array Empty）
# 思路：用 Counter 统计每个值的出现次数，次数为 1 则无解；否则尽量每次删 3 个，操作数为 ceil(c / 3) = (c + 2) // 3。
# 时间复杂度：O(n)，统计词频与遍历计数各 O(n)；空间复杂度：O(n)，字典存不同数值的计数。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int]) -> int:  # nums 为输入数组，返回最少操作次数（无解返回 -1）
        count = Counter(nums)  # 用 Counter 统计每个值的出现次数（判题环境已内置 Counter，无需额外 import）
        ans = 0  # 累计最少操作次数
        for c in count.values():  # 只需遍历每种数值的出现次数
            if c == 1:  # 只剩 1 个：无法按 2 个或 3 个一组删除，无解
                return -1  # 直接返回 -1 表示无法清空数组
            ans += (c + 2) // 3  # 向上取整的除法：等价于 ceil(c / 3)，删 3 个最优
        return ans  # 返回最少操作次数
