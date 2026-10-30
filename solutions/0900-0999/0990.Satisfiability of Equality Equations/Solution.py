# 题目：990. 等式方程的可满足性（Satisfiability of Equality Equations）
# 思路：并查集。先合并所有「==」两端的字母，再检查每个「!=」两端是否落在同一集合。
# 时间复杂度：O(n·α(26)) 近似 O(n)，n 为等式条数；空间复杂度：O(1)，只需要 26 个字母的父数组。
class Solution:  # LeetCode 约定的题解类
    def equationsPossible(self, equations: List[str]) -> bool:  # equations：形如 "a==b" 或 "a!=b" 的等式列表；判断它们能否同时成立
        def find(x):  # 并查集查找：递归找根并做路径压缩（p 在外层稍后创建，闭包按调用时取值）
            if p[x] != x:  # 父结点不是自己，说明还没到根
                p[x] = find(p[x])  # 递归找根，并把当前结点直接挂到根下（路径压缩）
            return p[x]  # 返回集合代表元

        p = list(range(26))  # 26 个小写字母的并查集，初始时每个字母各自独立
        for e in equations:  # 第一遍：只处理 '=='，把相等关系合并
            a, b = ord(e[0]) - ord('a'), ord(e[-1]) - ord('a')  # 等式固定形如 "x==y"，e[0] 与 e[-1] 是两个字母
            if e[1] == '=':  # e[1] 为 '=' 表示两者相等
                p[find(a)] = find(b)  # 合并两个集合：把 a 的根挂到 b 的根下
        for e in equations:  # 第二遍：检查 '!=' 是否与已合并的相等关系冲突
            a, b = ord(e[0]) - ord('a'), ord(e[-1]) - ord('a')  # 同样取出不等号两侧的字母
            if e[1] == '!' and find(a) == find(b):  # 要求不相等，却查出同属一个集合
                return False  # 约束矛盾，返回 False
        return True  # 全部约束可满足，返回 True
