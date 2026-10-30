# 题目：673. 最长递增子序列的个数（Number of Longest Increasing Subsequence）
# 思路：O(n^2) 动态规划，f[i] 是以 i 结尾的最长递增子序列长度，cnt[i] 是对应方案数，边转移边维护全局最优值。
# 时间复杂度：O(n^2)，双重循环枚举所有数对；空间复杂度：O(n)，两个长度为 n 的数组。
class Solution:  # LeetCode 约定的题解类
    def findNumberOfLIS(self, nums: List[int]) -> int:  # nums：输入数组
        n = len(nums)  # 数组长度
        f = [1] * n  # f[i]：以 nums[i] 结尾的最长递增子序列长度，单元素长度为 1
        cnt = [1] * n  # cnt[i]：达到 f[i] 长度的方案数，初始只有自身一种
        mx = 0  # mx：目前见过的全局最长长度
        for i in range(n):  # 依次计算每个位置作为结尾的答案
            for j in range(i):  # 枚举 i 之前的所有位置作为前驱
                if nums[j] < nums[i]:  # 严格递增才允许接在 j 后面
                    if f[i] < f[j] + 1:  # 找到更长的接法，长度和方案数一起覆盖
                        f[i] = f[j] + 1  # 更新以 i 结尾的最长长度
                        cnt[i] = cnt[j]  # 方案数改为前驱 j 的方案数
                    elif f[i] == f[j] + 1:  # 另一种接法也能得到同样长度
                        cnt[i] += cnt[j]  # 方案数累加
            if mx < f[i]:  # 出现更长的递增子序列
                mx = f[i]  # 更新全局最长长度
                ans = cnt[i]  # 方案总数重置为当前位置的方案数
            elif mx == f[i]:  # 与全局最长长度相同的另一种结尾
                ans += cnt[i]  # 把它的方案数累加进总数
        return ans  # 返回最长递增子序列的个数
