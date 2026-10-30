# 题目：3158. 求出出现两次数字的 XOR 值（Find the XOR of Numbers Which Appear Twice）
# 核心思路：先用 Counter 统计每个值的出现次数，再用列表推导筛出次数恰为 2 的值，最后用 reduce(xor, ..., 0) 把它们全部异或起来。
# 时间复杂度：O(n)，统计与筛选各扫一遍；空间复杂度：O(n)，Counter 最多保存 n 个不同值。
class Solution:  # LeetCode 约定的题解类
    def duplicateNumbersXOR(self, nums: List[int]) -> int:  # nums：输入数组，返回出现两次的所有数字的异或值
        cnt = Counter(nums)  # Counter 统计每个值出现次数，得到「值 → 次数」的映射
        return reduce(xor, [x for x, v in cnt.items() if v == 2], 0)  # 筛出次数为 2 的值并逐个异或；初始值 0 保证空列表时也返回 0
