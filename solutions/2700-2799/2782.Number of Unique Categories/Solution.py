# 题目：2782. 唯一类别的数量（Number of Unique Categories）
# 核心思路：并查集。枚举所有下标对 (a, b)，用判题器接口判断是否同类并合并集合；最后统计父指针等于下标的根结点个数，即类别数量。
# 时间复杂度：O(n^2 * α(n))，n^2 次询问、每次合并近似 O(1)；空间复杂度：O(n)，父指针数组。
# Definition for a category handler.
# class CategoryHandler:
#     def haveSameCategory(self, a: int, b: int) -> bool:
#         pass
class Solution:  # LeetCode 约定的题解类
    def numberOfCategories(  # 函数签名跨三行：n 是元素个数，categoryHandler 是判题器接口（第 1 行）
        self, n: int, categoryHandler: Optional['CategoryHandler']  # 参数续行：self 与 n 与 categoryHandler（第 2 行）
    ) -> int:  # 返回值注解与函数体开始（第 3 行）
        def find(x: int) -> int:  # 带路径压缩的递归 find；p 在函数后面才创建，但调用都发生在创建之后，闭包能取到它
            if p[x] != x:  # 当前结点不是根，就继续往上找
                p[x] = find(p[x])  # 递归找根，并把父指针直接指向根，实现路径压缩
            return p[x]  # 返回根结点

        p = list(range(n))  # 并查集父指针数组，初始时每个元素各自成一类
        for a in range(n):  # 枚举左元素 a
            for b in range(a + 1, n):  # 只枚举 b > a 的对，避免重复询问同一对元素
                if categoryHandler.haveSameCategory(a, b):  # 判题器判定二者属于同一类别
                    p[find(a)] = find(b)  # 合并：把 a 的根挂到 b 的根下面
        return sum(i == x for i, x in enumerate(p))  # p[i] == i 的结点是根，根的数量就是类别数量
