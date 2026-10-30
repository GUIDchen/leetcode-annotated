# 题目：2952. 需要添加的硬币的最小数量（Minimum Number of Coins to be Added）
# 思路：排序后贪心维护已能连续凑出的区间 [1, s-1]；面值不超过 s 的硬币并入区间，否则补一枚面值 s 的硬币让区间翻倍。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def minimumAddedCoins(self, coins: List[int], target: int) -> int:  # coins 是已有硬币面值，target 是目标值；返回最少需添加的硬币数
        coins.sort()  # 贪心前提：先按面值升序排序，才能从小到大扩展可凑区间
        s = 1  # s 表示当前能连续凑出的区间是 [1, s-1]
        ans = i = 0  # ans 记录添加的硬币数，i 是已排序硬币的下标
        while s <= target:  # 只要还没覆盖到 target 就继续补
            if i < len(coins) and coins[i] <= s:  # 手头硬币面值不超过 s，说明并进来不会留下空隙
                s += coins[i]  # 取用这枚硬币，区间扩展为 [1, s+coins[i]-1]
                i += 1  # 硬币下标前移
            else:  # 否则出现断层：s 这个值凑不出来
                s <<= 1  # 补一枚面值恰为 s 的硬币，区间翻倍为 [1, 2s-1]
                ans += 1  # 添加数量加一
        return ans  # 循环结束，可凑区间已覆盖 target
