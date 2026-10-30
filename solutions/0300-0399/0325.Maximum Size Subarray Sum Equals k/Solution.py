# 题目：325. 和等于 k 的最长子数组长度（Maximum Size Subarray Sum Equals k）
# 思路：用前缀和把子数组和转成两个前缀和之差，哈希表记录每个前缀和最早出现的下标，一次遍历即可求最长长度。
# 时间复杂度：O(n)，每个元素只处理一次；空间复杂度：O(n)，哈希表最多存 n+1 个前缀和。
class Solution:  # LeetCode 约定的题解类
    def maxSubArrayLen(self, nums: List[int], k: int) -> int:  # nums 是整数数组，k 是目标和，返回和等于 k 的最长子数组长度
        d = {0: -1}  # 哈希表「前缀和 → 最早出现的下标」；空前缀和 0 的下标记为 -1
        ans = s = 0  # ans 记录最长长度，s 是滚动前缀和，初始都是 0
        for i, x in enumerate(nums):  # 同时取出下标 i 和元素 x
            s += x  # 累加得到前缀和 s = nums[0..i] 的和
            if s - k in d:  # 存在前缀和 s-k，说明两者之间的那段区间和正好是 k
                ans = max(ans, i - d[s - k])  # 用区间长度 i - d[s-k] 更新最大值
            if s not in d:  # 只记录前缀和第一次出现的位置，越早越有利于取更长的区间
                d[s] = i  # 首次出现，记下当前下标
        return ans  # 返回最长长度，找不到合法子数组时为 0
