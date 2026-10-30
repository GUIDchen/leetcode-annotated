# 题目：956. 最高的广告牌（Tallest Billboard）
# 思路：@cache 记忆化搜索，dfs(i, j) 表示处理到第 i 根钢筋、两柱高度差为 j 时还能增加的公共高度，分不用/放高侧/放矮侧三种转移。
# 时间复杂度：O(n·s)，s 为钢筋总长，状态数为 n×(s+1)；空间复杂度：O(n·s)，缓存保存全部状态。
class Solution:  # LeetCode 约定的题解类
    def tallestBillboard(self, rods: List[int]) -> int:  # rods 是每根钢筋的长度，返回两根柱子能达到的最大公共高度
        @cache  # @cache 等价于 C++ 里的记忆化数组：同一个状态只算一次
        def dfs(i: int, j: int) -> int:  # i：当前钢筋下标；j：两柱的高度差；返回还能增加的公共高度
            if i >= len(rods):  # 递归出口：钢筋已经用完
                return 0 if j == 0 else -inf  # 差为 0 表示两柱等高，合法返回 0；否则该状态不可用，用 -inf 表示
            ans = max(dfs(i + 1, j), dfs(i + 1, j + rods[i]))  # 不用这根钢筋，或者把它放到较高的一侧（差值变大、公共高度不变）
            ans = max(ans, dfs(i + 1, abs(rods[i] - j)) + min(j, rods[i]))  # 放到较矮的一侧：差值变成 |rods[i] - j|，公共高度增加 min(j, rods[i])
            return ans  # 返回三种选择里的最优值，@cache 会自动把它缓存起来

        return dfs(0, 0)  # 从第 0 根钢筋、高度差 0 出发开始搜索
