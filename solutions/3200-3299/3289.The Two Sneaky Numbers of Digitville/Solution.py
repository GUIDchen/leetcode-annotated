# 题目：3289. 数字小镇中的捣蛋鬼（The Two Sneaky Numbers of Digitville）
# 思路：用 Counter 统计每个数的出现次数，出现 2 次的那两个数就是答案。
# 时间复杂度：O(n)；空间复杂度：O(n)，计数器最多存 n 个键。
class Solution:  # LeetCode 约定的题解类
    def getSneakyNumbers(self, nums: List[int]) -> List[int]:  # nums：长度 n+2、恰有两个数重复出现的数组
        cnt = Counter(nums)  # 统计每个数出现的次数，得到「值 → 频次」的映射
        return [x for x, v in cnt.items() if v == 2]  # 筛出频次恰为 2 的数，即两个捣蛋鬼
