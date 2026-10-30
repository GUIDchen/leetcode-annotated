# 题目：3171. 找到按位或最接近 K 的子数组（Find Subarray With Bitwise OR Closest to K）
# 思路：位或随窗口收缩单调不增，固定右端点时用滑动窗口；用 cnt 统计窗口内每一位的 1 的个数，从而在移出元素时按位撤销贡献。
# 时间复杂度：O(n log A)，A 为最大值，位宽不超过 31；空间复杂度：O(log A)，cnt 长度等于位宽。
class Solution:  # LeetCode 约定的题解类
    def minimumDifference(self, nums: List[int], k: int) -> int:  # nums 是非负整数数组，k 是目标值，返回子数组按位或与 k 的最小差值
        m = max(nums).bit_length()  # m 是最大值的二进制位数，也是需要统计的位数上界
        cnt = [0] * m  # cnt[h] 记录窗口内第 h 位为 1 的元素个数
        s = i = 0  # s 是窗口的按位或，i 是窗口左端点
        ans = inf  # ans 记录与 k 的最小差值，初始为无穷大
        for j, x in enumerate(nums):  # j 是窗口右端点，x 是新加入窗口的元素
            s |= x  # 把新元素并入窗口的按位或
            ans = min(ans, abs(s - k))  # 用当前窗口的或值更新答案
            for h in range(m):  # 逐位统计新元素对窗口的贡献
                if x >> h & 1:  # 第 h 位为 1 才需要计数
                    cnt[h] += 1  # 该位计数加一
            while i < j and s > k:  # 或值大于 k 时收缩左端点，让或值变小以逼近 k
                y = nums[i]  # 取出左端点元素，准备撤销它的贡献
                for h in range(m):  # 逐位撤销 y 的贡献
                    if y >> h & 1:  # y 的第 h 位为 1 才有影响
                        cnt[h] -= 1  # 该位计数减一
                        if cnt[h] == 0:  # 减到 0 说明窗口内已没有数在该位为 1
                            s ^= 1 << h  # 把这一位从 s 中清掉
                i += 1  # 左端点右移，窗口缩小
                ans = min(ans, abs(s - k))  # 收缩后再次尝试更新答案
        return ans  # 返回最小差值
