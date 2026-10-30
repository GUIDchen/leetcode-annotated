# 题目：2505. 所有子序列和的按位或（Bitwise OR of All Subsequence Sums）🔒
# 思路：先统计每个二进制位上 1 的总数；某位出现过就能出现在某个子序列和中，再按“每两个低位进位到高一位”向上累加。
# 时间复杂度：O(31n)，n 为元素个数；空间复杂度：O(1)，只需 64 个计数器。
class Solution:  # LeetCode 约定的题解类
    def subsequenceSumOr(self, nums: List[int]) -> int:  # nums：输入数组；返回所有子序列和按位或的结果
        cnt = [0] * 64  # cnt[i]：第 i 个二进制位上 1 的个数，64 位足够容纳所有进位
        ans = 0  # ans：所有子序列和按位或的结果
        for v in nums:  # 遍历每个数
            for i in range(31):  # 题目数值在 int 范围内，只有低 31 位可能为 1
                if (v >> i) & 1:  # 取出第 i 位，判断是否为 1
                    cnt[i] += 1  # 统计这一位上 1 的个数
        for i in range(63):  # 从低位到高位处理进位，最后一位留给最高位的进位
            if cnt[i]:  # 该位至少出现过一次，就能出现在某个子序列和中
                ans |= 1 << i  # 把第 i 位置入答案
            cnt[i + 1] += cnt[i] // 2  # 每 2 个第 i 位的 1 相加会向第 i+1 位进位
        return ans  # 返回所有子序列和按位或的结果
