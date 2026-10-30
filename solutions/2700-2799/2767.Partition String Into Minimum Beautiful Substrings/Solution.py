# 题目：2767. 将字符串分割为最少的美丽子字符串（Partition String Into Minimum Beautiful Substrings）
# 思路：先把 5 的幂（二进制形如 1 后跟若干 0）预处理进集合 ss，再用 @cache 记忆化 DFS 从下标 i 往后枚举所有「美丽子串」，取最少段数。
# 时间复杂度：O(n^2)，n 个状态、每个状态枚举 O(n) 个右端点；空间复杂度：O(n)，缓存与递归栈的开销。
class Solution:  # LeetCode 约定的题解类
    def minimumBeautifulSubstrings(self, s: str) -> int:  # s 是只含 '0'/'1' 的二进制字符串，返回最少分割段数
        @cache  # 缓存 dfs 的结果，同一状态只计算一次（等价于记忆化搜索）
        def dfs(i: int) -> int:  # dfs(i)：从下标 i 开始把剩余后缀切完所需的最少段数
            if i >= n:  # 已经切到末尾，没有字符需要处理
                return 0  # 剩余后缀需要 0 段
            if s[i] == "0":  # 美丽数的二进制首位一定是 1，以 '0' 开头的子串不可能可行
                return inf  # 用无穷大作为「不可行」的哨兵值
            x = 0  # 滚动还原 s[i..j] 的二进制数值，初值为空串的 0
            ans = inf  # 段数最多为 n 段，用 inf 表示当前还没有找到可行方案
            for j in range(i, n):  # 枚举当前这一段的右端点 j
                x = x << 1 | int(s[j])  # 左移一位并拼上当前位，得到 s[i..j] 的数值
                if x in ss:  # 这一段的值是 5 的幂，即它本身就是美丽子串
                    ans = min(ans, 1 + dfs(j + 1))  # 1 段加上切完后缀的最优段数，取最小值
            return ans  # 返回从 i 开始的最少段数（仍可能是 inf）

        # 预处理阶段：5 的幂的二进制形如 1 后跟若干 0，最多只需覆盖 n 位长度
        n = len(s)
        x = 1  # 从 5^0 = 1 开始枚举 5 的幂
        ss = {x}  # 集合里先放入 5^0
        for i in range(n):  # 子串最长 n 位，只需要再补 n 个 5 的幂
            x *= 5  # 递推下一个 5 的幂
            ss.add(x)  # 加入集合，供 dfs 判断子串是否美丽
        ans = dfs(0)  # 从下标 0 开始切整个字符串
        return -1 if ans == inf else ans  # 结果仍是 inf 说明无解，按题目要求返回 -1
