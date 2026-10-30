# 题目：2393. 严格递增的子数组个数（Count Strictly Increasing Subarrays）
# 思路：cnt 表示以当前元素结尾的严格递增子数组个数，递增则 cnt+1，否则重置为 1，逐个累加。
# 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用两个计数变量。
class Solution:  # LeetCode 约定的题解类
    def countSubarrays(self, nums: List[int]) -> int:  # nums 是待统计数组
        ans = cnt = 1  # ans 统计子数组总数；cnt 表示以当前元素结尾的严格递增子数组个数
        for x, y in pairwise(nums):  # pairwise 依次取出相邻元素对 (x, y)，即 nums[i-1] 与 nums[i]
            if x < y:  # 比前一个大，递增段可以继续延长
                cnt += 1  # 以 y 结尾的递增子数组个数等于前一个的个数再加 1
            else:  # 否则递增段在此中断
                cnt = 1  # 只能单独构成一个长度为 1 的子数组
            ans += cnt  # 累加以 y 结尾的全部严格递增子数组
        return ans  # 返回总数
