# 题目：294. 翻转游戏 II（Flip Game II）🔒
# 思路：把 '+'/'-' 的局面压缩成位掩码，用记忆化博弈搜索：只要存在一步让对手必败，当前局面就是必胜态。
# 时间复杂度：O(2^n · n)，共 2^n 个局面、每局面枚举 n 个位置；空间复杂度：O(2^n)，记忆化缓存。
class Solution:  # LeetCode 约定的题解类
    def canWin(self, currentState: str) -> bool:  # currentState：由 '+' / '-' 组成的当前局面
        @cache  # functools.cache 自动记忆化，避免同一掩码被重复搜索
        def dfs(mask):  # mask：当前局面；返回当前行动方是否必胜
            for i in range(n - 1):  # 枚举所有可能被翻转的「++」的起始位置
                if (mask & (1 << i)) == 0 or (mask & (1 << (i + 1)) == 0):  # 第 i、i+1 位不同时为 1，说明这里不是「++」
                    continue  # 该位置不可翻转，换下一个起点
                if dfs(mask ^ (1 << i) ^ (1 << (i + 1))):  # 翻转这两位模拟落子；若对手在新局面下仍然必胜，则这一步不可行
                    continue  # 换下一个起点继续尝试
                return True  # 存在一步让对手必败，当前局面必胜
            return False  # 所有走法都不行（或已无「++」可翻），当前局面必败

        mask, n = 0, len(currentState)  # 掩码初始为 0；n 记录字符串长度供闭包使用
        for i, c in enumerate(currentState):  # 逐字符扫描
            if c == '+':  # 只关心 '+' 的位置
                mask |= 1 << i  # 把第 i 位置 1，字符串局面转成二进制掩码
        return dfs(mask)  # 从初始掩码开始判断先手是否必胜
