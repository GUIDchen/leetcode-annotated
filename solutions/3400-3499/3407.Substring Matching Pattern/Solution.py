# 3407. 子字符串匹配模式 / Substring Matching Pattern
# 核心思路：按 '*' 把模式串切分成若干片段，在 s 中从前往后贪心地依次查找这些片段。
# 复杂度：时间复杂度 O(n*m)，空间复杂度 O(m)，其中 n、m 分别为 s、p 的长度。
class Solution:  # 题解类定义
    def hasMatch(self, s: str, p: str) -> bool:  # 判断 s 能否匹配只含至多一个 '*' 的模式 p
        i = 0  # i 记录 s 中已匹配到的位置
        for t in p.split("*"):  # 按 '*' 切分模式串，逐段贪心匹配
            j = s.find(t, i)  # 从 i 开始查找当前片段
            if j == -1:  # 找不到当前片段
                return False  # 匹配失败
            i = j + len(t)  # 匹配成功后从片段末尾继续
        return True  # 所有片段按序匹配成功
