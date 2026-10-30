# 题目：2574. 左右元素和的差值（Left and Right Sum Differences）
# 思路：先把整个数组求和作为右侧和，再从左往右移动分界线，同时维护左侧和与右侧和。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，用于存放结果列表。
class Solution:  # LeetCode 约定的题解类
    def leftRightDifference(self, nums: List[int]) -> List[int]:  # nums 是输入数组，返回每个位置左右元素和的差值
        l, r = 0, sum(nums)  # l 是左侧元素和，r 初始化为整个数组的总和
        ans = []  # 用来收集每个位置的结果
        for x in nums:  # 从左到右依次处理每个元素
            r -= x  # 当前元素不再属于右侧，先从右侧和中减去
            ans.append(abs(l - r))  # 记录左右和之差的绝对值
            l += x  # 当前元素加入左侧和，供下一个位置使用
        return ans  # 返回结果列表
