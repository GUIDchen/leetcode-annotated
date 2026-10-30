# 题目：1887. 使数组元素相等的减少操作次数（Reduction Operations to Make the Array Elements Equal）
# 思路：升序排序后用 pairwise 相邻比较，cnt 记录当前元素需要跨越的值层数，逐个累加到答案。
# 时间复杂度：O(n log n)，排序占主导；空间复杂度：O(1)，只用了常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def reductionOperations(self, nums: List[int]) -> int:  # nums 是待统一的数组
        nums.sort()  # 原地升序排序，让相等元素相邻
        ans = cnt = 0  # ans 是总操作次数，cnt 是当前元素需要跨越的层数
        for a, b in pairwise(nums):  # 依次取相邻的 (前一个元素, 当前元素)
            if a != b:  # 当前元素比前一个大，说明进入了新的一层
                cnt += 1  # 层数加一，后面的元素要多降一次
            ans += cnt  # 当前元素需要 cnt 次操作才能降到最小值
        return ans  # 返回总操作次数
