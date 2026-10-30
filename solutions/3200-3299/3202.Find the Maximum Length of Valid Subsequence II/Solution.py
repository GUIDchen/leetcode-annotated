# 题目：3202. 找出有效子序列的最大长度 II（Find the Maximum Length of Valid Subsequence II）
# 思路：有效子序列要求相邻两数之和模 k 恒为定值 v；枚举 v，用 f[x][y] 表示「末尾余数 x、前一位余数 y」的最长长度，转移 f[x][y] = f[y][x] + 1。
# 时间复杂度：O(n·k)，n 为数组长度、k 为模数；空间复杂度：O(k²)，即 DP 表的规模。
class Solution:  # LeetCode 题解类，固定入口名
    def maximumLength(self, nums: List[int], k: int) -> int:  # 返回最长有效子序列长度；nums 为原数组，k 为取模参数
        f = [[0] * k for _ in range(k)]  # k×k 的 DP 表：f[x][y] 表示末尾余数 x、前一位余数 y 的最长长度（每行独立创建，避免共享同一列表）
        ans = 0  # ans 记录全局最长长度
        for x in nums:  # 逐个元素遍历，每个元素都可能成为子序列的新末尾
            x %= k  # 只关心元素对 k 的余数
            for j in range(k):  # 枚举相邻两数之和的余数 v（即 j），它是整段子序列必须固定住的定值
                y = (j - x + k) % k  # 由 (x + y) % k == j 反解出前一位应有的余数 y
                f[x][y] = f[y][x] + 1  # 把 x 接到「以 y 结尾、前一位是 x」的序列后面，长度加一
                ans = max(ans, f[x][y])  # 用当前长度刷新答案
        return ans  # 返回最长有效子序列长度
