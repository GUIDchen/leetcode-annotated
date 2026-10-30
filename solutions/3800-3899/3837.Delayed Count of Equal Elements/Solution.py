# 3837. 相等元素的延迟计数 / Delayed Count of Equal Elements（中等）
# 核心思路：倒序遍历并维护一个滑动计数窗口；处理下标 i 时把 nums[i+k+1] 加入计数器，此时窗口中恰好是下标大于 i+k 的所有元素，答案就是其中与 nums[i] 相等的个数。
# 复杂度：时间 O(n)，空间 O(n)。
class Solution:  # LeetCode 要求的类名
    def delayedCount(self, nums: List[int], k: int) -> List[int]:  # 返回每个下标 i 对应的延迟计数值
        n = len(nums)  # 数组长度
        cnt = Counter()  # 计数器：记录下标大于 i+k 的元素出现次数
        ans = [0] * n  # 答案数组，初始全为 0
        for i in range(n - k - 2, -1, -1):  # 从右往左枚举；起点保证 i+k+1 不越界
            cnt[nums[i + k + 1]] += 1  # 把下标 i+k+1 的元素纳入窗口（窗口右端逐步扩张）
            ans[i] = cnt[nums[i]]  # 窗口内与 nums[i] 相等的元素个数即为答案
        return ans  # 返回全部下标的结果
