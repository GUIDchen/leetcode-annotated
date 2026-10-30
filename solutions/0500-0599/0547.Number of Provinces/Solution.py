# 题目：547. 省份数量（Number of Provinces）
# 思路：把邻接矩阵看成无向图，用 DFS 遍历连通块，每启动一次新的 DFS 就说明多了一个省份。
# 时间复杂度：O(n^2)，每个城市都要扫描一整行邻接关系；空间复杂度：O(n)，访问数组加递归栈。
class Solution:  # LeetCode 约定的题解类
    def findCircleNum(self, isConnected: List[List[int]]) -> int:  # isConnected 是邻接矩阵，返回省份（连通分量）的个数
        def dfs(i: int):  # 内部 DFS：从城市 i 出发，把同一连通块的城市全部标记
            vis[i] = True  # 标记当前城市已访问
            for j, x in enumerate(isConnected[i]):  # 同时取出下标 j 与 i、j 之间的连接关系 x
                if not vis[j] and x:  # j 未访问过且与 i 直接相连
                    dfs(j)  # 继续深入 j

        n = len(isConnected)  # 城市的数量 n
        vis = [False] * n  # 访问标记列表，初始全部为未访问
        ans = 0  # 省份计数
        for i in range(n):  # 依次检查每个城市
            if not vis[i]:  # 尚未访问就说明发现了一个新的省份
                dfs(i)  # 把这个省份的全部城市标记掉
                ans += 1  # 省份数加一
        return ans  # 返回省份总数
