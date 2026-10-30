# 3936. 将 0 移到末尾的最少交换次数 / Minimum Swaps to Move Zeros to End
# 核心思路：左右双指针向中间收缩，把左侧第一个 0 与右侧第一个非 0 配对，每成功配一对交换次数加 1。
# 复杂度：时间 O(n)，空间 O(1)。
class Solution:  # 题解类定义
    def minimumSwaps(self, nums: list[int]) -> int:  # 主函数：计算把 0 全部移到末尾的最少交换次数
        ans = 0  # 交换次数计数
        n = len(nums)  # 数组长度
        i, j = 0, n - 1  # 左右两个指针的初始位置
        while i < j:  # 两指针未相遇时继续配对
            while i < n and nums[i] != 0:  # 从左找到第一个 0
                i += 1  # 左指针右移
            while j and nums[j] == 0:  # 从右找到第一个非 0
                j -= 1  # 右指针左移
            if i >= j:  # 没有可交换的一对
                break  # 结束循环
            ans += 1  # 交换次数加 1
            i += 1  # 左指针右移
            j -= 1  # 右指针左移
        return ans  # 返回最少交换次数
