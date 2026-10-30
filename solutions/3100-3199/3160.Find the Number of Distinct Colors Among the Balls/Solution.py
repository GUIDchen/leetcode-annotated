# 题目：3160. 所有球里面不同颜色的数目（Find the Number of Distinct Colors Among the Balls）
# 核心思路：g 记录「球 → 当前颜色」，cnt 记录「颜色 → 该颜色的球数」；改色时先增减计数，再用 len(cnt) 直接读出不同颜色数。
# 时间复杂度：O(m)，m 为操作数，字典操作均摊 O(1)；空间复杂度：O(m)，最坏存 m 个球与颜色。
class Solution:  # LeetCode 约定的题解类
    def queryResults(self, limit: int, queries: List[List[int]]) -> List[int]:  # limit：球编号上界（本题用不到）；queries：涂色操作序列
        g = {}  # 球编号 → 当前颜色
        cnt = Counter()  # 颜色 → 拥有该颜色的球的数量，用 Counter 省去初始化
        ans = []  # 每次操作后的不同颜色数
        for x, y in queries:  # 逐条处理涂色操作，同时取出球编号与颜色
            cnt[y] += 1  # 新颜色的球数加一
            if x in g:  # 该球之前被涂过色，需要先扣掉旧颜色
                cnt[g[x]] -= 1  # 旧颜色的球数减一
                if cnt[g[x]] == 0:  # 旧颜色已经没有任何球
                    cnt.pop(g[x])  # 把它从 Counter 中删掉，保证 len 统计正确
            g[x] = y  # 更新该球的当前颜色
            ans.append(len(cnt))  # Counter 的键个数就是当前不同颜色数
        return ans  # 返回每次操作后的不同颜色数
