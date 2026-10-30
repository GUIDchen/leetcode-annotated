# 题目：1040. 移动石子直到连续 II（Moving Stones Until Consecutive II）
# 思路：先排序；最少步数用长度不超过 n 的滑动窗口求最多能复用的连续石子，并特判「n-1 颗石子已连续且只差一格」；最多步数等于两端空隙中较大的一个。
# 时间复杂度：O(n log n)，由排序主导；空间复杂度：O(1)，只用常数个变量（不含排序自身开销）。
class Solution:  # LeetCode 约定的题解类
    def numMovesStonesII(self, stones: List[int]) -> List[int]:  # stones 是各石子位置，返回 [最少移动次数, 最多移动次数]
        stones.sort()  # 先按位置升序排序，方便后面用滑动窗口统计连续区间
        mi = n = len(stones)  # 最少移动次数初值取最坏情况 n；同时取出石子总数 n
        mx = max(stones[-1] - stones[1] + 1, stones[-2] - stones[0] + 1) - (n - 1)  # 最多移动次数：擦掉左端或右端一颗石子后，剩余区间的空格数取较大者
        i = 0  # 滑动窗口左端点
        for j, x in enumerate(stones):  # 枚举窗口右端点 j 及其石子位置 x
            while x - stones[i] + 1 > n:  # 窗口跨度超过 n 时，右移左端收缩窗口，保证窗口能塞进长度 n 的连续段
                i += 1  # 收缩左边界，让窗口覆盖的位置数不超过 n
            if j - i + 1 == n - 1 and x - stones[i] == n - 2:  # 特判：窗口里已有 n-1 颗连续石子，且与外面那颗只隔一格（如 1,2,3,5）
                mi = min(mi, 2)  # 这种形状两步就能连续（先把多余那颗塞进空格，再补齐另一端）
            else:  # 一般情况分支开始
                mi = min(mi, n - (j - i + 1))  # 一般情况：把窗口外的 n-(j-i+1) 颗石子逐个填进窗口内的空位
        return [mi, mx]  # 返回 [最少移动次数, 最多移动次数]
