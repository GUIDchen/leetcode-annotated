# 题目：3003. 执行操作后的最大分割数量（Maximize the Number of Partitions After Operations）
# 思路：记忆化 DFS + 26 位掩码。cur 是当前段出现过的字母集合，t 表示还有没有一次改字母的机会；从左到右尽量延长当前段，超限就切段。
# 时间复杂度：记忆化后为 O(访问到的状态数)，最坏 O(n × 2^26)；空间复杂度：O(访问到的状态数)，缓存与递归栈。
class Solution:  # LeetCode 约定的题解类
    def maxPartitionsAfterOperations(self, s: str, k: int) -> int:  # s：输入字符串；k：每个分段允许包含的不同字母数上限；返回划分出的最大段数
        @cache  # 记忆化：相同的 (i, cur, t) 只计算一次
        def dfs(i: int, cur: int, t: int) -> int:  # 递归函数：i 为当前下标，cur 为当前段的字母掩码，t 表示是否还能修改一次字母
            if i >= n:  # 已经走到字符串末尾
                return 1  # 最后一段也要计入段数
            v = 1 << (ord(s[i]) - ord("a"))  # 当前字符对应的比特位
            nxt = cur | v  # 把当前字符并入当前段的字母集合
            if nxt.bit_count() > k:  # 不修改时字母种类超过 k，必须在此切段
                ans = dfs(i + 1, v, t) + 1  # 新段只含当前字符，段数加一
            else:  # 否则仍然合规，继续延长当前段
                ans = dfs(i + 1, nxt, t)  # 把当前字符并入后继续往下走，段数不变
            if t:  # 还有修改机会，枚举把 s[i] 换成哪个字母
                for j in range(26):  # 逐个尝试 26 个字母
                    nxt = cur | (1 << j)  # 替换后当前段的字母集合
                    if nxt.bit_count() > k:  # 替换后字母种类超过 k，被迫切段
                        ans = max(ans, dfs(i + 1, 1 << j, 0) + 1)  # 用掉修改机会，新段只含替换后的字母，段数加一
                    else:  # 否则替换后仍在 k 种以内
                        ans = max(ans, dfs(i + 1, nxt, 0))  # 用掉修改机会，继续延长当前段，不增加段数
            return ans  # 返回该状态能得到的最大段数

        n = len(s)  # 字符串长度，供 dfs 内部做边界判断（闭包引用）
        return dfs(0, 0, 1)  # 从下标 0、空掩码、还有一次修改机会开始搜索
