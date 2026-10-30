# 题目：3350. 检测相邻递增子数组 II（Adjacent Increasing Subarrays Detection II）
# 思路：极长递增段划分后，最大合法长度只能来自段内对半分 cur//2 或相邻两段取小 min(pre, cur)，取全局最大即可。
# 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxIncreasingSubarrays(self, nums: List[int]) -> int:  # nums：输入数组
        ans = pre = cur = 0  # 链式赋值：ans 历史最优、pre 前一段长度、cur 当前段长度都置 0
        for i, x in enumerate(nums):  # 同时取得下标 i 与值 x，线性扫描
            cur += 1  # 把当前元素并入当前递增段，段长加一
            if i == len(nums) - 1 or x >= nums[i + 1]:  # 到达末尾，或下一元素不再更大，说明当前递增段到此结束
                ans = max(ans, cur // 2, min(pre, cur))  # 段内对半分 cur // 2，跨段取 min(pre, cur)，三者取最大
                pre, cur = cur, 0  # 元组赋值：当前段变成「前一段」，同时把当前段长度清零
        return ans  # 返回全局最大的合法子数组长度
