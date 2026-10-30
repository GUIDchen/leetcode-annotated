# 题目：1726. 同积元组（Tuple with Same Product）
# 思路：用哈希表统计每个两数乘积出现的下标对数；乘积相同的任意两对可组成 8 个合法元组。
# 时间复杂度：O(n^2)，枚举所有下标对；空间复杂度：O(n^2)，哈希表最多存 O(n^2) 个乘积。
class Solution:  # LeetCode 约定的题解类
    def tupleSameProduct(self, nums: List[int]) -> int:  # nums：元素互不相同的输入数组
        cnt = defaultdict(int)  # 哈希表：键是两数乘积，值是该乘积出现的下标对数
        for i in range(1, len(nums)):  # 枚举下标对中较大的那个下标 i
            for j in range(i):  # 只枚举 j < i，保证每对下标只统计一次
                x = nums[i] * nums[j]  # 计算这两个数的乘积
                cnt[x] += 1  # 该乘积的出现次数加一
        return sum(v * (v - 1) // 2 for v in cnt.values()) << 3  # C(v, 2) 选出两对下标，再乘 8 得到元组数
