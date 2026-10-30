# 题目：2968. 执行操作使频率分数最大（Apply Operations to Maximize Frequency Score）
# 思路：排序后二分答案，前缀和 O(1) 算出把某个窗口整体变成其中位数的代价，检查是否存在长度 mid 的可行窗口。
# 时间复杂度：O(n log n)（排序 + 二分 O(log n) 次、每次 O(n)）；空间复杂度：O(n)（前缀和）。
class Solution:  # LeetCode 约定的题解类
    def maxFrequencyScore(self, nums: List[int], k: int) -> int:  # nums：初始数组；k：总共可用的加一操作次数
        nums.sort()  # 先排序，后面只需考虑连续区间——最优解就是把一段区间都变成它的中位数
        s = list(accumulate(nums, initial=0))  # 前缀和，initial=0 让 s[0] = 0，即 s[i] 为前 i 个元素之和
        n = len(nums)  # n 为数组长度
        l, r = 0, n  # 二分区间：l 是已知可行长度，r 是上界
        while l < r:  # 收缩到区间只剩一个值
            mid = (l + r + 1) >> 1  # 取上中位数，与下面的 l = mid 配合避免死循环
            ok = False  # 标记长度 mid 是否可行
            for i in range(n - mid + 1):  # 枚举长度为 mid 的窗口，i 为左端点（range 上界 n-mid+1 表示 i <= n-mid）
                j = i + mid  # j 为窗口右端点的下一个位置，窗口覆盖 [i, j-1]
                x = nums[(i + j) // 2]  # 目标值取窗口中位数：整段都变成中位数时代价最小
                left = ((i + j) // 2 - i) * x - (s[(i + j) // 2] - s[i])  # 左半段 [i, m-1] 抬到 x 的代价 = 个数乘 x 减去这段原和
                right = (s[j] - s[(i + j) // 2]) - ((j - (i + j) // 2) * x)  # 右半段 [m, j-1] 压到 x 的代价 = 这段原和减去个数乘 x
                if left + right <= k:  # 总代价不超过 k，说明该长度可行
                    ok = True  # 标记可行
                    break  # 提前结束窗口枚举
            if ok:  # 长度 mid 可行
                l = mid  # 抬高下界，尝试更大长度
            else:  # 长度 mid 不可行
                r = mid - 1  # 收缩上界
        return l  # 二分结束，l 即最大可行频率分数
