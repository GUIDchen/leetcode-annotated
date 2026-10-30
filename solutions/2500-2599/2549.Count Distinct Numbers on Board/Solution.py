# 题目：2549. 统计桌面上的不同数字（Count Distinct Numbers on Board）
# 思路：规律题。x % (x - 1) == 1 使得 n 能一路推出 n-1、n-2 … 直到 2，而 1 永远推不出来；因此 n > 1 时答案为 n-1，n == 1 时答案为 1。
# 时间复杂度：O(1)，只做一次减法与 max；空间复杂度：O(1)，没有额外存储。
class Solution:  # LeetCode 约定的题解类
    def distinctIntegers(self, n: int) -> int:  # n 是初始放在桌面上的数字
        # n 能一路推出 n-1 … 直到 2，而 1 永远推不出来，故答案恰为 n-1（n == 1 时单独处理）
        return max(1, n - 1)  # n > 1 时最终桌面上是 2..n 共 n-1 个数；n == 1 时只有 1 本身
