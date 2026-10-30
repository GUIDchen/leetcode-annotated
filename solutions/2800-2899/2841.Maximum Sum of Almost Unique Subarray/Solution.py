# 题目：2841. 几乎唯一子数组的最大和（Maximum Sum of Almost Unique Subarray）
# 思路：定长滑动窗口。用计数器维护窗口内元素频次，窗口每次右移一格，不同元素个数不少于 m 时用窗口和更新答案。
# 时间复杂度：O(n)，每个元素至多进出窗口一次；空间复杂度：O(k)，计数器最多保存窗口内 k 个元素。
class Solution:  # LeetCode 约定的题解类
    def maxSum(self, nums: List[int], m: int, k: int) -> int:  # nums 是数组，m 是不同元素个数下限，k 是子数组长度
        cnt = Counter(nums[:k])  # 记录第一个长度为 k 的窗口内各元素的出现次数
        s = sum(nums[:k])  # 第一个窗口的元素之和
        ans = s if len(cnt) >= m else 0  # 第一个窗口达标就先作为候选答案，否则保持 0
        for i in range(k, len(nums)):  # 窗口右移：新进 nums[i]，移出 nums[i - k]
            cnt[nums[i]] += 1  # 新元素加入窗口，计数加 1
            cnt[nums[i - k]] -= 1  # 移出窗口的元素计数减 1
            s += nums[i] - nums[i - k]  # 用进出的差值更新窗口和，避免重新求和
            if cnt[nums[i - k]] == 0:  # 移出元素的计数减到 0，说明窗口内已经没有它
                cnt.pop(nums[i - k])  # 删除该键，使 len(cnt) 恰好等于不同元素个数
            if len(cnt) >= m:  # 不同元素个数达到下限，窗口合法
                ans = max(ans, s)  # 尝试用更大的窗口和更新答案
        return ans  # 返回最大窗口和；没有合法子数组时仍为 0
