# 题目：845. 数组中的最长山脉（Longest Mountain in Array）
# 思路：预处理每个位置向左的上升长度 f 与向右的下降长度 g，枚举山顶把两者拼起来取最大值。
# 时间复杂度：O(n)，三次线性遍历；空间复杂度：O(n)，两个长度数组。
class Solution:  # LeetCode 约定的题解类
    def longestMountain(self, arr: List[int]) -> int:  # arr 是输入数组；返回最长山脉长度，没有山脉时返回 0
        n = len(arr)  # 数组长度
        f = [1] * n  # f[i]：以 i 结尾的最长连续上升段长度，至少为 1
        g = [1] * n  # g[i]：以 i 开头的最长连续下降段长度，至少为 1
        for i in range(1, n):  # 从左到右扫描，计算每个位置向左的上升长度
            if arr[i] > arr[i - 1]:  # 当前元素比前一个大，上升段可以延长
                f[i] = f[i - 1] + 1  # 接上前一个位置的上升长度
        ans = 0  # 答案初值为 0，表示暂时没有山脉
        for i in range(n - 2, -1, -1):  # 从右往左扫描，计算每个位置向右的下降长度
            if arr[i] > arr[i + 1]:  # 当前元素比后一个大，从 i 开始可以下降
                g[i] = g[i + 1] + 1  # 接上后一个位置的下降长度
                if f[i] > 1:  # f[i] > 1 说明 i 左侧有上升段，i 才能当山顶
                    ans = max(ans, f[i] + g[i] - 1)  # 山脉长度 = 上升段 + 下降段 - 1（山顶被重复计算一次）
        return ans  # 返回最长山脉长度
