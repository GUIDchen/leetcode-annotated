# 题目：291. 单词规律 II（Word Pattern II）—— pattern 每个字符要对应 s 的一个非空子串且为双射，判断是否存在这种切分。
# 核心思路：回溯 DFS。按 pattern 字符顺序枚举切分长度，用 d（字符→串）与 vis（已用过的串）保证双射，失败立即回退。
# 时间复杂度：最坏指数级（每层多种切分，靠长度剪枝削减）；空间复杂度：O(m + n)，递归栈加两个哈希容器。
class Solution:  # LeetCode 约定的题解类
    def wordPatternMatch(self, pattern: str, s: str) -> bool:  # pattern：规律串；s：等待切分的字符串
        def dfs(i, j):  # i：pattern 下标；j：s 下标；返回从这两个位置开始能否匹配
            if i == m and j == n:  # 两边同时用完，说明找到了一组合法映射
                return True  # 返回成功
            if i == m or j == n or n - j < m - i:  # 一方提前用完，或剩余长度不足以给每个剩余字符至少分 1 个字符 → 剪枝
                return False  # 返回失败
            for k in range(j, n):  # 枚举子串右端点 k，对应子串 s[j : k+1]（保证非空）
                t = s[j : k + 1]  # 当前尝试的子串
                if d.get(pattern[i]) == t:  # 该字符已映射且正好等于 t：沿用旧映射
                    if dfs(i + 1, k + 1):  # 递归匹配剩余部分
                        return True  # 成功即整体成功
                if pattern[i] not in d and t not in vis:  # 字符未映射且子串未被占用 → 可以建立新映射
                    d[pattern[i]] = t  # 记录正向映射
                    vis.add(t)  # 标记子串已被占用
                    if dfs(i + 1, k + 1):  # 递归尝试后续匹配
                        return True  # 成功即整体成功
                    d.pop(pattern[i])  # 回溯：撤销字符映射
                    vis.remove(t)  # 回溯：撤销子串占用
            return False  # 所有切分方式都失败

        m, n = len(pattern), len(s)  # 提前算好两个串长度，供闭包 dfs 直接使用
        d = {}  # pattern 字符 -> 子串
        vis = set()  # 已被占用的子串集合
        return dfs(0, 0)  # 从两个串的起点开始搜索
