# 题目：1462. 课程表 IV（Course Schedule IV）
# 思路：把先修关系看成有向图的边，用 Floyd 算法求传递闭包 f[i][j]（i 是否是 j 的先修课，含间接关系），再按 queries 逐条查表。
# 时间复杂度：O(n^3 + q)，三重循环求闭包，q 为询问数；空间复杂度：O(n^2)，布尔矩阵存可达性。
class Solution:  # LeetCode 约定的题解类
    def checkIfPrerequisite(  # 方法签名：n 为课程数，prerequisites 为直接先修关系，queries 为询问列表
        self, n: int, prerequisites: List[List[int]], queries: List[List[int]]  # 参数与类型标注：prerequisites[i]=[a,b] 表示 a 是 b 的直接先修课
    ) -> List[bool]:  # 返回值：每个询问对应的布尔结果列表
        f = [[False] * n for _ in range(n)]  # f[i][j] 为 True 表示 i 是 j 的先修课程（直接或间接），初始全为 False
        for a, b in prerequisites:  # 遍历所有直接先修关系
            f[a][b] = True  # a 是 b 的直接先修课，先标记这条边
        for k in range(n):  # Floyd 传递闭包：k 为中间点
            for i in range(n):  # i 为起点（先修课候选）
                for j in range(n):  # j 为终点（后继课）
                    if f[i][k] and f[k][j]:  # i 能到 k 且 k 能到 j
                        f[i][j] = True  # 于是 i 也能到 j，标记为可达（含间接先修关系）
        return [f[a][b] for a, b in queries]  # 列表推导式按询问顺序 O(1) 查表得到答案
