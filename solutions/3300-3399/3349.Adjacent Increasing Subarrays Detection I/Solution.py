# 题目：3349. 检测相邻递增子数组 I（Adjacent Increasing Subarrays Detection I）
# 思路：线性扫描把数组切成极长严格递增段，用 pre/cur 记录前一段与当前段长度，候选答案只可能是 cur//2 或 min(pre, cur)。
# 时间复杂度：O(n)，数组只扫描一遍；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def hasIncreasingSubarrays(self, nums: List[int], k: int) -> bool:  # nums：输入数组；k：要求的两段递增子数组长度
        mx = pre = cur = 0  # 链式赋值：mx 历史最优、pre 前一段长度、cur 当前段长度都置 0
        for i, x in enumerate(nums):  # 同时取得下标 i 与值 x，线性扫描
            cur += 1  # 把当前元素并入当前递增段，段长加一
            if i == len(nums) - 1 or x >= nums[i + 1]:  # 到达末尾，或下一元素不再更大，说明当前递增段到此结束
                mx = max(mx, cur // 2, min(pre, cur))  # 段内对半分 cur // 2，跨段取 min(pre, cur)，三者取最大
                pre, cur = cur, 0  # 元组赋值：当前段变成「前一段」，同时把当前段长度清零
        return mx >= k  # 最大可行长度达到 k，说明存在相邻的两个长度为 k 的递增子数组
