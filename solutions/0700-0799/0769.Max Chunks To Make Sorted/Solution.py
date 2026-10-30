# 题目：769. 最多能完成排序的块（Max Chunks To Make Sorted）
# 核心思路：arr 是 0..n-1 的排列，前缀最大值 mx 等于下标 i 时前 i+1 个数正好是 0..i，可以切一刀。
# 时间复杂度 O(n)（一次线性扫描）；空间复杂度 O(1)（只用到两个变量）。
class Solution:  # LeetCode 约定的题解类
    def maxChunksToSorted(self, arr: List[int]) -> int:  # arr：0..n-1 的排列；返回最多能切分的块数
        mx = ans = 0  # mx 记录前缀最大值，ans 记录块数，同时初始化为 0
        for i, v in enumerate(arr):  # 同时取得下标 i 与元素值 v
            mx = max(mx, v)  # 更新前 i+1 个元素的最大值
            if i == mx:  # 前缀最大值等于下标，说明前 i+1 个数正好是 0..i，可以切一刀
                ans += 1  # 块数加一
        return ans  # 返回最多块数
