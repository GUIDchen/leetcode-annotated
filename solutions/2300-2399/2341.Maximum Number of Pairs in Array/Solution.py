# 题目：2341. 数组能形成多少数对（Maximum Number of Pairs in Array）
# 思路：直接用 Counter 统计每个值的出现次数；每个值出现 c 次可配出 c//2 对，落单个数 = 总元素数 - 对数 * 2。
# 时间复杂度：O(n)，建表与求和都是线性；空间复杂度：O(k)，k 为不同取值的个数（本题值域 0..100，可视为 O(1)）。
class Solution:  # LeetCode 约定的题解类
    def numberOfPairs(self, nums: List[int]) -> List[int]:  # nums：输入数组；返回 [数对数目, 落单数目]
        cnt = Counter(nums)  # Counter 统计每个值的出现次数（由判题环境提供，无需 import）
        s = sum(v // 2 for v in cnt.values())  # v // 2 是一个值能配出的对数，对全部取值求和得到总对数 s
        return [s, len(nums) - s * 2]  # 总数减去已成对的 2s 个元素，剩下的都是落单的
