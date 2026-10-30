# 4067. 数对和受限的最长子数组  Longest Subarray With Restricted Pair Sums
# 核心思路：维护窗口内所有数对的和与差的计数，新元素若与窗口内某元素的和或差相同就左移窗口直到不冲突。
# 复杂度：时间 O(n^2)，空间 O(mx)，其中 mx 为数组最大值。

class Solution:
    def maxSubarray(self, nums: List[int]) -> int:  # 返回满足“任意两数之和互不相同且之差互不相同”的最长子数组长度
        mx = max(nums)  # 数组最大值，用于确定计数数组规模
        cnt_s = [0] * (mx << 1 | 1)  # 统计窗口内每种两数之和出现的次数，长度 2*mx+1
        cnt_d = [0] * (mx + 1)  # 统计窗口内每种两数之差出现的次数
        ans = l = 0  # ans 记录最长长度，l 为窗口左边界

        for r, x in enumerate(nums):  # 枚举窗口右端点 r 与新元素 x
            while cnt_s[x] > 0 or cnt_d[x] > 0:  # 新元素与窗口内某元素之和或差等于 x，产生冲突
                y = nums[l]  # 取出窗口最左元素
                l += 1  # 左边界右移
                for z in nums[l:r]:  # 枚举移出 y 之后窗口中剩余的元素
                    cnt_s[y + z] -= 1  # 撤销 y 与 z 之和的计数
                    cnt_d[abs(y - z)] -= 1  # 撤销 y 与 z 之差的计数

            for y in nums[l:r]:  # 把 x 与窗口内每个已有元素配对
                cnt_s[x + y] += 1  # 累加两数之和的计数
                cnt_d[abs(x - y)] += 1  # 累加两数之差的计数

            ans = max(ans, r - l + 1)  # 用当前窗口长度更新答案
        return ans  # 返回最长子数组长度
