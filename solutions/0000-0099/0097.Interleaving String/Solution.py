# 题目：97. 交错字符串（Interleaving String）
# 思路：记忆化搜索，dfs(i, j) 表示 s1 的前 i 个与 s2 的前 j 个字符能否交错拼出 s3 的前 i+j 个；
#       当前应匹配 s3[i+j]，可取自 s1[i] 或 s2[j]，两条路都走不通则返回 False。
# 时间复杂度：O(m·n)，每个状态只求解一次；空间复杂度：O(m·n)，缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:  # 判断 s3 能否由 s1、s2 交错拼接而成
        @cache  # 自动记忆化：相同 (i, j) 的结果只计算一次
        def dfs(i: int, j: int) -> bool:  # i、j 分别是 s1、s2 已用掉的字符数
            if i >= m and j >= n:  # 两个串都用完，说明 s3 也恰好被拼完
                return True  # 找到一条合法交错路径
            k = i + j  # 当前要对齐的是 s3 的第 k 个字符
            if i < m and s1[i] == s3[k] and dfs(i + 1, j):  # 方案一：让 s3[k] 取自 s1[i]，且余下部分也能拼成
                return True  # 有一条路成功即可提前返回
            if j < n and s2[j] == s3[k] and dfs(i, j + 1):  # 方案二：改让 s3[k] 取自 s2[j]
                return True  # 这条分支成功
            return False  # 两条路都走不通，该状态失败

        m, n = len(s1), len(s2)  # 两个串的长度，dfs 运行时从这里读取（闭包延迟绑定）
        if m + n != len(s3):  # 长度都对不上，绝无可能交错拼成
            return False  # 直接否决
        return dfs(0, 0)  # 从两个串都没用任何字符开始搜索
