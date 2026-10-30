# 题目：3310. 移除可疑的方法（Remove Methods From Project）
# 思路：先用有向图 DFS 标记出 k 能直接或间接调用的方法（可疑集合）；再用无向图从集合外的方法扩散，凡是与外部相连的方法都不能删，取消其余可疑标记。
# 复杂度：时间 O(n + m)，每条调用关系在两张邻接表里各被遍历一次；空间 O(n + m)，用于存邻接表与标记数组。
class Solution:  # LeetCode 约定的题解类
    def remainingMethods(  # 参数分行书写：n 为方法总数，k 为可疑方法，invocations 为调用关系列表
        self, n: int, k: int, invocations: List[List[int]]  # 续行：每个 [a, b] 表示方法 a 调用了方法 b
    ) -> List[int]:  # 返回移除可疑方法后仍保留的方法编号（升序）
        def dfs(i: int):  # 递归函数：从 i 出发沿有向边标记所有可达（即可疑）的方法
            suspicious[i] = True  # 先标记当前方法为可疑
            for j in g[i]:  # 遍历方法 i 直接调用的方法
                if not suspicious[j]:  # 未标记过才继续，防止环上无限递归
                    dfs(j)  # 递归处理被调用的方法

        def dfs2(i: int):  # 递归函数：从可疑集合外的方法出发，沿无向边扩散并取消标记
            vis[i] = True  # 标记已访问，避免重复遍历
            for j in f[i]:  # 遍历无向图上的邻居
                if not vis[j]:  # 邻居还没访问过
                    suspicious[j] = False  # 它与集合外的方法相连，说明不能单独删除，取消可疑标记
                    dfs2(j)  # 继续向外扩散

        f = [[] for _ in range(n)]  # 无向邻接表：用于判断可疑集合是否与集合外的方法相连
        g = [[] for _ in range(n)]  # 有向邻接表：只保留 a→b，用于求从 k 出发的可疑闭包
        for a, b in invocations:  # 逐条读入调用关系
            f[a].append(b)  # 无向图：a 的邻接表加入 b
            f[b].append(a)  # 无向图：b 的邻接表加入 a
            g[a].append(b)  # 有向图只记录 a→b 这条边
        suspicious = [False] * n  # 可疑标记数组，下标即方法编号，初始都不可疑
        dfs(k)  # 从 k 出发，求出完整的可疑集合

        vis = [False] * n  # 反向扩散用的访问标记数组
        ans = []  # 预留的答案列表（最终结果由末尾的列表推导生成）
        for i in range(n):  # 枚举所有方法，把它们作为扩散起点
            if not suspicious[i] and not vis[i]:  # 起点必须在可疑集合之外，且尚未被扩散访问
                dfs2(i)  # 从该起点扩散，把与之连通的方法一并排除在删除范围之外
        return [i for i in range(n) if not suspicious[i]]  # 返回最终仍不可疑（需要保留）的方法编号
