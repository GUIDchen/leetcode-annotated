# 题目：3499. 操作后最大活跃区段数 I（Maximize Active Section with Trade I）
# 思路：一次操作等价于把夹在 '1' 之间的两段 '0' 一并变 '1'，收益是这两段 '0' 的长度和，故答案为 '1' 的总数加上相邻两段 '0' 长度和的最大值。
# 时间复杂度：O(n)，双指针一趟扫完所有连续段；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxActiveSectionsAfterTrade(self, s: str) -> int:  # s：只含 '0' / '1' 的二进制字符串
        n = len(s)  # 字符串长度
        ans = i = 0  # ans 累计所有 '1' 的个数，i 是当前扫描位置
        pre, mx = -inf, 0  # pre 记录上一段连续 '0' 的长度（初值 -inf 表示还没有上一段）；mx 记录相邻两段 '0' 长度和的最大值
        while i < n:  # 逐段扫描整个字符串
            j = i + 1  # j 指向当前连续段的右边界（开区间）
            while j < n and s[j] == s[i]:  # 向后扩展，直到字符发生变化
                j += 1  # 同字符就继续右移
            cur = j - i  # 当前连续段的长度
            if s[i] == "1":  # 这一段全是 '1'，本来就活跃
                ans += cur  # 活跃字符数直接累加
            else:  # 这一段是 '0'，可能被一次操作整体翻转
                mx = max(mx, pre + cur)  # 用「上一段 0 + 本段 0」更新一次操作的最大收益
                pre = cur  # 本段成为下一段的「上一段 0」
            i = j  # 跳到下一段的起点
        ans += mx  # 活跃的 '1' 加上一次操作的最大收益
        return ans  # 返回最多活跃区段数
