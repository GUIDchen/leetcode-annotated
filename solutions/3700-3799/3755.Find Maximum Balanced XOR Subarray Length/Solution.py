# 3755. 最大平衡异或子数组的长度（Find Maximum Balanced XOR Subarray Length）
# 核心思路：平衡子数组要求偶数个数与奇数个数相等且异或和为 0；用（前缀异或, 偶数个数-奇数个数）作状态键，相同键的两前缀之间即为平衡区间，取最大下标差。
# 复杂度：时间 O(n)，空间 O(n)。
class Solution:  # 定义解法类
    def maxBalancedSubarray(self, nums: List[int]) -> int:  # 接口：返回最长的平衡异或子数组长度
        d = {(0, 0): -1}  # 字典记录 (前缀异或, 偶数个数-奇数个数) 首次出现的下标，空前缀记为 -1
        a = b = 0  # a 为前缀异或和，b 为偶数个数与奇数个数之差
        ans = 0  # ans 保存当前找到的最大区间长度
        for i, x in enumerate(nums):  # 从左到右枚举子数组右端点 i
            a ^= x  # 把当前元素异或进前缀异或和
            b += 1 if x % 2 == 0 else -1  # 偶数个数增多、奇数个数增多分别对应加一减一
            if (a, b) in d:  # 如果该状态之前出现过，说明中间这一段是平衡的
                ans = max(ans, i - d[(a, b)])  # 用 i 减去首次出现下标更新最大长度
            else:  # 否则说明这是该状态第一次出现
                d[(a, b)] = i  # 记录它的下标，供后面求长度
        return ans  # 返回最长平衡异或子数组长度
