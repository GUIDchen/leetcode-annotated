# 题目：1524. 和为奇数的子数组数目（Number of Sub-arrays With Odd Sum）
# 核心思路：子数组和等于两个前缀和之差；前缀和奇偶性不同时差为奇数，所以只需统计已出现的前缀和奇偶个数。
# 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def numOfSubarrays(self, arr: List[int]) -> int:  # arr：输入数组
        mod = 10**9 + 7  # 取模常数
        cnt = [1, 0]  # cnt[0]/cnt[1]：前缀和为偶数/奇数的个数，空前缀和 0 算偶数
        ans = s = 0  # ans 为答案，s 为当前前缀和
        for x in arr:  # 遍历每个元素
            s += x  # 更新前缀和
            ans = (ans + cnt[s & 1 ^ 1]) % mod  # (s&1)^1 是相反奇偶，与这类前缀组成的子数组和才是奇数
            cnt[s & 1] += 1  # 累计当前前缀和的奇偶
        return ans  # 返回取模后的答案
