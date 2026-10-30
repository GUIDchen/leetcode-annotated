# 题目：1567. 乘积为正数的最长子数组长度（Maximum Length of Subarray With Positive Product）
# 思路：动态规划，f[i] 记以 i 结尾乘积为正的最长子数组长度，g[i] 记乘积为负的最长长度，按 nums[i] 的正负转移。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(n)，两个长度 n 的 DP 列表。
class Solution:  # LeetCode 约定的题解类
    def getMaxLen(self, nums: List[int]) -> int:  # nums：输入整数数组
        n = len(nums)  # 数组长度
        f = [0] * n  # f[i]：以 i 结尾且乘积为正的最长子数组长度
        g = [0] * n  # g[i]：以 i 结尾且乘积为负的最长子数组长度
        f[0] = int(nums[0] > 0)  # 首元素为正时长度 1，否则为 0
        g[0] = int(nums[0] < 0)  # 首元素为负时长度 1，否则为 0
        ans = f[0]  # 答案至少是第一个元素贡献的正乘积长度
        for i in range(1, n):  # 从第二个元素开始递推
            if nums[i] > 0:  # 当前是正数：不改变乘积符号
                f[i] = f[i - 1] + 1  # 正乘积可以接在原有正乘积后面
                g[i] = 0 if g[i - 1] == 0 else g[i - 1] + 1  # 原负乘积不存在则仍不存在，存在则延长
            elif nums[i] < 0:  # 当前是负数：正负乘积互换
                f[i] = 0 if g[i - 1] == 0 else g[i - 1] + 1  # 负乘积乘上负数变正
                g[i] = f[i - 1] + 1  # 正乘积乘上负数变负
            ans = max(ans, f[i])  # 用当前的正乘积长度更新答案
        return ans  # 返回乘积为正的最长子数组长度
