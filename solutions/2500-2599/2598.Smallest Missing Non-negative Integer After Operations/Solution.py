# 题目：2598. 执行操作后的最大 MEX（Smallest Missing Non-negative Integer After Operations）
# 思路：每个元素只能按 value 的整数倍增减，所以能否凑出某数只取决于它对 value 的余数；统计余数后从 0 起逐个消耗。
# 时间复杂度：O(n + m)，m 为答案大小且不超过 n；空间复杂度：O(min(n, value))，计数器按余数聚合。
class Solution:  # LeetCode 约定的题解类
    def findSmallestInteger(self, nums: List[int], value: int) -> int:  # nums：可反复加减 value 的数组；value：每次操作的步长；返回能得到的最大 MEX
        cnt = Counter(x % value for x in nums)  # 按 value 取模统计每个余数出现了多少次（Python 的 % 对负数返回非负，无需修正）
        for i in range(len(nums) + 1):  # 答案最多是 n（0..n-1 都凑出时缺失 n），所以循环到 len(nums) 即可
            if cnt[i % value] == 0:  # 该余数桶已空，说明凑不出 i
                return i  # 第一个凑不出的非负整数就是答案
            cnt[i % value] -= 1  # 能凑出 i，消耗掉该余数的一个配额后继续试下一个
