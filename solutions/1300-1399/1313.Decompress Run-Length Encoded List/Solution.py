# 题目：1313. 解压缩编码列表（Decompress Run-Length Encoded List）
# 核心思路：编码数组按 (频次, 值) 成对出现，用双层列表推导：外层每隔两位取一对，内层把值重复频次次。
# 时间复杂度：O(n + 答案长度)；空间复杂度：O(答案长度)，即结果列表本身。
class Solution:  # LeetCode 约定的题解类
    def decompressRLElist(self, nums: List[int]) -> List[int]:  # nums 是形如 [f1, v1, f2, v2, ...] 的编码数组
        return [nums[i + 1] for i in range(0, len(nums), 2) for _ in range(nums[i])]  # 外层步长 2 取每对，内层按频次 nums[i] 重复取 nums[i+1]
