# 题目：1827. 最少操作使数组递增（Minimum Operations to Make the Array Increasing）
# 思路：一次遍历，mx 记录处理后的当前位置值；每个元素补到 mx+1 的差值累加即为答案。
# 时间复杂度：O(n)，只遍历一次；空间复杂度：O(1)，只用两个辅助变量。
class Solution:  # LeetCode 约定的题解类
    def minOperations(self, nums: List[int]) -> int:  # nums：输入数组；返回使数组严格递增的最少操作次数
        ans = mx = 0  # ans 累计操作次数；mx 记录处理完当前位置后应达到的最小值
        for v in nums:  # 按顺序遍历每个元素
            ans += max(0, mx + 1 - v)  # v 至少要补到 mx+1，差值累加进答案
            mx = max(mx + 1, v)  # 更新 mx：取「抬到 mx+1」与原值中较大者
        return ans  # 返回最少操作次数
