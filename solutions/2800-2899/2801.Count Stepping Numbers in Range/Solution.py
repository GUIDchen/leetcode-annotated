# 题目：2801. 统计范围内的步进数字数目（Count Stepping Numbers in Range）
# 思路：数位 DP 记忆化搜索，先求不超过 high 的个数，再求不超过 low-1 的个数，两者相减即为区间答案。
# 时间复杂度：O(D * 10 * 10)，D 为 high 的位数；空间复杂度：O(D * 10)，即缓存的状态数。
class Solution:  # LeetCode 约定的题解类
    def countSteppingNumbers(self, low: str, high: str) -> int:  # low、high：闭区间的下界与上界（字符串形式）
        @cache  # 装饰器：按参数组合缓存 dfs 的结果，实现记忆化
        def dfs(pos: int, pre: int, lead: bool, limit: bool) -> int:  # pos：当前位；pre：上一位数字；lead：是否仍是前导零；limit：是否贴着上界
            if pos >= len(num):  # 所有数位都已经填完
                return int(not lead)  # 全是前导零代表数字 0，题目只统计正整数，故返回 0；否则返回 1
            up = int(num[pos]) if limit else 9  # 当前位的上限：贴紧上界时取上界该位的数字，否则可以取 0~9
            ans = 0  # ans：当前状态的方案数累加器
            for i in range(up + 1):  # 枚举当前位填入的数字 i
                if i == 0 and lead:  # 仍处于前导零阶段，填 0 不产生实际数值
                    ans += dfs(pos + 1, pre, True, limit and i == up)  # 继续保留前导零标记，上一位数字 pre 保持不变
                elif pre == -1 or abs(i - pre) == 1:  # 这是第一个非零数字，或与上一位相差恰好 1（满足步进条件）
                    ans += dfs(pos + 1, i, False, limit and i == up)  # 进入下一位，上一位更新为 i，并离开前导零状态
            return ans % mod  # 对 1e9+7 取模后返回当前状态的方案数

        mod = 10**9 + 7  # 取模常量（写在 dfs 之后，但调用时已绑定，闭包能正确读到）
        num = high  # num：当前统计的上界字符串，dfs 通过闭包读取它
        a = dfs(0, -1, True, True)  # 统计 [1, high] 内的步进数字个数
        dfs.cache_clear()  # 上界马上要换成 low-1，必须清空缓存，否则会复用旧上界的结果
        num = str(int(low) - 1)  # 用 Python 大整数把 low 减一再转回字符串，避免手写借位
        b = dfs(0, -1, True, True)  # 统计 [1, low-1] 内的步进数字个数
        return (a - b) % mod  # 前缀和相减得到 [low, high] 的答案；Python 取模结果天然非负
