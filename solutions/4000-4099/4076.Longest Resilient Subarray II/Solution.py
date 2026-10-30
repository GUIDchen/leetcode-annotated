# 4076. 最长有韧性的子数组 II（Longest Resilient Subarray II）
# 核心思路：与 I 相同：只有模 k 同余的连续元素才可能同属一段，段长 cnt 满足 x * (cnt - 1) 能被 k 整除时整段即有韧性；数据范围更大，乘积需用 1LL / Python 大整数防止溢出。
# 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution:  # 题解类
    def resilientSubarray(self, nums: list[int], k: int) -> int:  # 返回最长的“有韧性”子数组长度：删掉其中任意一个元素后，剩余元素之和仍能被 k 整除
        ans = cnt = 0  # ans 记录最长长度，cnt 记录当前同余连续段的长度
        for i, x in enumerate(nums):  # 从左到右扫描数组
            x %= k  # 当前元素模 k 的余数
            if i and nums[i - 1] % k == x:  # 前一个元素与当前元素同余，可以并入同一段
                cnt += 1  # 段长加一
            else:  # 否则同余段在此断开
                cnt = 1  # 以当前元素为新的起点
            if x * (cnt - 1) % k == 0:  # 删掉该段任一元素后剩余和模 k 为 x * (cnt - 1)（Python 大整数不会溢出），为 0 即满足韧性条件
                ans = max(ans, cnt)  # 更新最长长度
        return ans  # 返回最长有韧性子数组的长度
