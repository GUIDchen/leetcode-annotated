# 题目：3095. 或值至少为 K 的最短子数组 I（Shortest Subarray With OR at Least K I）
# 思路：维护滑动窗口 [i, j]，cnt[h] 记录窗口内第 h 位上 1 的个数，s 是窗口内所有数的按位或；当 s >= k 时不断右移左边界并更新最短长度。
# 时间复杂度：O(n × 32)，每个元素最多进出窗口一次；空间复杂度：O(32)，只用了长度 32 的计数数组。
class Solution:  # LeetCode 约定的题解类
    def minimumSubarrayLength(self, nums: List[int], k: int) -> int:  # nums 是数组，k 是或值下限
        n = len(nums)  # 数组长度
        cnt = [0] * 32  # cnt[h]：窗口内第 h 位为 1 的元素个数
        ans = n + 1  # 最短长度初值取不可能的 n+1，方便最后判断无解
        s = i = 0  # s 是窗口或值，i 是左边界
        for j, x in enumerate(nums):  # j 是右边界，x 是新进入窗口的元素
            s |= x  # 把新元素并入窗口或值
            for h in range(32):  # 统计新元素各个二进制位
                if x >> h & 1:  # 第 h 位为 1 才需要计数
                    cnt[h] += 1  # 该位为 1 的个数加一
            while s >= k and i <= j:  # 窗口合法时不断右移左边界，尝试更短的子数组
                ans = min(ans, j - i + 1)  # 用当前窗口长度更新答案
                y = nums[i]  # 即将移出窗口的元素
                for h in range(32):  # 逐位移除 y 的贡献
                    if y >> h & 1:  # y 的第 h 位为 1
                        cnt[h] -= 1  # 该位计数减一
                        if cnt[h] == 0:  # 窗口中已经没有这一位了
                            s ^= 1 << h  # 把或值中的这一位清掉
                i += 1  # 左边界右移
        return -1 if ans > n else ans  # 全程没找到合法子数组就返回 -1
