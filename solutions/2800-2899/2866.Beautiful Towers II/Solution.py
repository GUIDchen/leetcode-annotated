# 题目：2866. 美丽塔 II（Beautiful Towers II）
# 思路：用单调栈分别求出每个位置左侧第一个更矮、右侧第一个不更高的下标，再正序/逆序递推出以 i 为山顶的左段和 f[i] 与右段和 g[i]。
# 时间复杂度：O(n)，每个下标最多进出栈一次；空间复杂度：O(n)，保存左右边界与两个求和数组。
class Solution:  # LeetCode 约定的题解类
    def maximumSumOfHeights(self, maxHeights: List[int]) -> int:  # maxHeights 是每座塔的高度上限
        n = len(maxHeights)  # 塔的数量
        stk = []  # 单调栈，存下标，其对应高度从栈底到栈顶单调不降
        left = [-1] * n  # left[i] 为 i 左边第一个严格更矮的下标，找不到时保持 -1
        for i, x in enumerate(maxHeights):  # 从左往右扫一遍求 left
            while stk and maxHeights[stk[-1]] > x:  # 栈顶更高就不可能成为后面位置的最近更矮点
                stk.pop()  # 弹出栈顶，维持栈内高度单调不降
            if stk:  # 弹完后栈顶即左边第一个严格更矮的位置
                left[i] = stk[-1]  # 记录左边界
            stk.append(i)  # 当前下标入栈，供右边的位置使用
        stk = []  # 清空栈，准备反向扫描
        right = [n] * n  # right[i] 为 i 右边第一个不高于它的下标，找不到时保持 n
        for i in range(n - 1, -1, -1):  # 从右往左扫一遍求 right
            x = maxHeights[i]  # 当前位置的高度上限
            while stk and maxHeights[stk[-1]] >= x:  # 用 >= 弹栈，等高的右侧位置留给它自己，避免重复统计
                stk.pop()  # 弹出栈顶，维持单调性
            if stk:  # 栈顶就是右边第一个严格更矮的位置
                right[i] = stk[-1]  # 记录右边界
            stk.append(i)  # 当前下标入栈，供左边的位置使用
        f = [0] * n  # f[i]：以 i 为山顶时左半段（含 i）的高度和
        for i, x in enumerate(maxHeights):  # 正序递推 f
            if i and x >= maxHeights[i - 1]:  # 左边邻居不比它高，左侧高度序列可以原样保留
                f[i] = f[i - 1] + x  # 沿用 f[i-1]，再补上自己这一格
            else:  # 左边邻居更高，需要把一段区间压低到 x
                j = left[i]  # j 是左边第一个比 x 矮的位置
                f[i] = x * (i - j) + (f[j] if j != -1 else 0)  # 区间 (j, i] 全填 x，j 以左沿用 f[j]
        g = [0] * n  # g[i]：以 i 为山顶时右半段（含 i）的高度和
        for i in range(n - 1, -1, -1):  # 逆序递推 g
            if i < n - 1 and maxHeights[i] >= maxHeights[i + 1]:  # 右边邻居不比它高，右侧序列可直接复用
                g[i] = g[i + 1] + maxHeights[i]  # 沿用 g[i+1]，再补上自己这一格
            else:  # 右边邻居更高，需要把一段区间压低到当前高度
                j = right[i]  # j 是右边第一个不高于当前值的位置
                g[i] = maxHeights[i] * (j - i) + (g[j] if j != n else 0)  # 区间 [i, j) 全填当前高度，j 以右沿用 g[j]
        return max(a + b - c for a, b, c in zip(f, g, maxHeights))  # 左右两段都含山顶，减去重复的一次后取最大
