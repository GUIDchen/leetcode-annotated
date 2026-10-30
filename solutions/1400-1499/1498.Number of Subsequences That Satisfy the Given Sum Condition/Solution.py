# 题目：1498. 满足条件的子序列数目（Number of Subsequences That Satisfy the Given Sum Condition）
# 思路：排序后固定最小值 x，用二分找出最后一个满足 x + y <= target 的位置 j，中间元素任选，贡献 2^(j-i)。
# 时间复杂度：O(n log n)，排序加 n 次二分；空间复杂度：O(n)，2 的幂表。
class Solution:  # LeetCode 约定的题解类
    def numSubseq(self, nums: List[int], target: int) -> int:  # 统计满足最小+最大 <= target 的非空子序列数目
        mod = 10**9 + 7  # 取模常数
        nums.sort()  # 排序后最小值和最大值分别落在区间两端
        n = len(nums)  # 数组长度
        f = [1] + [0] * n  # f[i] 保存 2^i % mod，先准备长度为 n+1 的表
        for i in range(1, n + 1):  # 递推计算每个 2 的幂
            f[i] = f[i - 1] * 2 % mod  # 乘 2 后取模，避免数值过大
        ans = 0  # 累加答案
        for i, x in enumerate(nums):  # 枚举最小值的位置 i
            if x * 2 > target:  # 最小值都超过一半，后面更大的值更不可能满足
                break  # 直接结束循环
            j = bisect_right(nums, target - x, i + 1) - 1  # 在 i+1 之后二分，找到最后一个 <= target-x 的下标 j
            ans = (ans + f[j - i]) % mod  # 中间 j-i 个元素任选，贡献 2^(j-i) 个子序列
        return ans  # 返回答案
