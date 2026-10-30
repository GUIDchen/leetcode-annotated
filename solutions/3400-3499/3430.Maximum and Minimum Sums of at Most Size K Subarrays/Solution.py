# 3430. Maximum and Minimum Sums of at Most Size K Subarrays / 3430. 最多 K 个元素的子数组的最值之和
# 核心思路：滑动窗口 + 两套单调队列，用 shares 维护窗口内所有子数组的最大值之和与最小值之和。
# 复杂度：时间 O(n)，空间 O(n)。

class Solution:  # LeetCode 题解统一使用 Solution 类
    def minMaxSubarraySum(self, nums: list[int], k: int) -> int:  # 返回所有长度不超过 k 的子数组中最大值之和与最小值之和的总和
        subarrays_max_min_sum = 0  # 累计所有子数组的最大值与最小值总和

        max_stack: deque[list[int]] = deque([])  # Format: [idx, num, shares].  最大栈元素格式：[下标, 数值, 该数值作为最值的子数组个数]
        subarrays_max_sum = 0  # 当前窗口内所有子数组的最大值之和

        min_stack: deque[list[int]] = deque([])  # Format: [idx, num, shares].  最小栈元素格式：[下标, 数值, 该数值作为最值的子数组个数]
        subarrays_min_sum = 0  # 当前窗口内所有子数组的最小值之和

        for end_idx, num in enumerate(nums):  # 枚举窗口右端点 end_idx 与当前值 num
            start_idx = max(0, end_idx - k + 1)  # 窗口左端点下界，保证窗口长度不超过 k

            # Window start idx slides by 1: must update stacks' info.
            if start_idx > 0:  # 窗口左端点右移一位，需要同步修正两个栈的栈首份额与和值
                max_stack[0][2] -= 1  # Decrement stack's front num shares.  栈首数值的份额减一，表示少了一个以它为最值的子数组
                subarrays_max_sum -= max_stack[0][1]  # 该次贡献消失，最大值之和减去栈首数值

                if max_stack[0][0] < start_idx:  # Front num out of window.  最大栈栈首下标已经滑出窗口
                    max_stack.popleft()  # 弹出最大栈栈首，保证栈内下标有效

                min_stack[0][2] -= 1  # Decrement stack's front num shares.  最小栈栈首份额同样减一
                subarrays_min_sum -= min_stack[0][1]  # 最小值之和减去栈首数值

                if min_stack[0][0] < start_idx:  # Front num out of window.  最小栈栈首下标已经滑出窗口
                    min_stack.popleft()  # 弹出最小栈栈首

            max_shares = 1  # Base case.  新元素自身至少覆盖一个子数组
            subarrays_max_sum += num  # 先把它自己作为一个子数组的最大值计入

            while max_stack and max_stack[-1][1] <= num:  # 维护最大值栈的单调递减性：栈尾数值不大于当前值就合并
                _, prev_num, prev_shares = max_stack.pop()  # 弹出栈尾并取出其数值与份额

                max_shares += prev_shares  # Max shares transition.  被合并的份额累加到当前数值上

                # Reflect transition in max sum.
                subarrays_max_sum += (num - prev_num) * prev_shares  # 最值从 prev_num 换成 num，最大值之和增加 (num - prev_num) * prev_shares

            max_stack.append([end_idx, num, max_shares])  # 把当前值按合并后的份额压入最大值栈

            min_shares = 1  # Base case.  新元素自身至少覆盖一个子数组
            subarrays_min_sum += num  # 先把它自己作为一个子数组的最小值计入

            while min_stack and min_stack[-1][1] >= num:  # 维护最小值栈的单调递增性：栈尾数值不小于当前值就合并
                _, prev_num, prev_shares = min_stack.pop()  # 弹出栈尾并取出其数值与份额

                min_shares += prev_shares  # Min shares transition.  被合并的份额累加到当前数值上

                # Reflect transition in min sum.
                subarrays_min_sum += (num - prev_num) * prev_shares  # 最小值从 prev_num 换成 num，最小值之和增加 (num - prev_num) * prev_shares

            min_stack.append([end_idx, num, min_shares])  # 把当前值按合并后的份额压入最小值栈

            subarrays_max_min_sum += subarrays_max_sum + subarrays_min_sum  # 右端点固定时，窗口内所有合法子数组的最值之和累加进答案

        return subarrays_max_min_sum  # 返回所有长度不超过 k 的子数组的最值总和
