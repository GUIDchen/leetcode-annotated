# 题目：941. 有效的山脉数组（Valid Mountain Array）
# 思路：双指针相向爬坡，左指针只走严格上坡、右指针只走严格下坡，最终在同一个峰顶相遇即为合法山脉数组。
# 时间复杂度：O(n)，每个元素最多访问一次；空间复杂度：O(1)，只用两个下标。
class Solution:  # LeetCode 约定的题解类
    def validMountainArray(self, arr: List[int]) -> bool:  # arr 是待判定数组，返回它是否为山脉数组
        n = len(arr)  # 数组长度
        if n < 3:  # 山脉至少需要上坡、峰顶、下坡三个元素
            return False  # 长度不足直接否决
        i, j = 0, n - 1  # i 从左往右爬坡，j 从右往左爬坡
        while i + 1 < n - 1 and arr[i] < arr[i + 1]:  # 左指针严格上升，i + 1 < n - 1 防止越过峰顶
            i += 1  # 往右走一步继续上坡
        while j - 1 > 0 and arr[j - 1] > arr[j]:  # 右指针严格下降，j - 1 > 0 防止越过峰顶
            j -= 1  # 往左走一步继续下坡
        return i == j  # 在同一个峰顶相遇才是合法山脉
