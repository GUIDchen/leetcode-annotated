# 题目：674. 最长连续递增序列（Longest Continuous Increasing Subsequence）
# 思路：一次遍历，维护以当前位置结尾的连续递增段长度 cnt，遇到断点重置为 1，全程用 ans 记录最大值。
# 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用两个计数器变量。
class Solution:  # LeetCode 约定的题解类
    def findLengthOfLCIS(self, nums: List[int]) -> int:  # nums：输入数组
        ans = cnt = 1  # ans 记录最大长度，cnt 记录当前连续递增段长度，均从 1 开始
        for i, x in enumerate(nums[1:]):  # 切片后下标从 0 开始，故 x 对应原数组的 nums[i+1]
            if nums[i] < x:  # 相邻元素严格递增，连续段可以延长
                cnt += 1  # 当前连续段长度加一
                ans = max(ans, cnt)  # 用当前长度更新答案
            else:  # 递增中断
                cnt = 1  # 从当前元素重新开始计一段
        return ans  # 返回最长连续递增序列的长度
