# 题目：3251. 单调数组对的数目 II（Find the Count of Monotonic Pairs II）
# 思路：与 I 同样用动态规划 + accumulate 前缀和，f[i][j] 表示 arr1[i]=j 的方案数，上一位取值上界由 arr1 不降、arr2 不升共同决定。
# 时间复杂度：O(n·m)，可承受本题更大的数据范围；空间复杂度：O(n·m)，用于存放 DP 表。
class Solution:  # LeetCode 约定的题解类
    def countOfPairs(self, nums: List[int]) -> int:  # nums：输入数组；返回满足条件的单调数组对数目
        mod = 10**9 + 7  # 取模常量，防止答案溢出
        n, m = len(nums), max(nums)  # n：数组长度；m：数组最大值，作为 arr1 各元素取值的上界
        f = [[0] * (m + 1) for _ in range(n)]  # f[i][j]：arr1[i]=j 时的方案数，初值全为 0
        for j in range(nums[0] + 1):  # 第 0 位：arr1[0] 可以是 0..nums[0] 中任意一个值
            f[0][j] = 1  # 每种取值只对应一种分法，方案数为 1
        for i in range(1, n):  # 从左到右逐位确定 arr1 的取值
            s = list(accumulate(f[i - 1]))  # accumulate 得到 f[i-1] 的前缀和，用于 O(1) 求区间方案和
            for j in range(nums[i] + 1):  # 枚举 arr1[i] 的取值 j，需满足 arr1[i]+arr2[i]=nums[i]
                k = min(j, j + nums[i - 1] - nums[i])  # 上一位取值的上界：既要 arr1 不降(k<=j)，又要 arr2 不升(k<=j+nums[i-1]-nums[i])
                if k >= 0:  # k<0 表示不存在合法的上一位取值
                    f[i][j] = s[k] % mod  # 前缀和 s[k] 即所有合法的 f[i-1][0..k] 之和
        return sum(f[-1][: nums[-1] + 1]) % mod  # 最后一位 arr1[n-1] 取 0..nums[n-1] 的方案全部累加后取模
