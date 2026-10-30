# 题目：1182. 与目标颜色间的最短距离（Shortest Distance to Target Color）
# 思路：预处理两个方向表：right[i][c] 为从 i 往右第一个颜色 c 的位置，left[i][c] 为 i 左边最近颜色 c 的位置；
#       查询时两侧取更近的一侧即可，都不存在则返回 -1。
class Solution:  # LeetCode 约定的题解类
    def shortestDistanceColor(  # colors 为颜色数组，queries 每项是 [下标, 目标颜色]
        self, colors: List[int], queries: List[List[int]]  # 签名换行只是排版，形参含义同上
    ) -> List[int]:  # 返回每个查询的最短距离
        n = len(colors)  # 数组长度
        right = [[inf] * 3 for _ in range(n + 1)]  # right[i][c]：从 i 向右第一个颜色 c 的位置，初始用 inf 哨兵表示不存在
        for i in range(n - 1, -1, -1):  # 从右往左倒推，保证 right[i+1] 已算好
            for j in range(3):  # 枚举 3 种颜色
                right[i][j] = right[i + 1][j]  # 先整体继承右邻位置的最近目标信息
            right[i][colors[i] - 1] = i  # 当前位置的颜色最近就是它自己，覆盖继承值
        left = [[-inf] * 3 for _ in range(n + 1)]  # left[i][c]：i 左边最近颜色 c 的位置，初始用 -inf 哨兵
        for i, c in enumerate(colors, 1):  # 从左往右构造，enumerate 从 1 开始，i 表示“前 i 个元素”
            for j in range(3):  # 枚举 3 种颜色
                left[i][j] = left[i - 1][j]  # 先整体继承前一个位置的最近目标信息
            left[i][c - 1] = i - 1  # 前 i 个元素里最新出现的颜色位于下标 i-1
        ans = []  # 按查询顺序保存答案
        for i, c in queries:  # 逐个查询取位置与目标颜色（颜色转 0 基下标）
            d = min(i - left[i + 1][c - 1], right[i][c - 1] - i)  # 左右两侧距离取较小者，哨兵会让其中一侧变成巨大值
            ans.append(-1 if d > n else d)  # 距离超过 n 说明该颜色从未出现，返回 -1
        return ans  # 返回全部查询答案
