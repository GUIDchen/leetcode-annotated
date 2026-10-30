# 题目：2862. 完全子集的最大元素和（Maximum Element-Sum of a Complete Subset of Indices）
# 思路：把下标按「去掉平方因子后的核心」分成 k·1²、k·2²、… 各组，同组任意两数之积是完全平方，枚举核心 k 求最大组和。
# 复杂度：时间 O(n·√n)，每个核心 k 只枚举到 √(n/k)；空间 O(1)，只用了累加变量。
class Solution:  # LeetCode 约定的题解类
    def maximumSum(self, nums: List[int]) -> int:  # nums：数组，元素 nums[i-1] 对应题目里的 1 下标 i
        n = len(nums)  # 数组长度
        ans = 0  # 记录所有分组中的最大元素和
        for k in range(1, n + 1):  # 枚举每个分组的核心 k（下标去掉平方因子后的基底）
            t = 0  # 当前这一组的元素和
            j = 1  # 组内倍率从 1 开始
            while k * j * j <= n:  # 组内下标形如 k·j²，超过 n 就停止
                t += nums[k * j * j - 1]  # 累加下标 k·j² 对应的元素（转成 0 下标要减一）
                j += 1  # 倍率加一，继续累加同组元素
            ans = max(ans, t)  # 更新全局最大组和
        return ans  # 返回最大元素和
