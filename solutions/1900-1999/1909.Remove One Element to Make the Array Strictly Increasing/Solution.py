# 题目：1909. 删除一个元素使数组严格递增（Remove One Element to Make the Array Strictly Increasing）
# 思路：先扫描出第一处 nums[i] >= nums[i+1] 的位置 i，被删元素只可能是 i 或 i+1；再用 check 分别验证删掉其中一个后是否严格递增。
# 时间复杂度：O(n)，最多两次线性扫描；空间复杂度：O(1)，只使用常数个辅助变量。
class Solution:  # LeetCode 约定的题解类
    def canBeIncreasing(self, nums: List[int]) -> bool:  # nums：待检查的整数数组，返回能否只删一个元素使其严格递增
        def check(k: int) -> bool:  # 内部函数 check(k)：判断删掉下标 k 的元素后数组是否严格递增
            pre = -inf  # pre：上一个保留元素的值；-inf 保证第一个元素一定能通过比较
            for i, x in enumerate(nums):  # 同时取得下标 i 与元素值 x
                if i == k:  # 遇到需要删除的下标 k
                    continue  # 跳过它，不参与相邻比较
                if pre >= x:  # 前一个保留元素不小于当前元素，已经不严格递增
                    return False  # 直接返回 False
                pre = x  # 更新 pre，作为下一次比较的基准
            return True  # 全部比较通过，说明删掉下标 k 后严格递增

        # 第一段严格递增的末尾就是冲突点附近，下面从它开始尝试两种删法
        i = 0  # i：从头开始、最后一个仍满足严格递增的下标
        while i + 1 < len(nums) and nums[i] < nums[i + 1]:  # 一直后移，直到遇到第一处不满足严格递增的位置（或走到末尾）
            i += 1  # 下标加一，继续检查
        return check(i) or check(i + 1)  # 冲突只可能靠删除 i 或 i+1 修复，任一可行即为 True
