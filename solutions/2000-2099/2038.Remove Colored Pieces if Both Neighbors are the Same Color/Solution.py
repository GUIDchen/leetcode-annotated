# 题目：2038. 如果相邻两个颜色均相同则删除当前颜色（Remove Colored Pieces if Both Neighbors are the Same Color）
# 思路：itertools.groupby 把串切成同色段，长度 L 的段该颜色玩家能删 L-2 次，比较双方总次数即可。
# 时间复杂度：O(n)，每个字符只被分组一次；空间复杂度：O(1)，只用到分组迭代器与几个计数器。
class Solution:  # LeetCode 约定的题解类
    def winnerOfGame(self, colors: str) -> bool:  # colors：仅由 'A'、'B' 组成的字符串
        a = b = 0  # a、b 分别累计 Alice 与 Bob 可删除的次数
        for c, v in groupby(colors):  # groupby 把相邻同色字符聚成一组：c 是组名（字符），v 是该组的迭代器
            m = len(list(v)) - 2  # 段长 L 的组最多能删 L-2 次
            if m > 0 and c == 'A':  # 长度至少 3 且颜色为 'A' 时，这些机会归 Alice
                a += m  # 累加 Alice 的次数
            elif m > 0 and c == 'B':  # 颜色为 'B' 时同理
                b += m  # 累加 Bob 的次数
        return a > b  # Alice 可删次数严格更多才必胜
