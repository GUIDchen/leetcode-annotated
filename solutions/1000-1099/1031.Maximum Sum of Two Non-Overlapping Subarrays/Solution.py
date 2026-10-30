# 题目：1031. 两个无重叠子数组的最大和（Maximum Sum of Two Non-Overlapping Subarrays）
# 思路：accumulate 构造前缀和 O(1) 取窗口和；分别枚举两种左右顺序，用 t 记录左侧已扫过的最佳窗口。
# 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def maxSumTwoNoOverlap(self, nums: List[int], firstLen: int, secondLen: int) -> int:  # 求长度分别为 firstLen、secondLen 的两个不重叠子数组的最大元素和
        n = len(nums)  # 数组长度
        s = list(accumulate(nums, initial=0))  # 前缀和，initial=0 让 s[0] 为 0，方便用 s[r]-s[l] 表示区间和
        ans = t = 0  # ans 记录答案；t 记录左侧已扫过窗口的最大和
        i = firstLen  # 情况一：firstLen 子数组在左，从它的右端点位置开始枚举
        while i + secondLen - 1 < n:  # 只要右侧还能放下 secondLen 长度的窗口就继续
            t = max(t, s[i] - s[i - firstLen])  # 更新左侧 firstLen 窗口的最大和
            ans = max(ans, t + s[i + secondLen] - s[i])  # 左侧最优 + 右侧当前 secondLen 窗口，更新答案
            i += 1  # 右端点右移一位
        t = 0  # 第二种前后顺序要重新开始统计左侧最大值
        i = secondLen  # 情况二：secondLen 子数组在左
        while i + firstLen - 1 < n:  # 同样保证右侧还能放下 firstLen 长度的窗口
            t = max(t, s[i] - s[i - secondLen])  # 更新左侧 secondLen 窗口的最大和
            ans = max(ans, t + s[i + firstLen] - s[i])  # 左侧最优 + 右侧当前 firstLen 窗口，更新答案
            i += 1  # 右端点右移一位
        return ans  # 返回两种顺序中的最大和
