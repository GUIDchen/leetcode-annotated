# 题目：3365. 重排子字符串以形成目标字符串（Rearrange K Substrings to Form Target String）
# 思路：把 s 与 t 各切成 k 段等长子串，用计数器做「s 段 +1、t 段 -1」的差分，计数全为 0 即可重排成功。
# 时间复杂度：O(n) 期望，切段与计数合计线性；空间复杂度：O(k)，最多保存 k 个不同子串。
class Solution:  # LeetCode 约定的题解类
    def isPossibleToRearrange(self, s: str, t: str, k: int) -> bool:  # s：原串；t：目标串；k：要求切成的段数
        cnt = Counter()  # 计数器：统计每种等长子串在 s 与 t 中出现次数的差
        n = len(s)  # 字符串长度
        m = n // k  # 每段长度，题目保证 n 能被 k 整除
        for i in range(0, n, m):  # 从下标 0 开始按步长 m 依次切出 k 段
            cnt[s[i : i + m]] += 1  # s 的当前段计数 +1
            cnt[t[i : i + m]] -= 1  # t 的当前段计数 -1，两边抵消后只需看差值
        return all(v == 0 for v in cnt.values())  # 所有段的差值都是 0，才说明能重排成目标串
