# 题目：3719. 最长平衡子数组 I（Longest Balanced Subarray I）
# 思路：枚举左端点并向右扩展，用集合记录出现过的值，分别累计不同偶数与不同奇数的个数；两者相等时子数组平衡，更新最长长度。
# 时间复杂度：O(n²)，空间复杂度：O(n)，每个左端点需要一个去重集合。
class Solution:  # LeetCode 约定的题解类
    def longestBalanced(self, nums: List[int]) -> int:  # nums：整数数组；返回最长平衡子数组的长度
        n = len(nums)  # 数组长度
        ans = 0  # 记录最长平衡子数组长度
        for i in range(n):  # 枚举子数组左端点
            cnt = [0, 0]  # cnt[0]：不同偶数的个数；cnt[1]：不同奇数的个数
            vis = set()  # 当前子数组中已经出现过的值
            for j in range(i, n):  # 枚举子数组右端点
                if nums[j] not in vis:  # 该值在当前子数组中首次出现
                    cnt[nums[j] & 1] += 1  # 按奇偶性给对应种类的不同值个数加一
                    vis.add(nums[j])  # 标记为已出现
                if cnt[0] == cnt[1]:  # 不同偶数与不同奇数个数相等即为平衡
                    ans = max(ans, j - i + 1)  # 更新最长长度
        return ans  # 返回最长平衡子数组长度
