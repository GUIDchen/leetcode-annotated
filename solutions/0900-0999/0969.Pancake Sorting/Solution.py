# 题目：969. 煎饼排序（Pancake Sorting）
# 思路：每轮把当前最大的未归位数用一次翻转提到开头，再整体翻转把它送到目标下标，记录每次翻转的长度。
# 时间复杂度：O(n^2)，每轮扫描找最大值 O(n)；空间复杂度：O(1)，只用了常数个额外变量（不计输出）。
class Solution:  # LeetCode 约定的题解类
    def pancakeSort(self, arr: List[int]) -> List[int]:  # arr 是待排序数组，返回每次翻转的长度（1-based）
        def reverse(arr, j):  # 辅助函数：原地翻转 arr 的前 j+1 个元素（下标区间 [0, j]）
            i = 0  # 双指针，i 从左端开始
            while i < j:  # 两指针相遇前持续交换
                arr[i], arr[j] = arr[j], arr[i]  # 交换左右两端的元素
                i, j = i + 1, j - 1  # 两指针向中间收拢

        n = len(arr)  # n 为数组长度
        ans = []  # 记录每次翻转的长度序列
        for i in range(n - 1, 0, -1):  # 从末尾往前逐位归位，本轮要归位的目标值是 i+1
            j = i  # 从下标 i 开始向前查找目标值 i+1 的位置
            while j > 0 and arr[j] != i + 1:  # 向前扫描，直到找到目标值或到达下标 0
                j -= 1  # 下标前移一位
            if j < i:  # 找到目标值且不在目标位置时才需要翻转
                if j > 0:  # 目标值不在首位时，先把它翻到最前面
                    ans.append(j + 1)  # 记录这次翻转的长度 j+1
                    reverse(arr, j)  # 翻转前 j+1 个元素，把目标值送到开头
                ans.append(i + 1)  # 记录把目标值翻到正确位置所用的翻转长度 i+1
                reverse(arr, i)  # 翻转前 i+1 个元素，目标值落到下标 i
        return ans  # 返回所有翻转操作
