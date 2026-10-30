# 题目：1438. 绝对差不超过限制的最长连续子数组（Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit）
# 思路：右指针扩张窗口并用有序表维护窗口元素，最大值减最小值超限时不断右移左指针。
# 时间复杂度：O(n log n)；空间复杂度：O(n)。
class Solution:  # LeetCode 约定的题解类
    def longestSubarray(self, nums: List[int], limit: int) -> int:  # nums 是输入数组，limit 是窗口内允许的最大绝对差
        sl = SortedList()  # 有序可重列表（LeetCode 环境内置的 sortedcontainers），维护窗口内全部元素
        ans = j = 0  # ans 记录最长长度，j 是窗口左端点
        for i, x in enumerate(nums):  # 右端点 i 逐个右移，同时取得元素值 x
            sl.add(x)  # 新元素加入窗口
            while sl[-1] - sl[0] > limit:  # 索引 -1 是最大值、0 是最小值，差值超限就收缩
                sl.remove(nums[j])  # 从有序表中删掉一个左端点元素
                j += 1  # 左端点右移一位
            ans = max(ans, i - j + 1)  # 用当前窗口长度更新答案
        return ans  # 返回最长合法子数组的长度
