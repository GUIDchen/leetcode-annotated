# 题目：131. 分割回文串（Palindrome Partitioning）
# 思路：区间 DP 预处理 f[i][j] 表示 s[i..j] 是否回文，再用 DFS 回溯枚举所有切分方式，只沿回文区间扩展。
# 时间复杂度：O(n * 2^n)，预处理 O(n^2)、答案数量本身是指数级；空间复杂度：O(n^2)，回文表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def partition(self, s: str) -> List[List[str]]:  # 返回所有能切成回文子串的方案
        def dfs(i: int):  # 回溯函数：i 是当前还没切分的后缀起点
            if i == n:  # 切到末尾，说明当前方案已经完整
                ans.append(t[:])  # 拷贝一份 t（用切片复制）放进答案，避免后续回溯改到它
                return  # 结束本条分支
            for j in range(i, n):  # 枚举下一段的结束位置 j
                if f[i][j]:  # 只有 s[i..j] 是回文才继续往下切
                    t.append(s[i : j + 1])  # 把当前回文段加入方案
                    dfs(j + 1)  # 从 j 的下一位继续切后缀
                    t.pop()  # 回溯：撤销本段的加入，尝试下一个 j

        n = len(s)  # n 是字符串长度
        f = [[True] * n for _ in range(n)]  # 回文判定表，先全部初始化为 True（长度 0、1 的区间天然回文）
        for i in range(n - 1, -1, -1):  # i 从后往前，保证递推用到的 f[i+1][j-1] 已经算好
            for j in range(i + 1, n):  # j 从 i+1 开始，短区间已在初值里
                f[i][j] = s[i] == s[j] and f[i + 1][j - 1]  # 首尾字符相同且去掉首尾后仍回文，则 s[i..j] 回文
        ans = []  # 收集所有完整方案
        t = []  # 回溯用的当前方案
        dfs(0)  # 从下标 0 开始搜索（此时 f、ans、t 都已就绪，闭包按调用时的名字取用）
        return ans  # 返回全部方案
