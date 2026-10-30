# 题目：1800. 最大升序子数组和（Maximum Ascending Subarray Sum）
# 思路：遍历数组，t 记录当前严格递增段的元素和，一旦不再递增就用当前元素重新起段，ans 全程记录最大值。
# 时间复杂度：O(n)，只需一次遍历；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxAscendingSum(self, nums: List[int]) -> int:  # nums 是输入数组，返回最大升序子数组的和
        ans = t = 0  # ans 存答案；t 存当前升序段的累加和，都从 0 开始
        for i, v in enumerate(nums):  # 同时取得下标 i 与元素值 v
            if i == 0 or v > nums[i - 1]:  # 首个元素，或当前值比前一个值大：升序段继续延伸
                t += v  # 把当前值累加进这一段
                ans = max(ans, t)  # 刷新历史最大和
            else:  # 否则升序被打断
                t = v  # 以当前值作为新一段的起点
        return ans  # 返回最大升序子数组和
