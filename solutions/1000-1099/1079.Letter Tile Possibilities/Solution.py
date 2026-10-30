# 题目：1079. 活字印刷（Letter Tile Possibilities）
# 思路：用计数器统计每种字母的张数，然后做回溯 DFS：每层任选一个仍有剩余的字母接到当前序列后面，选完立刻计数，再递归、回溯恢复计数，靠固定的遍历顺序天然去重。
# 时间复杂度：O(n * n!)，n 为字母个数，最坏要枚举所有排列；空间复杂度：O(n)，递归深度不超过 n。
class Solution:  # LeetCode 约定的题解类
    def numTilePossibilities(self, tiles: str) -> int:  # tiles 是可用的字母集合（每个字符是一张字牌）
        def dfs(cnt: Counter) -> int:  # 递归函数：返回从当前剩余字母出发还能组成多少个不同的非空序列
            ans = 0  # 记录本轮能产生的序列个数
            for i, x in cnt.items():  # 遍历每种字母及其剩余张数（遍历中只改值不增删键，因此安全）
                if x > 0:  # 该字母还有剩余字牌才可以选择
                    ans += 1  # 选它构成一个长度 +1 的新序列，先计数
                    cnt[i] -= 1  # 用掉一张该字母的字牌
                    ans += dfs(cnt)  # 递归统计在这个前缀之后继续接字母得到的所有序列
                    cnt[i] += 1  # 回溯：恢复这张字牌，供其他分支使用
            return ans  # 返回本轮统计到的序列总数

        cnt = Counter(tiles)  # 统计每种字母出现的张数
        return dfs(cnt)  # 从空序列开始搜索，答案即所有非空序列的个数
