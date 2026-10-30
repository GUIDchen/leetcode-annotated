# 题目：1564. 把箱子放进仓库里 I（Put Boxes Into the Warehouse I）
# 思路：箱子只能从最左端推入，第 i 格的实际可用高度是左侧前缀最小值；箱子升序排序后从仓库最右侧往前贪心匹配。
# 时间复杂度：O(n log n + m log m)，排序主导；空间复杂度：O(n)，前缀最小值数组。
class Solution:  # LeetCode 约定的题解类
    def maxBoxesInWarehouse(self, boxes: List[int], warehouse: List[int]) -> int:  # boxes：每个箱子的边长；warehouse：仓库每格高度
        n = len(warehouse)  # n 为仓库格子数
        left = [warehouse[0]] * n  # left[i] 表示从最左端推到第 i 格时能通过的最大高度
        for i in range(1, n):  # 从左往右递推前缀最小值
            left[i] = min(left[i - 1], warehouse[i])  # 前面的高度限制会一路传递下来
        boxes.sort()  # 箱子按边长升序，优先安排小箱子
        i, j = 0, n - 1  # i 指向下一个待放箱子；j 是从右往左的候选位置
        while i < len(boxes):  # 还有箱子没尝试完就继续
            while j >= 0 and left[j] < boxes[i]:  # 从右往左找能容纳当前箱子的位置
                j -= 1  # 该位置太矮，继续左移
            if j < 0:  # 已经没有可用位置
                break  # 更大的箱子更放不下，结束
            i, j = i + 1, j - 1  # 放好一个箱子，同时占用掉这个位置
        return i  # i 恰好等于成功放入的箱子数
