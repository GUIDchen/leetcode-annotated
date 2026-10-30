# 题目：624. 数组列表中的最大距离（Maximum Distance in Arrays）
# 思路：每组内部有序，扫描时用「历史全局最小值/最大值」与当前组的另一端组合，边更新边取最大距离。
# 时间复杂度：O(m)，m 为数组组数；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxDistance(self, arrays: List[List[int]]) -> int:  # arrays 是若干组升序数组，要求取自不同组的两个元素的最大差值绝对值
        ans = 0  # 记录目前为止的最大距离，初始为 0
        mi, mx = arrays[0][0], arrays[0][-1]  # 前若干组里出现过的最小值与最大值（每组内部升序，首元素最小、末元素最大）
        for arr in arrays[1:]:  # 从第二组开始遍历，边更新历史最值边计算距离
            a, b = abs(arr[0] - mx), abs(arr[-1] - mi)  # 两种跨组候选：本组最小 vs 历史最大；本组最大 vs 历史最小
            ans = max(ans, a, b)  # 三者取最大，刷新答案
            mi = min(mi, arr[0])  # 把本组最小值并入历史最小
            mx = max(mx, arr[-1])  # 把本组最大值并入历史最大
        return ans  # 返回最终的最大距离
