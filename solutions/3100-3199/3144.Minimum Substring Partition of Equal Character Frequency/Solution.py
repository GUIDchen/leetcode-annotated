# 题目：3144. 分割字符频率相等的最少子字符串（Minimum Substring Partition of Equal Character Frequency）
# 思路：@cache 记忆化搜索，dfs(i) 表示后缀 s[i:] 的最少分段数；枚举右端点 j，用 cnt 记字符次数、freq 记「次数 → 字符种类数」，freq 只剩一种次数时当前子串合法、可以切分。
# 时间复杂度：O(n^2)，每个状态枚举右端点；空间复杂度：O(n)，缓存表与递归栈开销。
class Solution:  # LeetCode 约定的题解类
    def minimumSubstringsInPartition(self, s: str) -> int:  # s：待分割的字符串
        @cache  # @cache：自动记忆化，同一个 i 只计算一次
        def dfs(i: int) -> int:  # dfs(i)：后缀 s[i:] 的最少分段数
            if i >= n:  # 越过末尾，没有字符需要分段
                return 0  # 空后缀需要 0 段
            cnt = defaultdict(int)  # cnt：各字符在当前子串中出现的次数
            freq = defaultdict(int)  # freq[c]：出现次数恰为 c 的字符种类数
            ans = n - i  # 先取上界：最坏情况一个字符一段，共 n - i 段
            for j in range(i, n):  # 枚举子串右端点 j
                if cnt[s[j]]:  # 该字符此前出现过，需要把它从旧次数桶里移走
                    freq[cnt[s[j]]] -= 1  # 旧次数桶的字符种类数减一
                    if not freq[cnt[s[j]]]:  # 这个桶已经空了
                        freq.pop(cnt[s[j]])  # 删除空桶，保证 len(freq) 只统计真实存在的次数
                cnt[s[j]] += 1  # 该字符出现次数加一
                freq[cnt[s[j]]] += 1  # 挂到新的次数桶上
                if len(freq) == 1 and (t := 1 + dfs(j + 1)) < ans:  # 只剩一种出现次数，且切一刀后的总段数更优
                    ans = t  # 更新当前最优值
            return ans  # 返回后缀 s[i:] 的最少分段数

        n = len(s)  # n：字符串长度（dfs 定义之后再赋值，调用时已就绪）
        return dfs(0)  # 从下标 0 开始求整个字符串的最少分段数
