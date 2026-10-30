# 题目：1574. 删除最短的子数组使剩余数组有序（Shortest Subarray to be Removed to Make Array Sorted）
# 思路：先求出最长非递减前缀终点 i 与最长非递减后缀起点 j；答案先取只保留一侧的代价，再枚举前缀末尾 l，在有序后缀里二分第一个不小于 arr[l] 的位置 r，删除区间 (l, r) 得到候选答案。
# 时间复杂度：O(n log n)，枚举前缀 O(n) 次、每次二分 O(log n)；空间复杂度：O(1)，只用常数个下标变量。
class Solution:  # LeetCode 约定的题解类
    def findLengthOfShortestSubarray(self, arr: List[int]) -> int:  # arr 是输入数组，返回需要删除的最短子数组长度
        n = len(arr)  # 数组长度，后续所有下标边界都基于它
        i, j = 0, n - 1  # i 为最长非递减前缀末位，j 为最长非递减后缀首位
        while i + 1 < n and arr[i] <= arr[i + 1]:  # 只要右侧邻居不小于自己，前缀就能继续向右延伸
            i += 1  # 前缀右扩一位
        while j - 1 >= 0 and arr[j - 1] <= arr[j]:  # 只要左侧邻居不大于自己，后缀就能继续向左延伸
            j -= 1  # 后缀左扩一位
        if i >= j:  # 前后缀已重叠或相邻，说明整个数组本身非递减
            return 0  # 无需删除任何元素
        ans = min(n - i - 1, j)  # 只保留一侧的两种代价取较小者：删掉 i 之后的部分，或删掉 j 之前的部分
        for l in range(i + 1):  # 枚举保留下来的前缀末尾位置 l
            r = bisect_left(arr, arr[l], lo=j)  # 在后缀 j..n-1 中二分出第一个 >= arr[l] 的下标 r
            ans = min(ans, r - l - 1)  # 删除开区间 (l, r) 内的所有元素，长度即 r-l-1
        return ans  # 返回最短删除长度
