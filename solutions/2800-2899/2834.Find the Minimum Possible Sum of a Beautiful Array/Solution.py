# 题目：2834. 找出美丽数组的最小和（Find the Minimum Possible Sum of a Beautiful Array）
# 思路：贪心选最小的数。令 m = target // 2，1..m 内任意两个不同数之和都不超过 target，全部可选；而 m+1..target-1 中的每个数都会和前面的某个数凑成 target，必须整段跳过，所以剩下的数从 target 开始连续取。
# 时间复杂度：O(1)，只有常数次算术运算；空间复杂度：O(1)，只用了几个临时变量。
class Solution:  # LeetCode 约定的题解类
    def minimumPossibleSum(self, n: int, target: int) -> int:  # n：数组长度；target：任意两数之和都不能等于它
        mod = 10**9 + 7  # 结果需要对 1e9+7 取模
        m = target // 2  # 安全前缀上界：取 1..m 时任意两数之和都 <= target
        if n <= m:  # 需要的个数不超过安全前缀长度
            return ((1 + n) * n // 2) % mod  # 直接取 1..n，等差数列求和后取模
        return ((1 + m) * m // 2 + (target + target + n - m - 1) * (n - m) // 2) % mod  # 前半段 1..m 的和，加上后半段从 target 起连续 (n-m) 个数的和
