# 3840. 打家劫舍 V / House Robber V（中等）
# 核心思路：线性 DP，f 表示不偷当前房屋的最大收益、g 表示偷当前房屋的最大收益；相邻两间颜色相同则不能同时偷，偷 i 只能接 f；颜色不同时偷 i 可以接 max(f, g)。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # LeetCode 要求的类名
    def rob(self, nums: List[int], colors: List[int]) -> int:  # 返回满足颜色限制的最大收益
        n = len(nums)  # 房屋数量
        f, g = 0, nums[0]  # f：不偷第 0 间的收益；g：偷第 0 间的收益
        for i in range(1, n):  # 从第 1 间开始逐间递推
            if colors[i - 1] == colors[i]:  # 相邻两间颜色相同，不能同时偷
                f, g = max(f, g), f + nums[i]  # 元组同时赋值：不偷 i 取前两状态较优值，偷 i 只能接不偷 i-1
            else:  # 颜色不同，可以连续偷两间
                f, g = max(f, g), max(f, g) + nums[i]  # 元组同时赋值：不偷 i 取前两状态较优值，偷 i 可接前面任一状态
        return max(f, g)  # 最后一间偷与不偷取较大者
