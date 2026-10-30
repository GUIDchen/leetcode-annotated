# 题目：1510. 石子游戏 IV（Stone Game IV）
# 思路：记忆化搜索 + 博弈论：只要存在平方数 j² 让对手在 i-j² 局面必败，当前局面就必胜。
# 时间复杂度：O(n·√n)，每个状态枚举 √i 个平方数；空间复杂度：O(n)，缓存表与递归栈。
@cache  # cache 装饰器把 (i) → 返回值缓存下来，实现记忆化搜索
def dfs(i: int) -> bool:  # i：剩余石子数；返回当前先手是否必胜
    if i <= 0:  # 没有石子可取，当前玩家无法行动
        return False  # 无法行动即必败
    k = isqrt(i)  # k：不超过 i 的最大平方数根，即可取的 j 的上界
    return any(not dfs(i - j * j) for j in range(1, k + 1))  # 任意一种取法让对手在 i - j*j 必败，当前玩家就必胜（any 短路求值）


class Solution:  # LeetCode 约定的题解类
    def winnerSquareGame(self, n: int) -> bool:  # n：石子总数，返回先手是否有必胜策略
        return dfs(n)  # 调用记忆化搜索得到初始局面的结果
