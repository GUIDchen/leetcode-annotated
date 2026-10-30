# 题目：53. 最大子数组和（Maximum Subarray）
# 思路：动态规划 / 贪心。用 f 表示以当前元素结尾的最大子数组和，若 f 为负就丢弃前面、只留当前元素，边递推边更新全局最大值。
# 时间复杂度：O(n)，只扫一遍数组；空间复杂度：O(1)，只用两个变量滚动更新。
class Solution:  # LeetCode 约定的题解类
    def maxSubArray(self, nums: List[int]) -> int:  # nums 为输入数组，返回其连续子数组的最大和
        ans = f = nums[0]  # ans 记录全局最大值；f 记录以当前元素结尾的最大和，都用首元素初始化
        for x in nums[1:]:  # 从第二个元素开始遍历（首元素已在初值中考虑）
            f = max(f, 0) + x  # f 为负时前面部分只会拖累结果，于是从当前元素重新累加
            ans = max(ans, f)  # 用当前结尾的最优值更新全局最优解
        return ans  # 返回最大子数组和
