# 题目：1983. 范围和相等的最宽索引对（Widest Pair of Indices With Equal Range Sum）
# 思路：两数组差数组的前缀和相等，就意味着中间那段区间的和相等；哈希表记录每个前缀和首次出现的下标，取最远距离。
# 时间复杂度：O(n)，每个元素一次哈希操作；空间复杂度：O(n)，存前缀和到下标的映射。
class Solution:  # LeetCode 约定的题解类
    def widestPairOfIndices(self, nums1: List[int], nums2: List[int]) -> int:  # 返回满足条件和相等的最大区间长度
        d = {0: -1}  # 空前缀的差为 0，虚拟下标 -1，使从 0 开始的区间也能被统计
        ans = s = 0  # ans：最宽长度；s：当前前缀差
        for i, (a, b) in enumerate(zip(nums1, nums2)):  # i 是下标，(a, b) 是两个数组同一位置的元素
            s += a - b  # 更新前缀差 s
            if s in d:  # 这个前缀差出现过，说明 d[s]+1..i 两数组和相等
                ans = max(ans, i - d[s])  # 用当前区间长度更新答案，保留最早下标才能最宽
            else:  # 前缀差第一次出现
                d[s] = i  # 记录下标，作为后续区间的左端点
        return ans  # 返回最宽长度，没有则返回 0
