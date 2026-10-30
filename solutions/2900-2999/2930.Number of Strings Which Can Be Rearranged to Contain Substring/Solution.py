# 题目：2930. 重新排列后包含指定子字符串的字符串数目（Number of Strings Which Can Be Rearranged to Contain Substring）
# 思路：只关心 l、e、t 各出现多少次。记忆化搜索枚举长度为 n 的字符串，状态 (i, l, e, t) 表示还剩 i 个位置、三种字符已出现次数（分别封顶 1、2、1），终态要求恰好 1 个 l、2 个 e、1 个 t。
# 时间复杂度：O(n * 2 * 3 * 2) = O(n)，状态数只有 12n 个；空间复杂度：O(n * 2 * 3 * 2) = O(n)，用于缓存。
class Solution:  # LeetCode 约定的题解类
    def stringCount(self, n: int) -> int:  # n 为字符串长度
        @cache
        def dfs(i: int, l: int, e: int, t: int) -> int:  # l、e、t 分别是三种字符已经出现的次数
            if i == 0:  # 位置已经填完
                return int(l == 1 and e == 2 and t == 1)  # 恰好 1 个 l、2 个 e、1 个 t 时为 1，否则为 0
            a = dfs(i - 1, l, e, t) * 23 % mod  # 放其余 23 个字母，三种计数都不变
            b = dfs(i - 1, min(1, l + 1), e, t)  # 放 l，次数封顶在 1，只关心是否出现过
            c = dfs(i - 1, l, min(2, e + 1), t)  # 放 e，次数封顶在 2，因为只需要 2 个
            d = dfs(i - 1, l, e, min(1, t + 1))  # 放 t，次数封顶在 1
            return (a + b + c + d) % mod  # 四种选择求和后取模

        mod = 10**9 + 7  # 答案要对 1e9+7 取模
        return dfs(n, 0, 0, 0)  # 从 n 个空位、三种字符都还没出现开始搜
