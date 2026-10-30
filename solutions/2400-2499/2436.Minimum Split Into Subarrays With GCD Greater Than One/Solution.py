# 题目：2436. 使子数组最大公约数大于一的最小分割数（Minimum Split Into Subarrays With GCD Greater Than One）
# 思路：贪心。从左到右把能并入同一段的元素合并求 gcd，一旦 gcd 变成 1 就必须在这里切一刀，并把新段的 gcd 重置为当前元素。
# 时间复杂度：O(n*log V)，每个元素做一次 gcd，V 是数值大小；空间复杂度：O(1)，只用了几个计数变量。
class Solution:  # LeetCode 约定的题解类
    def minimumSplits(self, nums: List[int]) -> int:  # nums：输入数组，返回满足「每段 gcd > 1」的最少段数
        ans, g = 1, 0  # ans：当前已开的段数（至少一段）；g：当前段的 gcd，用 0 作单位元让首个数直接成为 gcd
        for x in nums:  # 从左到右依次尝试把每个元素并入当前段
            g = gcd(g, x)  # 合并后当前段的 gcd 更新为 gcd(旧 gcd, x)（判题器已提供 gcd）
            if g == 1:  # 当前段 gcd 变成 1，这一段已经非法，必须在此切开
                ans += 1  # 新开一段，段数加一
                g = x  # 新段的 gcd 从当前元素 x 重新开始
        return ans  # 返回累计得到的最少段数
