# 题目：2025. 分割数组的最多方案数（Maximum Number of Ways to Partition an Array）
# 思路：先求前缀和并建成「右侧」频次表；枚举把每个元素换成 k，用新总和的一半去左右两张表查划分点个数，遍历中把当前前缀和从右表挪到左表。
# 时间复杂度：O(n)，一次求前缀和加一次遍历，哈希查询 O(1)；空间复杂度：O(n)，前缀和数组与两张频次表。
class Solution:  # LeetCode 约定的题解类
    def waysToPartition(self, nums: List[int], k: int) -> int:  # nums 是原数组，k 是唯一允许替换成的值，返回最大划分方案数
        n = len(nums)  # 数组长度，供初始化与循环使用
        s = [nums[0]] * n  # 先开出长度为 n 的前缀和数组，首项已知，其余稍后填充
        right = defaultdict(int)  # right：前缀和频次表，默认值为 0，先当作「划分点在右侧」的候选集合
        for i in range(1, n):  # 从下标 1 开始顺推前缀和
            s[i] = s[i - 1] + nums[i]  # 前缀和递推：前一项加上当前元素
            right[s[i - 1]] += 1  # 把 s[i-1] 计入右侧频次表

        ans = 0  # 答案初值：不替换任何元素时的最大划分方案数
        if s[-1] % 2 == 0:  # 总和为偶数才可能被平分成两半
            ans = right[s[-1] // 2]  # 不替换时，划分点左侧和恰为总和一半的方案数

        left = defaultdict(int)  # left：左侧前缀和频次表，随遍历逐步扩大
        for v, x in zip(s, nums):  # 同时取出前缀和 v 与对应元素 x，枚举把 x 替换成 k
            d = k - x  # d：替换后数组总和的增量
            if (s[-1] + d) % 2 == 0:  # 新总和为偶数才存在「左右和相等」的划分
                t = left[(s[-1] + d) // 2] + right[(s[-1] - d) // 2]  # 划分点在当前位置左侧、右侧两种情形分别查表求和
                if ans < t:  # 只有更优才更新
                    ans = t  # 记录本轮得到的方案数
            left[v] += 1  # v 从此归入左侧频次表
            right[v] -= 1  # 同时从右侧频次表扣除，避免同一划分点被重复统计
        return ans  # 返回最大划分方案数
