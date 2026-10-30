# 题目：1764. 通过连接另一个数组的子数组得到一个数组（Form Array by Concatenating Subarrays of Another Array）
# 思路：双指针贪心匹配。在 nums 当前位置 j 用切片尝试匹配 groups[i]；相同则跳过该组长度并前进一组，否则 j 右移一位。
# 时间复杂度：O(n*m)，最坏情况每个位置都比较一次且切片比较 O(m)；空间复杂度：O(m)，切片会临时复制一段。
class Solution:  # LeetCode 约定的题解类
    def canChoose(self, groups: List[List[int]], nums: List[int]) -> bool:  # groups：需按顺序拼接的组；nums：源数组
        n, m = len(groups), len(nums)  # n 是分组个数，m 是源数组长度
        i = j = 0  # i 是当前分组的行标，j 是源数组中尝试匹配的位置
        while i < n and j < m:  # 分组没匹配完且源数组还有剩余就继续
            g = groups[i]  # 取出当前要匹配的分组
            if g == nums[j : j + len(g)]:  # 用切片取出等长的一段比较，相等即匹配成功
                j += len(g)  # 跳过整段，子数组之间不允许重叠
                i += 1  # 继续匹配下一个分组
            else:  # 当前位置匹配失败
                j += 1  # 源数组位置右移一位再试
        return i == n  # 所有分组都匹配成功才返回 True
