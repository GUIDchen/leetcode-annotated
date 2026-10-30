# 题目：76. 最小覆盖子串（Minimum Window Substring）
# 思路：滑动窗口 + 计数器。右指针把字符纳入窗口，当窗口已覆盖 t 的全部字符时收缩左指针，边收缩边更新最短窗口。
# 时间复杂度：O(m + n)，左右指针各最多移动 m 次、为 t 建计数器需要 n 次；空间复杂度：O(Σ)，两份计数器的大小取决于字符集。
class Solution:  # LeetCode 约定的题解类
    def minWindow(self, s: str, t: str) -> str:  # s 是长串，t 是需要被完整覆盖的目标子串
        need = Counter(t)  # need 记录 t 中每个字符的需求次数
        window = Counter()  # window 记录当前窗口内每个字符实际出现的次数
        cnt = l = 0  # cnt 是窗口内已满足需求的字符个数，l 是窗口左边界
        k, mi = -1, inf  # k 记录最短窗口起点，mi 记录最短窗口长度；inf 作为初值表示还没找到可行窗口
        for r, c in enumerate(s):  # 右指针 r 从左到右扩张窗口，c 是本轮新纳入窗口的字符
            window[c] += 1  # 把字符 c 的窗口计数加一
            if need[c] >= window[c]:  # 加入后仍不超过需求量，说明这次纳入是「有效贡献」
                cnt += 1  # 有效字符数加一
            while cnt == len(t):  # 窗口已覆盖 t 的所有字符，于是尝试收缩左边界找更短的解
                if r - l + 1 < mi:  # 当前窗口长度 r-l+1 比已知最短窗口更短
                    mi = r - l + 1  # 更新最短长度
                    k = l  # 同时记下这个最短窗口的起点
                if need[s[l]] >= window[s[l]]:  # 判断即将移出的左端字符是否是有效贡献
                    cnt -= 1  # 是的话有效字符数减一，窗口可能不再覆盖 t，从而退出 while
                window[s[l]] -= 1  # 把该字符从窗口计数中减去
                l += 1  # 左边界右移，完成一次收缩
        return "" if k < 0 else s[k : k + mi]  # k<0 表示没有可行窗口就返回空串，否则用切片取出最短窗口
