# 3940. 限制有序数组中的元素出现次数 / Limit Occurrences in Sorted Array
# 核心思路：利用数组有序性，用快慢指针原地覆盖，连续相同元素累计未超过 k 个就保留。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # 题解类定义
    def limitOccurrences(self, nums: list[int], k: int) -> list[int]:  # 主函数：每个元素最多保留 k 次
        n = len(nums)  # 数组长度
        cnt = l = 1  # cnt 为当前元素已保留次数，l 为写指针
        for r in range(1, n):  # r 为读指针，从第二个元素开始
            if nums[r] != nums[r - 1]:  # 遇到与上一个不同的新元素
                cnt = 1  # 保留计数重置为 1
            else:  # 仍是同一个元素
                cnt += 1  # 保留计数累加
            if cnt <= k:  # 尚未超过允许的出现次数
                nums[l] = nums[r]  # 原地写入到写指针位置
                l += 1  # 写指针后移
        return nums[:l]  # 返回前 l 个元素组成的结果
