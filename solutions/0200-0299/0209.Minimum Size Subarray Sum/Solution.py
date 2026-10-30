# 题目：209. 长度最小的子数组（Minimum Size Subarray Sum）
# 思路：前缀和 + 二分。对每个左端点 i，二分找到第一个满足 s[j] - s[i] >= target 的 j，用 j - i 更新答案。
# 时间复杂度：O(n log n)，n 次二分每次 O(log n)；空间复杂度：O(n)，前缀和列表长度为 n + 1。
class Solution:  # LeetCode 约定的题解类
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:  # target 是目标和，nums 是正整数数组
        n = len(nums)  # 数组长度
        s = list(accumulate(nums, initial=0))  # 前缀和：s[i] 表示前 i 个元素之和，长度 n + 1（依赖判题器已导入 accumulate）
        ans = n + 1  # 答案先设为不可能取到的 n + 1，方便后面取 min
        for i, x in enumerate(s):  # 枚举左端点对应的前缀和下标 i 与其值 x
            j = bisect_left(s, x + target)  # 二分查找第一个使 s[j] - x >= target 的下标 j（依赖判题器已导入 bisect_left）
            if j <= n:  # 右端点存在，即 j 没有超出前缀和范围
                ans = min(ans, j - i)  # 用当前子数组长度 j - i 更新最小长度
        return ans if ans <= n else 0  # 从未更新过说明不存在满足条件的子数组，按题意返回 0
