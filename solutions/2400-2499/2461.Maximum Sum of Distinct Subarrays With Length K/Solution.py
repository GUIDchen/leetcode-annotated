# 题目：2461. 长度为 K 子数组中的最大和（Maximum Sum of Distinct Subarrays With Length K）
# 思路：定长滑动窗口 + Counter 统计窗口内各值频次，不同值个数等于 k 时才是合法窗口，窗口和增量更新。
# 时间复杂度：O(n)，每个元素最多进出窗口一次；空间复杂度：O(k)，Counter 最多保存窗口内 k 个不同值。
class Solution:  # LeetCode 约定的题解类
    def maximumSubarraySum(self, nums: List[int], k: int) -> int:  # nums 是输入数组，k 是固定窗口长度，返回最大和
        cnt = Counter(nums[:k])  # 统计初始窗口（前 k 个元素）中每个值的出现次数，Counter 的键数就是不同值的个数
        s = sum(nums[:k])  # 初始窗口的元素和
        ans = s if len(cnt) == k else 0  # 不同值个数等于 k 说明窗口内元素互不相同，此时初始和可以作为候选答案；否则记 0 表示还没找到合法窗口
        for i in range(k, len(nums)):  # 让窗口逐格右移，i 是新进入窗口元素的下标
            cnt[nums[i]] += 1  # 新元素进窗，计数加一
            cnt[nums[i - k]] -= 1  # 窗口左侧的旧元素出窗，计数减一
            if cnt[nums[i - k]] == 0:  # 计数减到 0 说明这个值已完全离开窗口
                cnt.pop(nums[i - k])  # 删除该键，使 len(cnt) 恰好等于窗口内不同值的个数
            s += nums[i] - nums[i - k]  # 增量维护窗口和：进一个新元素、出一个旧元素
            if len(cnt) == k:  # 不同值个数等于 k，说明窗口内元素互不相同
                ans = max(ans, s)  # 刷新最大和
        return ans  # 返回答案；若不存在合法窗口则返回 0
