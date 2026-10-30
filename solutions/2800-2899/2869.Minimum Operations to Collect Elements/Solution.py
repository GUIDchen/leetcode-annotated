# 题目：2869. 收集元素的最少操作次数（Minimum Operations to Collect Elements）
# 思路：从数组尾部倒序扫描，用布尔列表标记 1..k 中已被收集的数，集齐 k 个时立刻返回已取走的元素个数。
# 时间复杂度：O(n)，最坏倒序扫完整个数组；空间复杂度：O(k)，标记列表只开 k 个位置。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 表示要收齐 1..k 这 k 个数
        is_added = [False] * k  # 标记列表：is_added[x-1] 为真表示数值 x 已经被收集
        count = 0  # 已收集到的不同数值个数
        n = len(nums)  # 记录数组长度，后面把下标换算成操作次数要用
        for i in range(n - 1, -1, -1):  # 从末尾倒序扫描：每次操作取走的正是当前最后一个元素
            if nums[i] > k or is_added[nums[i] - 1]:  # 大于 k 的数用不上，重复出现的数也不该重复计数
                continue  # 直接跳过，不算一次有效收集
            is_added[nums[i] - 1] = True  # 把数值 nums[i] 标记为已收集
            count += 1  # 有效收集数加一
            if count == k:  # 1..k 全部收齐
                return n - i  # 从下标 n-1 扫到 i，一共取了 n-i 次操作
