# 题目：1639. 通过给定词典构造目标字符串的方案数（Number of Ways to Form a Target String Given a Dictionary）
# 思路：预处理每一列各字母的出现次数，再按目标串位置做记忆化 DFS：跳过该列，或用该列匹配下一个目标字符。
# 时间复杂度：O(m·n·26)，预处理计数与 m×n 个状态的转移；空间复杂度：O(m·n + n·26)，缓存与列计数表。
class Solution:  # LeetCode 约定的题解类
    def numWays(self, words: List[str], target: str) -> int:  # words 是长度相同的词典，target 是目标串，返回构造方案数
        @cache  # @cache 装饰器：把 dfs(i, j) 的结果缓存起来，实现记忆化搜索
        def dfs(i: int, j: int) -> int:  # 递归函数：i 是目标串进度，j 是当前列下标
            if i >= m:  # 目标串已经全部匹配完成，这是一种合法方案
                return 1  # 返回 1 累加方案数
            if j >= n:  # 列已经用完但目标串还没匹配完，该分支无解
                return 0  # 返回 0 表示此路不通
            ans = dfs(i + 1, j + 1) * cnt[j][ord(target[i]) - ord('a')]  # 方案一：用第 j 列的字母匹配 target[i]，方案数乘以该列上该字母的出现次数
            ans = (ans + dfs(i, j + 1)) % mod  # 方案二：跳过第 j 列，把两部分方案数相加后取模
            return ans  # 返回该状态的方案数（同时被 @cache 记录）

        m, n = len(target), len(words[0])  # m 是目标串长度，n 是词典中单词长度（也是可用列数）
        cnt = [[0] * 26 for _ in range(n)]  # cnt[j][c]：第 j 列上字母 c 出现的次数（26 个字母表）
        for w in words:  # 遍历词典里的每个单词
            for j, c in enumerate(w):  # 遍历该单词的每一列（j 为列号，c 为该列字符）
                cnt[j][ord(c) - ord('a')] += 1  # 第 j 列上字母 c 的计数加一（ord 差值映射到 0~25）
        mod = 10**9 + 7  # 模数 1e9+7，防止计数溢出
        return dfs(0, 0)  # 从「目标串下标 0、第 0 列」开始求解
