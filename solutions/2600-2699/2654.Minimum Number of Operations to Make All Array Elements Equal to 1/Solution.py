# 题目：2654. 使数组所有元素变成 1 的最少操作次数（Minimum Number of Operations to Make All Array Elements Equal to 1）
# 核心思路：先数已有的 1；若没有，就找 gcd 为 1 的最短子数组，用 mi-1 次操作把它变成一个 1，再用 n-1 次把 1 传染给其余元素。
# 时间复杂度：O(n^2 log V)，枚举所有子数组并求 gcd；空间复杂度：O(1)，只用了常数个辅助变量。
class Solution:  # 题解类
    def minOperations(self, nums: List[int]) -> int:  # nums：输入数组；返回使全部元素变成 1 的最少操作次数
        n = len(nums)  # 记录数组长度
        cnt = nums.count(1)  # 统计数组中 1 的个数
        if cnt:  # 已经存在 1，可以直接用 1 去「传染」其他元素
            return n - cnt  # 每个非 1 元素一次操作，答案为 n - cnt
        mi = n + 1  # mi 保存能凑出 1 的最短子数组长度，n+1 表示尚未找到
        for i in range(n):  # 枚举子数组的左端点 i
            g = 0  # 区间 gcd 累加器，gcd(0, x) = x，便于从零开始累
            for j in range(i, n):  # 右端点 j 从 i 开始向右扩展
                g = gcd(g, nums[j])  # 把 nums[j] 并入当前区间的 gcd
                if g == 1:  # 区间 gcd 变成 1，可以通过操作造出一个 1
                    mi = min(mi, j - i + 1)  # 用更短的区间长度更新 mi
        return -1 if mi > n else n - 1 + mi - 1  # 无解返回 -1；否则先花 mi-1 次造 1，再花 n-1 次传染
