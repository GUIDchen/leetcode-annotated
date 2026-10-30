# 题目：2902. 和带限制的子多重集合的数目（Count of Sub-Multisets With Bounded Sum）
# 思路：按数值做有界背包，用滑动窗口前缀和（stride）把每种数值的转移压到 O(r)；数值 0 不改变和，最后单独乘以取法数。
# 时间复杂度：O(V * r)，V 为不同数值的个数；空间复杂度：O(r)，dp 与 stride 各一个长度 r+1 的数组。
class Solution:  # LeetCode 约定的题解类
    def countSubMultisets(self, nums: List[int], l: int, r: int) -> int:  # nums：输入多重集合；l、r：子多重集和的下界与上界
        kMod = 1_000_000_007  # 取模常数
        # dp[i] := # of submultisets of nums with sum i
        dp = [1] + [0] * r  # dp[0]=1 表示空集，其余先置 0；下标 i 表示和为 i 的方案数
        count = collections.Counter(nums)  # 统计每个数值的出现次数
        zeros = count.pop(0, 0)  # 数值 0 不影响和，先取出，最后乘上「取 0..zeros 个 0」的 zeros+1 种

        for num, freq in count.items():  # 逐个数值做有界背包（freq 为该数值的可用个数）
            # stride[i] := dp[i] + dp[i - num] + dp[i - 2 * num] + ...
            stride = dp.copy()  # 复制当前 dp，作为同余类前缀和的起点
            for i in range(num, r + 1):  # 按同余类做一次前缀和，相当于允许取任意多个 num
                stride[i] += stride[i - num]  # 累加「再多取一个 num」的方案数
            for i in range(r, 0, -1):  # 倒序更新，避免本轮读到已被覆盖的 dp 值
                if i >= num * (freq + 1):  # 取值个数超过 freq 的部分是非法的，需要扣除
                    # dp[i] + dp[i - num] + dp[i - freq * num]
                    dp[i] = stride[i] - stride[i - num * (freq + 1)]  # 滑动窗口差分：只保留取 0..freq 个 num 的方案
                else:  # 取不到 freq+1 个 num，不会出现超量
                    dp[i] = stride[i]  # 直接用前缀和结果作为 dp[i]

        return (zeros + 1) * sum(dp[l : r + 1]) % kMod  # 对 [l, r] 求和并乘上 0 的取法数，最后统一取模
