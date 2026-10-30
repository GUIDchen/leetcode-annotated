# 题目：399. 除法求值（Evaluate Division）
# 思路：带权并查集。令 w[x] 表示「x 的值 / 父节点的值」，把每个等式 a / b = v 当作一次集合合并并推出新根的权值，查询时用 c、d 到根的权值相除。
# 时间复杂度：O((n + m) α(n))，n 为等式数、m 为查询数；空间复杂度：O(n)，父指针表与权值表各 O(n)。
class Solution:  # LeetCode 约定的题解类
    def calcEquation(  # 先用等式建带权并查集，再回答所有查询
        self, equations: List[List[str]], values: List[float], queries: List[List[str]]  # 形参换行：equations 是等式列表，values 是对应的比值，queries 是待求的查询
    ) -> List[float]:  # 返回每个查询的浮点答案
        def find(x):  # 带路径压缩的查找：返回根，并把 w[x] 修正为 x 到根的比值
            if p[x] != x:  # x 还不是根节点
                origin = p[x]  # 先记下旧父节点，压缩后要靠它换算权重
                p[x] = find(p[x])  # 递归找到根，并把 x 直接挂到根下
                w[x] *= w[origin]  # 路径变短后更新权重：x 到根 = (x 到旧父) * (旧父到根)
            return p[x]  # 返回根变量名

        w = defaultdict(lambda: 1)  # 权值表：w[x] 表示 x 的值与父节点值之比，默认 1
        p = defaultdict()  # 父指针表：变量名 -> 父变量名
        for a, b in equations:  # 第一遍：让每个出现过的变量各自成集合
            p[a], p[b] = a, b  # 父指针先指向自己
        for i, v in enumerate(values):  # 第二遍：按 a / b = v 合并集合
            a, b = equations[i]  # 取出当前等式
            pa, pb = find(a), find(b)  # 分别找到两个变量所在集合的根（会顺带压缩路径）
            if pa == pb:  # 根相同说明等式冗余
                continue  # 跳过这条等式
            p[pa] = pb  # 把 a 的根挂到 b 的根下面
            w[pa] = w[b] * v / w[a]  # 由 a/b = v 推出 pa/pb = w[b]*v/w[a]，据此设置新根的权值
        return [  # 逐条查询，用列表推导式构造答案
            -1 if c not in p or d not in p or find(c) != find(d) else w[c] / w[d]  # 变量缺失或不在同一集合时无解给 -1，否则两个权值相除就是 c/d
            for c, d in queries  # 遍历每个查询
        ]  # 列表推导式结束
