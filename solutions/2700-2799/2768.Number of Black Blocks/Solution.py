# 题目：2768. 黑格子的数目（Number of Black Blocks）
# 思路：一个黑格子只可能影响它作为四个角的 4 个 2×2 块，用 Counter 统计每个块的黑格数，再用块总数减去被占用的块得到全白块数。
# 时间复杂度：O(k)，k 为黑格子个数；空间复杂度：O(k)，Counter 最多记录 4k 个块。
class Solution:  # LeetCode 约定的题解类
    def countBlackBlocks(  # m 行 n 列的网格；coordinates 是黑格子的坐标列表（形参跨两行书写）
        self, m: int, n: int, coordinates: List[List[int]]  # 依次是行数、列数与黑格子坐标
    ) -> List[int]:  # 返回长度 5 的数组，ans[c] 表示含 c 个黑格子的块数
        cnt = Counter()  # 键是 2×2 块的左上角坐标，值是块内的黑格子数量
        for x, y in coordinates:  # 遍历每一个黑格子
            for a, b in pairwise((0, 0, -1, -1, 0)):  # pairwise 把 (0,0,-1,-1,0) 相邻两项配对成四个块的左上角偏移
                i, j = x + a, y + b  # 某个可能包含该黑格子的块左上角坐标
                if 0 <= i < m - 1 and 0 <= j < n - 1:  # 左上角合法说明这个 2×2 块完全落在网格内
                    cnt[(i, j)] += 1  # 该块的黑格子数加一
        ans = [0] * 5  # ans[c] 表示黑格子数为 c 的块数，c 最多为 4
        for x in cnt.values():  # 遍历每个至少含一个黑格子的块，x 是它的黑格数
            ans[x] += 1  # 黑格数为 x 的块数加一
        ans[0] = (m - 1) * (n - 1) - len(cnt.values())  # 全白块数 = 块总数 - 至少含一个黑格子的块数
        return ans  # 返回统计结果
