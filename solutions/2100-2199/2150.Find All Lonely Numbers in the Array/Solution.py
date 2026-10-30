# 题目：2150. 找出数组中的所有孤独数字（Find All Lonely Numbers in the Array）
# 思路：用 Counter 统计每个数字的出现次数，再筛出「只出现一次且 x-1、x+1 计数为 0」的数字。
# 时间复杂度：O(n)，建表与遍历各一遍；空间复杂度：O(n)，计数器存放至多 n 个不同数字。
class Solution:  # LeetCode 约定的题解类
    def findLonely(self, nums: List[int]) -> List[int]:  # nums：输入数组；返回所有孤独数字
        cnt = Counter(nums)  # Counter 计数器：统计每个数字出现的次数
        return [  # 返回满足孤独条件的数字列表（列表推导式）
            x for x, v in cnt.items() if v == 1 and cnt[x - 1] == 0 and cnt[x + 1] == 0  # 只出现一次，且 x-1、x+1 的计数都是 0（Counter 访问不存在的键返回 0）
        ]  # 推导式结束
