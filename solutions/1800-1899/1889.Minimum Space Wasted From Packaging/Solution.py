# 题目：1889. 装包裹的最小浪费空间（Minimum Space Wasted From Packaging）
# 思路：排序包裹；对每个供应商方案的箱子也排序，箱子由小到大用 bisect_right 二分出能装的包裹区间，累加箱子总体积，最后减去包裹体积和即为浪费。
# 时间复杂度：O(n log n + Σ b_i log n)；空间复杂度：O(1)，除排序外只用常数个变量（inf、bisect_right 由判题器的 from math import * / from bisect import * 提供）。
class Solution:  # LeetCode 约定的题解类
    def minWastedSpace(self, packages: List[int], boxes: List[List[int]]) -> int:  # packages：各包裹尺寸；boxes：各供应商方案的箱子尺寸，返回最小浪费空间
        mod = 10**9 + 7  # 结果按题目要求对 1e9+7 取模
        ans = inf  # inf 来自判题器的 from math import *，表示「还没有可行方案」
        packages.sort()  # 包裹就地升序排序，后续才能按区间批量分配
        for box in boxes:  # 逐个供应商方案尝试
            box.sort()  # 该方案的箱子也升序排列，才能贪心地由小到大装包裹
            if packages[-1] > box[-1]:  # 最大的包裹比最大的箱子还大，该方案必然装不下
                continue  # 跳过这个方案
            s = i = 0  # s 是箱子总体积；i 是尚未装箱的包裹起始下标（链式赋值同时置 0）
            for b in box:  # 按箱子从小到大扫描
                j = bisect_right(packages, b, lo=i)  # bisect_right 来自 from bisect import *，lo=i 表示只在未装箱的区间里二分
                s += (j - i) * b  # 区间 [i, j) 的包裹都装进体积为 b 的箱子，累加总体积
                i = j  # 已装好的包裹不再参与后续箱子，起点右移
            ans = min(ans, s)  # 用当前方案的总体积刷新最小值
        if ans == inf:  # 所有方案都装不下
            return -1  # 按题目要求返回 -1
        return (ans - sum(packages)) % mod  # 总浪费 = 箱子总体积 - 包裹体积和，再对 1e9+7 取模
