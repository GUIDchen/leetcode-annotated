# 3795. 不同元素和至少为 K 的最短子数组长度 / Minimum Subarray Length With Distinct Sum At Least K
# 核心思路：滑动窗口维护窗口内不同元素之和，右端点扩张、和达到 k 时收缩左端点并更新最短长度。
# 复杂度：时间 O(n)，空间 O(n)。
class Solution:  # 定义 LeetCode 题解类
    def minLength(self, nums: List[int], k: int) -> int:  # 返回不同元素和至少为 k 的最短子数组长度
        cnt = defaultdict(int)  # 窗口内每个元素的出现次数
        n = len(nums)  # 数组长度
        ans = n + 1  # 最短长度，先设为不可能的值
        s = l = 0  # s 为不同元素之和，l 为窗口左端点
        for r, x in enumerate(nums):  # 右端点向右扩展
            cnt[x] += 1  # 当前元素进入窗口
            if cnt[x] == 1:  # 该元素在窗口内首次出现
                s += x  # 把它的值计入不同元素之和
            while s >= k:  # 和已满足要求，尝试收缩窗口
                ans = min(ans, r - l + 1)  # 用当前窗口长度更新最短长度
                cnt[nums[l]] -= 1  # 左端点元素移出窗口
                if cnt[nums[l]] == 0:  # 该元素在窗口内的出现次数减为 0
                    s -= nums[l]  # 从不同元素之和中扣除它的值
                l += 1  # 左端点右移
        return -1 if ans > n else ans  # 没有满足条件的子数组则返回 -1
