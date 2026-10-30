# 题目：3333. 找到初始输入字符串 II（Find the Original Typed String II）
# 思路：先把字符串按连续相同字符合并成若干段，各段长度的乘积是总方案数；段数不足 k 时，再用前缀和优化的 DP 统计“长度小于 k”的非法方案，用总数减掉。
# 时间复杂度：O(n + m·k)，m 为段数；空间复杂度：O(m·k)。
class Solution:  # LeetCode 约定的题解类
    def possibleStringCount(self, word: str, k: int) -> int:  # word 是最终输入串，k 是初始串长度的下界
        mod = 10**9 + 7  # 取模常量
        nums = []  # nums 保存每段“最多能少写”的字符数（段长减一）
        ans = 1  # ans 先记录不考虑长度下界时的总方案数
        cur = 0  # 当前连续段的长度
        for i, c in enumerate(word):  # 逐字符扫描，切分连续相同字符的段
            cur += 1  # 当前段长度加一
            if i == len(word) - 1 or c != word[i + 1]:  # 到达串尾或字符改变，说明一段结束
                if cur > 1:  # 段长大于 1 才有可删的多余字符
                    if k > 0:  # 仍受长度下界约束时才记录该段余量
                        nums.append(cur - 1)  # 该段最多可以少写 cur-1 个字符
                    ans = ans * cur % mod  # 该段有 cur 种可能的原始长度，累乘进总方案数
                cur = 0  # 重置计数，准备统计下一段
                k -= 1  # 每结束一段 k 减一，扫描完后 k 是“下界减去段数”
        if k < 1:  # k < 1 表示段数已不少于下界，所有方案都合法
            return ans  # 直接返回总方案数
        m = len(nums)  # 段数
        f = [[0] * k for _ in range(m + 1)]  # f[i][j]：前 i 段只产生 j 个字符（j < k）的方案数，即非法方案
        f[0][0] = 1  # 空前缀产生 0 个字符，方案数为 1
        for i, x in enumerate(nums, 1):  # 逐段递推
            s = list(accumulate(f[i - 1], initial=0))  # accumulate 求前缀和，initial=0 让 s[j] 表示前 j 项之和
            for j in range(k):  # 枚举前 i 段产生的总字符数 j
                f[i][j] = (s[j + 1] - s[j - min(x, j)] + mod) % mod  # 前缀和区间求和：第 i 段最多少写 x 个字符
        return (ans - sum(f[m][j] for j in range(k))) % mod  # 总方案数减去非法方案即为答案
