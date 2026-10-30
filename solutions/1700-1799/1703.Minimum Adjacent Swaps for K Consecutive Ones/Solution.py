# 题目：1703. 得到连续 K 个 1 的最少相邻交换次数（Minimum Adjacent Swaps for K Consecutive Ones）
# 思路：记录所有 1 的下标，用长度为 k 的滑动窗口枚举，窗口的中位 1 原地不动、其余 1 向它靠拢最省；借助前缀和 O(1) 求窗口内的交换代价。
# 时间复杂度：O(n)，收集下标与滑动窗口各一遍；空间复杂度：O(n)，存储下标数组与前缀和数组。
class Solution:  # LeetCode 约定的题解类
    def minMoves(self, nums: List[int], k: int) -> int:  # nums 是 0/1 数组，k 是要求的连续 1 的个数
        arr = [i for i, x in enumerate(nums) if x]  # 收集每个 1 的原始下标
        s = list(accumulate(arr, initial=0))  # 前缀和，s[i] 表示 arr 前 i 个元素之和，initial=0 保证长度为 m+1
        ans = inf  # 答案初值设为无穷大，方便后面取 min
        x = (k + 1) // 2  # 窗口内中位 1 及其左边元素的个数（向上取整）
        y = k - x  # 中位 1 右边的元素个数
        for i in range(x - 1, len(arr) - y):  # 枚举中位 1 的下标，保证左右各取够元素
            j = arr[i]  # 中位 1 的原始下标，作为这 k 个 1 聚集的锚点
            ls = s[i + 1] - s[i + 1 - x]  # 左侧 x 个 1（含中位）的原始下标和
            rs = s[i + 1 + y] - s[i + 1]  # 右侧 y 个 1 的原始下标和
            a = (j + j - x + 1) * x // 2 - ls  # 左侧 x 个 1 紧贴到 j 左侧需要的交换次数
            b = rs - (j + 1 + j + y) * y // 2  # 右侧 y 个 1 紧贴到 j 右侧需要的交换次数
            ans = min(ans, a + b)  # 用当前锚点的总代价更新最优解
        return ans  # 返回最少的相邻交换次数
