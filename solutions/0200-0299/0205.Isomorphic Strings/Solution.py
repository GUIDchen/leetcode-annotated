# 题目：205. 同构字符串（Isomorphic Strings）
# 思路：用两个字典分别维护 s→t 和 t→s 的映射，逐位检查新旧映射是否冲突，两个方向都一致才算同构。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(Σ)，Σ 为字符集大小。
class Solution:  # LeetCode 约定的题解类
    def isIsomorphic(self, s: str, t: str) -> bool:  # 判断 s 与 t 是否同构（字符一一对应）
        d1 = {}  # s 的字符 -> t 的字符
        d2 = {}  # t 的字符 -> s 的字符，反向映射用来防止两个不同字符映射到同一个字符
        for a, b in zip(s, t):  # zip 逐位同步取两串的字符，两串等长所以不会漏
            if (a in d1 and d1[a] != b) or (b in d2 and d2[b] != a):  # 正反两个方向任一出现与旧映射不一致的情况，就说明冲突
                return False  # 不同构
            d1[a] = b  # 建立 a -> b 的映射
            d2[b] = a  # 同时建立 b -> a 的映射
        return True  # 全程没有冲突，说明同构
