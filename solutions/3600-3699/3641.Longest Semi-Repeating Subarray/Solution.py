# 题目：3641. 最长半重复子数组（Longest Semi-Repeating Subarray）
# 核心思路：滑动窗口。窗口内记录每个值的出现次数，以及「出现次数恰好为 2 的不同值个数」cur；右端每纳入一个元素就更新 cur，一旦 cur 超过 k 就不断右移左端收缩窗口，窗口合法时用其长度更新答案。
# 复杂度：时间 O(n)，左右指针各自最多右移 n 次；空间 O(n)，哈希表最多保存窗口内不同值的个数。
class Solution:  # LeetCode 题解类
    def longestSubarray(self, nums: List[int], k: int) -> int:  # nums：输入数组；k：允许「恰好出现两次」的元素种类数上限
        cnt = defaultdict(int)  # 滑动窗口内每个值的出现次数（缺省为 0）
        ans = cur = l = 0  # ans：最长长度；cur：窗口内恰出现两次的种类数；l：窗口左端
        for r, x in enumerate(nums):  # 枚举窗口右端 r，x 为当前元素
            cnt[x] += 1  # 新元素计数 +1
            cur += cnt[x] == 2  # 计数变成 2 时，恰为两次的种类数 +1（布尔值当 0/1 用）
            while cur > k:  # 超出上限，收缩左端
                cnt[nums[l]] -= 1  # 左端元素计数 -1
                cur -= cnt[nums[l]] == 1  # 减后为 1 说明它不再是「恰好两次」，种类数 -1
                l += 1  # 左指针右移
            ans = max(ans, r - l + 1)  # 用当前窗口长度更新答案
        return ans  # 返回最长合法长度
