# 题目：833. 字符串中的查找与替换（Find And Replace in String）
# 思路：先用 startswith 校验每个替换在对应下标处是否真的匹配，把「起点 → 替换编号」记入 d；再从左到右扫描原串，命中替换就整段替换并跳过，否则逐字符拷贝。
# 时间复杂度：O(n + m·L)，m 为替换个数、L 为被替换子串长度；空间复杂度：O(n)，需要 d 数组与答案列表。
class Solution:  # LeetCode 约定的题解类
    def findReplaceString(  # 返回把全部合法替换应用之后的新字符串
        self, s: str, indices: List[int], sources: List[str], targets: List[str]  # s 是原串；三个等长数组分别是替换起点、被匹配子串、替换目标
    ) -> str:  # 返回值为字符串
        n = len(s)  # 原串长度
        d = [-1] * n  # d[i] 记录从 i 开始可执行的替换编号，-1 表示该位置没有合法替换
        for k, (i, src) in enumerate(zip(indices, sources)):  # 同时遍历替换编号 k、起点 i 与待匹配子串 src
            if s.startswith(src, i):  # 只有 s 在 i 处确实以 src 开头，这次替换才合法
                d[i] = k  # 记下该位置的替换编号，供后面拼接时查用
        ans = []  # 逐段收集答案字符，最后再拼接成字符串
        i = 0  # 当前扫描位置
        while i < n:  # 从左到右扫描原串
            if ~d[i]:  # -1 按位取反为 0，因此可一次判断「该位置确实有替换」
                ans.append(targets[d[i]])  # 用替换目标整段替换原内容
                i += len(sources[d[i]])  # 跳过被替换掉的那一段字符
            else:  # 该位置没有替换
                ans.append(s[i])  # 原样保留原字符
                i += 1  # 前进一位
        return "".join(ans)  # 拼接成字符串返回
