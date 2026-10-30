# 题目：523. 连续的子数组和（Continuous Subarray Sum）
# 思路：前缀和取模 k，同一余数在距离大于 1 处再次出现，说明中间这段子数组的和是 k 的倍数。
# 时间复杂度：O(n)，遍历一次并用哈希表 O(1) 查询；空间复杂度：O(k)，最多存 k 个不同余数。
class Solution:  # LeetCode 约定的题解类
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:  # nums：非负整数数组；k：除数；返回是否存在长度至少为 2、和是 k 倍数的连续子数组
        d = {0: -1}  # 余数 → 最早下标；预置余数 0 对应下标 -1，便于处理从首元素开始的子数组
        s = 0  # s 记录当前前缀和对 k 取模的余数
        for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
            s = (s + x) % k  # 累加后立刻取模，既防溢出又让余数落在 [0, k) 内
            if s not in d:  # 该余数首次出现
                d[s] = i  # 记录最早下标，保留最长区间
            elif i - d[s] > 1:  # 余数出现过，且两次出现之间至少有 2 个元素
                return True  # 找到合法子数组
        return False  # 遍历结束仍未找到
