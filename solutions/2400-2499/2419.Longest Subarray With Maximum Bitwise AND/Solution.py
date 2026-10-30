# 题目：2419. 按位与最大的最长子数组（Longest Subarray With Maximum Bitwise AND）
# 核心思路：子数组的按位与不会超过其中任一元素，故最大按位与就是数组最大值 mx；只需统计 mx 连续出现的最长长度。
# 时间复杂度：O(n)，一趟线性扫描；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def longestSubarray(self, nums: List[int]) -> int:  # nums：输入数组
        mx = max(nums)  # 按位与只会让数值变小或不变，最大值就是能达到的最大按位与
        ans = cnt = 0  # ans 记录最长长度，cnt 记录当前连续等于 mx 的个数
        for x in nums:  # 顺序扫描每个元素
            if x == mx:  # 命中最大值，这一段可以继续延伸
                cnt += 1  # 当前连续段长度加一
                ans = max(ans, cnt)  # 用当前段长度更新答案
            else:  # 遇到比 mx 小的元素
                cnt = 0  # 与运算会变小，连续段被打断，计数清零
        return ans  # 返回最长子数组长度
