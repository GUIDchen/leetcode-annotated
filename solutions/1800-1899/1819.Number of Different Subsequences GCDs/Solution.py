# 题目：1819. 序列中不同最大公约数的数目（Number of Different Subsequences GCDs）
# 思路：枚举可能的 GCD 值 x，把 nums 中所有 x 的倍数依次求 gcd；一旦累积 gcd 等于 x，说明 x 是某个子序列的 GCD。
# 时间复杂度：O(M log M)，M = max(nums)，调和级数级别的枚举量；空间复杂度：O(M)，集合保存出现过的数值。
class Solution:  # LeetCode 约定的题解类
    def countDifferentSubsequenceGCDs(self, nums: List[int]) -> int:  # nums：输入数组
        mx = max(nums)  # 数组最大值，作为枚举上界
        vis = set(nums)  # 用集合记录出现过的数值，实现 O(1) 的存在性查询
        ans = 0  # 不同子序列 GCD 的个数
        for x in range(1, mx + 1):  # 枚举候选 GCD 值 x
            g = 0  # 累积当前 x 的所有倍数中出现过的数的 gcd，0 与任何数 gcd 仍是该数
            for y in range(x, mx + 1, x):  # 按倍数步长枚举所有 x 的倍数
                if y in vis:  # 只有出现过的数才能参与子序列
                    g = gcd(g, y)  # 把 y 并入累积 gcd
                    if g == x:  # gcd 恰好等于 x，说明 x 可被某个子序列取到
                        ans += 1  # 计数加一
                        break  # 已经确认 x 可达，无需继续枚举倍数
        return ans  # 返回不同 GCD 的总数
