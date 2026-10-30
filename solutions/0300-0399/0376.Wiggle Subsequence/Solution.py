# 题目：376. 摆动序列（Wiggle Subsequence）
# 思路：线性 DP，f[i] / g[i] 分别表示以 i 结尾且最后一步为上升 / 下降的最长摆动子序列长度，枚举前驱转移。
# 时间复杂度：O(n^2)，双重循环；空间复杂度：O(n)，两个 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def wiggleMaxLength(self, nums: List[int]) -> int:  # nums 为输入序列，返回最长摆动子序列的长度
        n = len(nums)  # 序列长度
        ans = 1  # 任意一个元素本身就是摆动序列，答案至少为 1
        f = [1] * n  # f[i]：以 i 结尾、最后一段是上升的最长摆动子序列长度，初值为 1
        g = [1] * n  # g[i]：以 i 结尾、最后一段是下降的最长摆动子序列长度，初值为 1
        for i in range(1, n):  # 枚举子序列的结尾下标 i
            for j in range(i):  # 枚举前一个元素 j，尝试把 i 接在 j 后面
                if nums[j] < nums[i]:  # nums[j] < nums[i]：最后一步是上升
                    f[i] = max(f[i], g[j] + 1)  # 上升前必须处于下降段，故用 g[j] 接上再长度加 1
                elif nums[j] > nums[i]:  # nums[j] > nums[i]：最后一步是下降
                    g[i] = max(g[i], f[j] + 1)  # 下降前必须处于上升段，故用 f[j] 接上再长度加 1
            ans = max(ans, f[i], g[i])  # 用当前结尾的两种状态更新全局最大值
        return ans  # 返回最长摆动子序列长度
