# 题目：2275. 按位与结果大于零的最长组合（Largest Combination With Bitwise AND Greater Than Zero）
# 思路：只要存在一位在组合中所有数字里都为 1，按位与就大于 0；于是逐位统计 1 的个数并取最大值。
# 时间复杂度：O(n × log M)，M 为最大元素；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def largestCombination(self, candidates: List[int]) -> int:  # candidates：候选数字；返回按位与大于 0 的最长子集长度
        ans = 0  # 记录所有比特位中「1 的个数」的最大值
        for i in range(max(candidates).bit_length()):  # 最大值决定枚举位数：bit_length 返回最高有效位的位数
            ans = max(ans, sum(x >> i & 1 for x in candidates))  # 统计第 i 位上 1 的个数，与当前答案取较大值（>> 优先于 &）
        return ans  # 返回按位与结果大于零的最长组合长度
