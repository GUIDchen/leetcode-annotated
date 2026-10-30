# 题目：1580. 把箱子放进仓库里 II（Put Boxes Into the Warehouse II）
# 思路：每列真正可用的高度是 min(自身高度, max(左侧方向上限, 右侧方向上限))，因为箱子可以从更有利的一侧推进来；把列高与箱子都排序后，用双指针贪心依次塞入能装下的最矮列。
# 时间复杂度：O(n log n + m log m)，两边排序主导；空间复杂度：O(n)，需要 left、right 两个辅助数组。
class Solution:  # LeetCode 约定的题解类
    def maxBoxesInWarehouse(self, boxes: List[int], warehouse: List[int]) -> int:  # boxes 为箱子边长，warehouse 为各列高度，返回最多能放下的箱子数
        n = len(warehouse)  # 仓库列数
        left = [0] * n  # left[i]：箱子从左侧推入到 i 时能通过的最大高度
        right = [0] * n  # right[i]：箱子从右侧推入到 i 时能通过的最大高度
        left[0] = right[-1] = inf  # 首尾哨兵置为无穷大，表示该方向边界没有额外限制
        for i in range(1, n):  # 从左往右预处理 left
            left[i] = min(left[i - 1], warehouse[i - 1])  # i 的上限由左侧方向上限与左边相邻列高共同决定（不含 i 自身）
        for i in range(n - 2, -1, -1):  # 从右往左预处理 right
            right[i] = min(right[i + 1], warehouse[i + 1])  # i 的上限由右侧方向上限与右边相邻列高共同决定（不含 i 自身）
        for i in range(n):  # 确定每列真正可用的高度
            warehouse[i] = min(warehouse[i], max(left[i], right[i]))  # 箱子可任选更有利的一侧推入，故取左右两个方向上限的较大者
        boxes.sort()  # 箱子边长升序
        warehouse.sort()  # 仓库可用高度升序
        ans = i = 0  # ans 为已放入箱数，i 为当前可用的最矮列下标
        for x in boxes:  # 从小到大依次尝试箱子
            while i < n and warehouse[i] < x:  # 跳过装不下当前箱子的仓库列
                i += 1  # 指针右移
            if i == n:  # 仓库列已用尽
                break  # 后续箱子只会更大，提前结束
            ans, i = ans + 1, i + 1  # 放入当前箱子并占用该列，两个计数同时加一
        return ans  # 返回最多能放下的箱子数
