# 题目：3518. 最小回文排列 II（Smallest Palindromic Rearrangement II）
# 思路：回文由左半部分唯一决定，故在左半部分逐位贪心：按字母序尝试每一位，用多重集排列数判断第 k 小落在哪个分支。
# 时间复杂度：O(|Σ| * n * |Σ|)，排列数带截断；空间复杂度：O(n + |Σ|)。
class Solution:  # LeetCode 约定的题解类
    def smallestPalindrome(self, s: str, k: int) -> str:  # s：输入字符串；k：字典序序号；返回第 k 小的回文排列，不存在返回空串
        limit = 1_000_001  # limit：排列数上限，超过即视为「足够大」
        freq = [0] * 26  # freq[x]：字母 x 的出现次数
        for ch in s:  # 遍历字符串的每个字符
            freq[ord(ch) - 97] += 1  # 对应字母的计数加一
        odd = 0  # odd：出现奇数次的字母个数
        mid = 26  # mid：中心字母下标，26 表示没有
        for i, v in enumerate(freq):  # 扫描 26 个字母并同时取下标
            if v & 1:  # 该字母出现奇数次
                odd += 1  # 奇数次字母数加一
                mid = i  # 记录中心字母
        if odd > 1:  # 超过一个奇数次字母就无法构成回文
            return ""  # 不存在回文排列，返回空串
        half = [v // 2 for v in freq]  # half[x]：左半部分中字母 x 的个数
        half_len = sum(half)  # halfLen：左半部分的长度

        def count_permutations(counts: List[int]) -> int:  # counts：多重集各字母的个数；返回不同排列数，超过上限时截断
            remaining = sum(counts)  # remaining：剩余待安排的字符总数
            perms = 1  # perms：排列数
            for count in counts:  # 逐个字母用组合数相乘
                if count == 0:  # 该字母没有出现
                    continue  # 跳过
                selected = min(count, remaining - count)  # 取较小的一边算组合数，减少循环次数
                combos = 1  # combos：组合数 C(remaining, selected)
                for step in range(1, selected + 1):  # 逐项累乘组合数
                    combos = combos * (remaining - step + 1) // step  # 乘一项除一项，保证中间结果始终是整数
                    if combos >= limit:  # 已经达到上限
                        combos = limit  # 截断到上限，避免溢出
                        break  # 提前结束累乘
                perms *= combos  # 乘上当前字母的组合数
                if perms >= limit:  # 排列数超过上限
                    return limit  # 直接返回上限，后续比较仍然成立
                remaining -= count  # 该字母安排完毕，剩余数量减少
            return perms  # 返回排列数，不超过 limit

        if k > count_permutations(half):  # 左半部分的不同排列数不足 k 个
            return ""  # 说明整体也没有 k 个回文排列，返回空串
        n = len(s)  # n：字符串长度
        pal = [""] * n  # pal：结果回文，逐字符填充
        rank = k  # rank：当前还在找第几小
        pos = 0  # pos：左半部分的写入位置
        for _ in range(half_len):  # 逐位确定左半部分的每个字符
            for i in range(26):  # 按字母序尝试，保证字典序最小
                if half[i] == 0:  # 该字母已经用完
                    continue  # 换下一个字母
                half[i] -= 1  # 假设这一位放字母 i
                suffix = count_permutations(half)  # 固定这一位后，剩余位置能形成的排列数
                if suffix >= rank:  # 第 k 小就落在这一分支里
                    pal[pos] = chr(97 + i)  # 确定这一位，写入对应字母
                    pos += 1  # 写入位置后移
                    break  # 跳出字母尝试
                rank -= suffix  # 否则跳过整个分支，排名向前扣减
                half[i] += 1  # 恢复计数，尝试下一个字母
        if mid < 26:  # 存在中心字母
            pal[half_len] = chr(97 + mid)  # 把中心字母放到正中间
        for i in range(half_len):  # 用左半部分镜像填充右半部分
            pal[n - 1 - i] = pal[i]  # 对称位置赋值，保证整体回文
        return "".join(pal)  # 返回第 k 小的回文排列
