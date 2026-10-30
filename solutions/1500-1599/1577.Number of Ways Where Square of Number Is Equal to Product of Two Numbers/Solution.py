# 题目：1577. 数的平方等于两数乘积的方法数（Number of Ways Where Square of Number Is Equal to Product of Two Numbers）
# 思路：先用 Counter 分别统计两个数组里所有数对的乘积频次，再对另一数组的每个元素 x 累加 x*x 的命中次数，两种情况相加。
# 时间复杂度：O(m^2 + n^2)，两数组各枚举一次数对；空间复杂度：O(m^2)，乘积频次表最多存 m 个元素的两两乘积。
class Solution:  # LeetCode 约定的题解类
    def numTriplets(self, nums1: List[int], nums2: List[int]) -> int:  # nums1/nums2 为两个输入数组，返回满足条件的三元组个数
        def count(nums: List[int]) -> Counter:  # 内层函数 count：统计 nums 中所有数对乘积的频次表
            cnt = Counter()  # Counter 充当「乘积 → 出现次数」的哈希表
            for j in range(len(nums)):  # 枚举数对的第一个下标 j
                for k in range(j + 1, len(nums)):  # 枚举第二个下标 k，只取 k>j 避免同一个数对重复计数
                    cnt[nums[j] * nums[k]] += 1  # 该乘积出现一次，频次加一
            return cnt  # 返回频次表

        def cal(nums: List[int], cnt: Counter) -> int:  # cal：对 nums 的每个元素累加其平方在频次表中的命中次数
            return sum(cnt[x * x] for x in nums)  # 生成器求和：x*x 命中几次就贡献几个三元组

        cnt1 = count(nums1)  # nums1 的数对乘积频次
        cnt2 = count(nums2)  # nums2 的数对乘积频次
        return cal(nums1, cnt2) + cal(nums2, cnt1)  # 两种情况相加：nums1 做平方配 nums2 的乘积，反之亦然
