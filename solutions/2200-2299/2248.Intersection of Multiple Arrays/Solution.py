# 题目：2248. 多个数组求交集（Intersection of Multiple Arrays）
# 思路：用值域计数数组统计每个数跨所有数组的出现次数，次数等于数组个数即为公共元素，按下标升序枚举正好得到升序结果。
# 时间复杂度：O(元素总数 + 1000)；空间复杂度：O(1000)，值域计数数组。
class Solution:  # LeetCode 约定的题解类
    def intersection(self, nums: List[List[int]]) -> List[int]:  # nums 为若干数组，返回它们的交集（升序）
        cnt = [0] * 1001  # 值域 1..1000 的计数数组
        for arr in nums:  # 逐个数组统计
            for x in arr:  # 遍历数组中的每个数
                cnt[x] += 1  # 出现一次就加一，累计的是跨所有数组的总次数
        return [x for x, v in enumerate(cnt) if v == len(nums)]  # 列表推导：按下标升序枚举，v 等于数组个数即每个数组都含有该数
