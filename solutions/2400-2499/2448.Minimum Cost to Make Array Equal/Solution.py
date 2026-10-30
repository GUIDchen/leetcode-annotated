# 题目：2448. 使数组相等的最小开销（Minimum Cost to Make Array Equal）
# 思路：把 (nums[i], cost[i]) 按数值升序配对，做前缀和 f 记 Σ值×单价、g 记 Σ单价；目标值取某个 arr[i-1] 时，左侧全抬高、右侧全压低，代价用前缀和 O(1) 得到，枚举所有候选取最小。
# 时间复杂度：O(n log n)，排序主导（枚举 O(n)）；空间复杂度：O(n)，排序结果与两条前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def minCost(self, nums: List[int], cost: List[int]) -> int:  # nums 是原数组，cost 是每个位置改 1 的单价
        arr = sorted(zip(nums, cost))  # 把数值与单价配对后按数值升序排序，使左侧恰好是更小的数
        n = len(arr)  # 元素个数
        f = [0] * (n + 1)  # f[i]：前 i 个元素的 Σ值×单价（前缀和）
        g = [0] * (n + 1)  # g[i]：前 i 个元素的 Σ单价（前缀和）
        for i in range(1, n + 1):  # 从 1 开始递推，下标 0 留作空前缀
            a, b = arr[i - 1]  # 取出第 i 个元素的数值 a 与单价 b
            f[i] = f[i - 1] + a * b  # 累加 数值×单价（Python 整数无溢出顾虑）
            g[i] = g[i - 1] + b  # 累加单价，得到左侧每改动 1 的总开销系数
        ans = inf  # 用正无穷初始化答案，保证第一次比较一定被更新
        for i in range(1, n + 1):  # 枚举目标值：把所有数都变成 arr[i-1] 的数值
            a = arr[i - 1][0]  # 取出候选目标数值 a
            l = a * g[i - 1] - f[i - 1]  # 左侧元素全抬到 a：a*Σ单价 - Σ值×单价
            r = f[n] - f[i] - a * (g[n] - g[i])  # 右侧元素全压到 a：Σ值×单价 - a*Σ单价
            ans = min(ans, l + r)  # 两侧代价相加，更新最小值
        return ans  # 返回最优目标下的最小总开销
