# 题目：2565. 最少得分子序列（Subsequence With the Minimum Score）
# 思路：先正/反向贪心预处理出 t 每个位置在 s 中最早、最晚能匹配的下标；再用二分找「被删除的那段 t 的最小长度」，利用二分左边界定位第一个可行长度。
# 时间复杂度：O((m + n) log n)，m、n 分别为 s、t 的长度；空间复杂度：O(n)，两个长度为 n 的辅助数组。
class Solution:  # LeetCode 约定的题解类
    def minimumScore(self, s: str, t: str) -> int:  # s 是长串，t 要删掉最少字符后才成为 s 的子序列
        def check(x):  # 判断：是否存在长度为 x 的 t 子串，删掉它后「剩余前缀 + 剩余后缀」仍是 s 的子序列
            for k in range(n):  # 枚举被删子串的起点 k，即删除 t[k .. k+x-1]
                i, j = k - 1, k + x  # i：左侧保留前缀的末位下标；j：右侧保留后缀的首位下标
                l = f[i] if i >= 0 else -1  # 左前缀末位在 s 中最早的匹配下标；前缀为空时取 -1，视作位于 s 开头之前
                r = g[j] if j < n else m + 1  # 右后缀首位在 s 中最晚的匹配下标；后缀为空时取 m+1，视作位于 s 末尾之后
                if l < r:  # 左侧匹配位置严格早于右侧，说明前后缀能同时嵌入 s 且中间留有空隙
                    return True  # 该长度可行，立即返回
            return False  # 所有起点都不可行，说明 x 还不够大

        m, n = len(s), len(t)  # m：s 的长度；n：t 的长度（闭包 check 在执行时才读取它们）
        f = [inf] * n  # f[j]：正向扫描时 t[j] 最早能匹配到 s 的下标（匹配不到就保留正无穷大）
        g = [-1] * n  # g[j]：反向扫描时 t[j] 最晚能匹配到 s 的下标（匹配不到就是 -1）
        i, j = 0, 0  # 正向双指针：i 扫 s，j 扫 t
        while i < m and j < n:  # 只要两个串都没扫完就继续
            if s[i] == t[j]:  # 字符相同，说明 t[j] 可以落在 s 的位置 i 上
                f[j] = i  # 记录 t[j] 最早的匹配位置
                j += 1  # t 前进一位，因为子序列必须保持相对顺序
            i += 1  # 无论是否匹配成功，s 都要继续往后扫
        i, j = m - 1, n - 1  # 反向双指针：从两个串的末尾开始
        while i >= 0 and j >= 0:  # 两个串都还没扫到开头之前
            if s[i] == t[j]:  # 从后往前遇到相同字符
                g[j] = i  # 记录 t[j] 最晚的匹配位置
                j -= 1  # t 向左移动一位
            i -= 1  # 无论是否匹配成功，s 都要继续往前扫

        return bisect_left(range(n + 1), True, key=check)  # 在 [0, 1, ..., n] 上按 key=check 做二分，返回第一个让 check 为真的最小值，即最少得分
