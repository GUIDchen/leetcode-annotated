# 题目：2297. 跳跃游戏 VIII（Jump Game VIII）
# 思路：两遍单调栈求出每个位置右侧最近的不低于/严格低于它的落点并连边，再按下标递增顺序做 DP。
# 时间复杂度：O(n)，每个下标最多入栈出栈常数次；空间复杂度：O(n)，邻接表与 DP 数组。
class Solution:  # LeetCode 约定的题解类
    def minCost(self, nums: List[int], costs: List[int]) -> int:  # nums：各块石头的高度；costs：落到某块石头的花费
        n = len(nums)  # n 为石头个数
        g = defaultdict(list)  # g[i]：从 i 一步能跳到的下标集合，用 defaultdict 免去判空
        stk = []  # 单调栈，存放下标，从右往左扫描
        for i in range(n - 1, -1, -1):  # 第一遍：从右向左遍历
            while stk and nums[stk[-1]] < nums[i]:  # 弹出高度严格小于 nums[i] 的下标，它们会被 i 挡住
                stk.pop()  # 这些位置不可能再成为左侧元素的最近「不低于」目标
            if stk:  # 栈非空说明找到了满足条件的落点
                g[i].append(stk[-1])  # 连边 i → 栈顶：nums[i] <= nums[j] 且中间元素都严格小于 nums[i]
            stk.append(i)  # i 入栈，留待左侧元素匹配

        stk = []  # 清空栈，准备第二遍扫描
        for i in range(n - 1, -1, -1):  # 第二遍：求右侧最近且高度严格低于 nums[i] 的位置
            while stk and nums[stk[-1]] >= nums[i]:  # 弹出高度不低于 nums[i] 的下标，它们会挡住更矮的落点
                stk.pop()  # 只保留严格更矮的候选
            if stk:  # 栈非空说明找到更矮的落点
                g[i].append(stk[-1])  # 连边 i → 栈顶
            stk.append(i)  # i 入栈，留待左侧元素匹配

        f = [inf] * n  # f[i] 表示到达第 i 块石头的最小总花费，先初始化为无穷大
        f[0] = 0  # 起点不需要任何花费
        for i in range(n):  # 所有边都指向更大的下标，按 i 递增顺序即可完成 DP
            for j in g[i]:  # 枚举从 i 一步可达的落点 j
                f[j] = min(f[j], f[i] + costs[j])  # 落到 j 要支付 costs[j]，取更小的方案
        return f[n - 1]  # 返回到达终点的最小总花费
