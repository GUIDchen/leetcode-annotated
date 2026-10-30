# 3934. 最短唯一子数组 / Smallest Unique Subarray
# 核心思路：二分答案长度 L，用多项式滚动哈希在 O(n) 内判断是否存在恰好出现一次的长度为 L 的子数组。
# 复杂度：时间 O(n log n)，空间 O(n)。
class Solution:  # 题解类定义
    def smallestUniqueSubarray(self, nums: list[int]) -> int:  # 求最短的、只出现一次的子数组长度
        self.nums = nums  # 缓存输入数组，供内部校验方法复用

        self.base = 19  # 哈希基数，取质数 19
        self.modulo = 10**9 + 7  # 哈希取模的模数，避免数值过大
        self.powers = [1] * (len(nums) + 1)  # 预分配 base 的幂数组，长度 n+1

        self.hash_values: dict[int, int] = dict()  # 记录每个窗口哈希值出现的次数

        min_possible_len = len(nums)  # Base case.  # 答案上界先取整个数组长度（基准情况）

        min_len, max_len = 1, len(nums)  # For binary search usage.  # 二分搜索的长度区间

        while min_len <= max_len:  # 二分最短可行长度
            mid_len = (min_len + max_len) // 2  # 取区间中点作为待检验长度

            if self._check_uniqueness(mid_len):  # 判断该长度是否存在唯一子数组
                if mid_len < min_possible_len:  # 只有更短时才更新答案
                    min_possible_len = mid_len  # 记录更优的长度
                max_len = mid_len - 1  # 该长度可行，尝试更短的一侧

            else:  # 该长度不存在唯一子数组
                min_len = mid_len + 1  # 只能向更长的方向收缩

        return min_possible_len  # 返回最短唯一子数组长度

    def _check_uniqueness(self, subarray_len: int) -> bool:  # 判断长度为 subarray_len 的子数组是否有一个只出现一次
        # Only need to reset leftmost power to 1 before usage.  # 只需在使用前把最左侧的幂重置为 1。
        self.powers[0] = 1  # Because powers are calculated by bottom-up.  # 幂表需自底向上重算，先把首项归位。

        for idx in range(1, len(self.nums) + 1):  # 自底向上预计算 base 的各次幂
            self.powers[idx] = (self.powers[idx - 1] * self.base) % self.modulo  # 递推得到 base^idx mod modulo

        current_hash = 0  # 初始化首个窗口的哈希值
        for idx in range(subarray_len):  # 累加得到第一个窗口的哈希
            current_hash *= self.base  # 整体左移一位（乘以基数）
            current_hash += self.nums[idx]  # 把新进入窗口的元素并入哈希
            current_hash %= self.modulo  # 取模控制数值范围

        self.hash_values.clear()  # Clear before usage.  # 每次检查前清空哈希计数表。
        self.hash_values[current_hash] = 1  # 首个窗口的哈希出现次数记为 1

        for idx in range(1, len(self.nums) - subarray_len + 1):  # 枚举窗口左端点，滑动更新哈希
            # Window shifts: deduct leftmost num's share from hash value.  # 窗口右移：先扣掉最左侧元素的贡献。
            current_hash -= self.powers[subarray_len - 1] * self.nums[idx - 1]  # 减去左端元素乘以 base^(L-1) 的贡献

            # Integrate newly added num's share into hash value.  # 再把新加入元素的贡献并回哈希值。
            current_hash *= self.base  # 整体左移一位
            current_hash += self.nums[idx + subarray_len - 1]  # 加上窗口右端的新元素
            current_hash %= self.modulo  # 取模规范化

            if current_hash not in self.hash_values.keys():  # 该哈希值首次出现时先建条目
                self.hash_values.update({current_hash: 0})  # 计数初始化为 0，随后统一加 1
            self.hash_values[current_hash] += 1  # 该窗口对应的哈希出现次数加 1

        return 1 in self.hash_values.values()  # 存在出现次数为 1 的哈希即说明有唯一子数组
