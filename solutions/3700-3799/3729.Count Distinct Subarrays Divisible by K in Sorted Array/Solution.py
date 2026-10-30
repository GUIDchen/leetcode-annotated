# 3729. 统计有序数组中可被 K 整除的子数组数量 / Count Distinct Subarrays Divisible by K in Sorted Array
# 核心思路：先用前缀和取模统计所有元素和能被 k 整除的子数组，再按连续相同元素分组，扣掉完全由等值元素组成、与其他位置重复的计数。
# 复杂度：时间 O(n)，空间 O(min(n, k))。
class Solution:  # 定义 LeetCode 解法类
    def numGoodSubarrays(self, nums: List[int], k: int) -> int:  # 返回元素互不相同且元素和能被 k 整除的子数组数量
        cnt = Counter({0: 1})  # 计数器，空前缀余数 0 先放一个哨兵
        ans = s = 0  # ans 为答案，s 为前缀和模 k 的余数
        for x in nums:  # 遍历有序数组中的每个元素
            s = (s + x) % k  # 更新前缀和余数
            ans += cnt[s]  # 累加以当前位置结尾、与前面余数相同的子数组
            cnt[s] += 1  # 余数计数加一，供后续位置使用
        n = len(nums)  # 数组长度
        i = 0  # i 指向当前相同元素分组的起点
        while i < n:  # 逐个处理相同元素分组
            j = i + 1  # 组内扫描指针
            while j < n and nums[j] == nums[i]:  # 向右扩展，直到元素值与 nums[i] 不同
                j += 1  # 指针右移
            m = j - i  # 本组相同元素的个数
            for h in range(1, m + 1):  # 枚举从本组中取出的元素个数 h
                if (h * nums[i]) % k == 0:  # 这 h 个相同元素之和能被 k 整除
                    ans -= m - h  # 等值元素组成的子数组只保留一份，减去多余计数
            i = j  # 跳到下一个分组
        return ans  # 返回去重后的答案
