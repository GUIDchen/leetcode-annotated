# 题目：1186. 删除一次得到子数组最大和（Maximum Subarray Sum with One Deletion）
# 思路：正反两次扫描分别求出以 i 结尾、以 i 开头的最大子数组和，再枚举删除位置把左右两段拼接起来。
# 时间复杂度：O(n)，三次线性遍历；空间复杂度：O(n)，两个长度为 n 的数组。
class Solution:  # LeetCode 约定的题解类
    def maximumSum(self, arr: List[int]) -> int:  # arr：最多可删除一个元素的数组，返回删除后的最大子数组和
        n = len(arr)  # 数组长度
        left = [0] * n  # left[i]：以 i 结尾的最大子数组和
        right = [0] * n  # right[i]：以 i 开头的最大子数组和
        s = 0  # 滚动变量：以当前元素结尾的最大和，初值 0 表示还没开始累加
        for i, x in enumerate(arr):  # 从左到右扫一遍
            s = max(s, 0) + x  # 前缀和为负就丢弃，等价于从 x 重新开始累加
            left[i] = s  # 记录以 i 结尾的最大子数组和
        s = 0  # 重置滚动变量，准备从右往左扫
        for i in range(n - 1, -1, -1):  # 从右到左扫一遍
            s = max(s, 0) + arr[i]  # 后缀和为负就丢弃，从 arr[i] 重新开始
            right[i] = s  # 记录以 i 开头的最大子数组和
        ans = max(left)  # 一个都不删的答案，即普通的最大子数组和
        for i in range(1, n - 1):  # 枚举被删除的下标 i，删首尾等于没删，所以从 1 到 n-2
            ans = max(ans, left[i - 1] + right[i + 1])  # 删掉 arr[i] 后，左右两段直接拼在一起
        return ans  # 返回最优答案
