# 题目：3314. 构造最小位运算数组 I（Construct the Minimum Bitwise Array I）
# 核心思路：a | (a+1) 只取决于 a 末尾连续 1 的最高那一位；对每个 x 从低位找第一个为 0 的位 i，清掉第 i-1 位即最小的 a（x = 2 无解返回 -1）。
# 时间复杂度：每个元素最多扫 32 位，O(32n) 即 O(n)；空间复杂度：O(n) 存放答案。
class Solution:  # LeetCode 约定的题解类
    def minBitwiseArray(self, nums: List[int]) -> List[int]:  # nums：若干整数；返回 ans，其中 ans[i] 是满足 ans[i] | (ans[i]+1) == nums[i] 的最小值
        ans = []  # 逐项收集答案
        for x in nums:  # 每个 x 独立求解
            if x == 2:  # 2 是唯一的无解特例：比它小的数都凑不出 2
                ans.append(-1)  # 无解时按题目要求填 -1
            else:  # 其余元素都至少有一个可行解
                for i in range(1, 32):  # 从低位到高位找第一个为 0 的二进制位
                    if x >> i & 1 ^ 1:  # (x>>i)&1 取出第 i 位再 ^1 取反：该位为 0 时条件成立
                        ans.append(x ^ 1 << (i - 1))  # 清掉第 i-1 位（<< 优先级高于 ^），a|(a+1) 恰好还原 x，且 a 最小
                        break  # 找到最小解就停止往高位扫
        return ans  # 返回与 nums 一一对应的答案
