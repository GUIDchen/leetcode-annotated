# 题目：1536. 排布二进制网格的最少交换次数（Minimum Swaps to Arrange a Binary Grid）
# 思路：先求每行最右 1 的列号，再自上而下为第 i 行贪心挑选第一行 pos<=i 的行，用相邻交换把它上移 j-i 位。
# 时间复杂度：O(n²)，找候选加冒泡上移；空间复杂度：O(n)，存每行最右 1 的位置。
class Solution:  # LeetCode 约定的题解类
    def minSwaps(self, grid: List[List[int]]) -> int:  # grid 是 n×n 的 01 网格
        n = len(grid)  # 网格边长
        pos = [-1] * n  # pos[i] 存第 i 行最右 1 的列号，-1 表示整行都是 0
        for i in range(n):  # 逐行处理
            for j in range(n - 1, -1, -1):  # 从最右一列向左扫描
                if grid[i][j] == 1:  # 遇到第一个 1
                    pos[i] = j  # 记录它所在的列号
                    break  # 已是最右的 1，跳出内层循环
        ans = 0  # 交换次数从 0 开始累计
        for i in range(n):  # 自上而下确定第 i 行
            k = -1  # k 存被选中要搬到第 i 行的行号
            for j in range(i, n):  # 只在第 i 行及以下找候选，上面的行已固定
                if pos[j] <= i:  # 该行最右 1 已在第 i 列左侧（含 i），放到第 i 行即满足右上三角全 0
                    ans += j - i  # 上移 j-i 行就是 j-i 次相邻交换
                    k = j  # 记下选中的行号
                    break  # 选最近的一行，代价最小
            if k == -1:  # 找不到候选行，说明无法排布
                return -1  # 返回 -1
            while k > i:  # 把选中的行逐行向上冒泡到第 i 行
                pos[k], pos[k - 1] = pos[k - 1], pos[k]  # 相邻两行交换，等价于在 pos 数组里做一次相邻交换
                k -= 1  # 继续向上冒泡
        return ans  # 返回最少交换次数
