# 3455. 最短匹配子字符串 / Shortest Matching Substring
# 核心思路：用 KMP 分别求出三段模式串在 s 中所有出现位置，再用两个指针做单调递增的贪心匹配，取最短的覆盖区间。
# 复杂度：时间复杂度 O(|s| + |p|)，空间复杂度 O(|s|)。
class Solution:  # 题解类
    def shortestMatchingSubstring(self, s: str, p: str) -> int:  # 求 s 中最短的匹配 p 的子串长度
        def starts(pat: str):  # 用 KMP 求 pat 在 s 中所有出现的起始下标
            if not pat:  # 空模式串可以匹配任意位置
                return list(range(len(s) + 1))  # 共 len(s)+1 个可匹配位置
            m = len(pat)  # 模式串长度
            lps = [0] * m  # KMP 的最长公共前后缀数组
            length = 0  # 当前已匹配的公共前后缀长度
            i = 1  # 从第二位开始递推
            while i < m:  # 递推计算 lps
                if pat[i] == pat[length]:  # 字符相同，前后缀可以同时延长
                    length += 1  # 公共前后缀长度加一
                    lps[i] = length  # 记录到 lps[i]
                    i += 1  # 前进一位
                elif length:  # 失配时回退到更短的公共前后缀
                    length = lps[length - 1]  # 用已知结果回退，i 不动
                else:  # 已无更短前缀可回退
                    i += 1  # 当前位 lps 为 0，直接前进
            res = []  # 保存所有匹配起点
            i = j = 0  # 主串指针与模式串指针
            n = len(s)  # 主串长度
            while i < n:  # 在主串上扫描
                if s[i] == pat[j]:  # 当前字符匹配
                    i += 1  # 主串指针右移
                    j += 1  # 模式串指针右移
                    if j == m:  # 整个模式串匹配成功
                        res.append(i - m)  # 起点为 i-m
                        j = lps[j - 1]  # 利用 lps 继续寻找重叠的下一处匹配
                elif j:  # 失配但还有已匹配前缀
                    j = lps[j - 1]  # 回退模式串指针，主串指针不动
                else:  # 失配且没有任何已匹配前缀
                    i += 1  # 主串指针右移
            return res  # 返回所有匹配起点

        a, b, c = p.split('*')  # 按两个 '*' 把模式串拆成三段
        A, B, C = starts(a), starts(b), starts(c)  # 三段的全部出现位置，均升序
        la, lb, lc = len(a), len(b), len(c)  # 三段的长度
        ans = len(s) + 1  # 答案初值取一个不可能达到的长度
        j = k = 0  # j、k 分别指向 B、C 中待考察的位置，随 i 增大单调右移
        for i in A:  # 枚举第一段的每一个出现位置
            while j < len(B) and B[j] < i + la:  # 第二段必须严格排在 a 之后
                j += 1  # 不满足就继续右移
            if j == len(B):  # 第二段已经没有可用的位置
                break  # 后面的 i 更大，更不可能匹配，直接结束
            while k < len(C) and C[k] < B[j] + lb:  # 第三段必须严格排在 b 之后
                k += 1  # 不满足就继续右移
            if k == len(C):  # 第三段已经没有可用的位置
                break  # 后面的 i 更大，更不可能匹配，直接结束
            ans = min(ans, C[k] + lc - i)  # 区间右端减左端，得到当前匹配长度
        return -1 if ans > len(s) else ans  # 没有找到合法匹配则返回 -1
