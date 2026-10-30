# 题目：1061. 按字典序排列最小的等效字符串（Lexicographically Smallest Equivalent String）
# 思路：用并查集合并等价字母，合并时始终让字典序更小的根当父节点，于是每个集合的根就是最小字符，逐个替换 baseStr 的字符即可。
# 时间复杂度：O((n + m)·α(26))，近似线性；空间复杂度：O(26) 即 O(1)，只用固定大小的字母表。
class Solution:  # LeetCode 约定的题解类
    def smallestEquivalentString(self, s1: str, s2: str, baseStr: str) -> str:  # s1[i] 与 s2[i] 等价，求 baseStr 的字典序最小等价串
        def find(x: int) -> int:  # 查根 + 路径压缩
            if p[x] != x:  # 当前节点不是根
                p[x] = find(p[x])  # 递归把父指针直接指向根
            return p[x]  # 返回根节点

        p = list(range(26))  # 并查集父指针，初始每个字母自成一类
        for a, b in zip(s1, s2):  # 逐对处理等价关系
            x, y = ord(a) - ord("a"), ord(b) - ord("a")  # 把字母映射为 0..25 的编号
            px, py = find(x), find(y)  # 两个集合的根
            if px < py:  # 保证集合的根始终是字典序更小的那个
                p[py] = px  # 大根合并到小根
            else:  # 否则（py 更小或两者相等）
                p[px] = py  # 同样合并到较小的根（相等时无副作用）
        return "".join(chr(find(ord(c) - ord("a")) + ord("a")) for c in baseStr)  # 每个字符替换为所在集合的最小字符
