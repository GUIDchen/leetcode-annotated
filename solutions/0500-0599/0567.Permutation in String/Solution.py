# 题目：567. 字符串的排列（Permutation in String）
# 思路：滑动窗口加计数欠账：cnt 是窗口内各字符相对 s1 的差值，need 是尚未对齐的字符种类数；窗口长度保持 |s1|，need 归零即命中。
# 时间复杂度：O(|s2|)，窗口线性滑动；空间复杂度：O(1)，只用到 26 个字母的计数。
class Solution:  # LeetCode 约定的题解类
    def checkInclusion(self, s1: str, s2: str) -> bool:  # s1 是模式串，判断 s2 是否含有它的某个排列作为连续子串
        cnt = Counter(s1)  # 统计 s1 的字符计数；Counter 缺失的键按 0 处理，后续可安全增减
        need = len(cnt)  # need 记录还有多少种字符的计数没有归零
        m = len(s1)  # m 是目标窗口长度，等于 len(s1)
        for i, c in enumerate(s2):  # 右端点 i 从左到右滑动，c 是进入窗口的字符
            cnt[c] -= 1  # 新字符进入窗口：计数向 0 靠拢（可能变负，表示窗口内该字符超出需求）
            if cnt[c] == 0:  # 减到 0 说明这种字符刚好对齐
                need -= 1  # 欠账种类数减一
            if i >= m:  # 窗口超过 m 时，需要把最左侧字符移出
                cnt[s2[i - m]] += 1  # 移出字符的计数加回 1
                if cnt[s2[i - m]] == 1:  # 从 0 变成 1 说明这种字符重新欠账
                    need += 1  # 欠账种类数加一
            if need == 0:  # 所有字符计数都归零，说明找到一个排列
                return True  # 返回 True
        return False  # 遍历完 s2 也没找到，返回 False
