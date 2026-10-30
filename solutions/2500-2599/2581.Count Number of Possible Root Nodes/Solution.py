# 题目：2581. 统计可能的树根数目（Count Number of Possible Root Nodes）
# 思路：先以 0 为根 DFS 统计成立的猜测数 cnt，再做换根 DP：根从 i 移到子节点 j 时只调整 (i,j)、(j,i) 两条边的贡献，从而 O(n) 得到所有根的答案。
# 时间复杂度：O(n + m)，两次 DFS 各线性，m 为 guesses 长度；空间复杂度：O(n + m)，邻接表、猜测计数器与递归栈。
class Solution:  # LeetCode 约定的题解类
    def rootCount(  # 参数较多，这里换行书写，本行开始形参列表
        self, edges: List[List[int]], guesses: List[List[int]], k: int  # edges 为树的边，guesses 为猜的父子关系，k 为要求成立的最少猜测数
    ) -> int:
        def dfs1(i, fa):  # 第一遍 DFS：以 0 为根，累加成立的猜测数到 cnt
            nonlocal cnt  # 声明 cnt 来自外层作用域，可以在嵌套函数里就地修改
            for j in g[i]:  # 遍历 i 的所有邻居
                if j != fa:  # 跳过父节点，只向子树方向走
                    cnt += gs[(i, j)]  # 若 (i, j) 被猜过则计数加一；Counter 缺失键按 0 处理
                    dfs1(j, i)  # 以 i 为父继续递归 j 的子树

        def dfs2(i, fa):  # 第二遍 DFS：换根，用增量更新代替整体重算
            nonlocal ans, cnt  # ans 和 cnt 都要在嵌套函数里修改
            ans += cnt >= k  # cnt >= k 说明当前根合法，bool 转成 0/1 累加到答案
            for j in g[i]:  # 枚举换根方向
                if j != fa:  # 只处理子节点
                    cnt -= gs[(i, j)]  # 换根后 (i, j) 不再是父子关系，贡献减少
                    cnt += gs[(j, i)]  # 换根后 (j, i) 成为父子关系，贡献增加
                    dfs2(j, i)  # 以 j 为根继续统计它的子树
                    cnt -= gs[(j, i)]  # 回溯：撤销 (j, i) 的贡献
                    cnt += gs[(i, j)]  # 回溯：恢复 (i, j) 的贡献，保证兄弟分支共享同一份 cnt

        g = defaultdict(list)  # 建无向图，defaultdict 让未出现过的节点自动得到空列表
        for a, b in edges:  # 逐条加入无向边
            g[a].append(b)  # a 的邻居里加入 b
            g[b].append(a)  # b 的邻居里加入 a，两个方向都要存
        gs = Counter((u, v) for u, v in guesses)  # 统计每条有向猜测 (u, v) 出现的次数
        cnt = 0  # 以节点 0 为根时，成立的猜测数从 0 开始累加
        dfs1(0, -1)  # 第一次 DFS 求出以 0 为根时成立的猜测数，-1 表示没有父节点
        ans = 0  # 合法根的计数从 0 开始
        dfs2(0, -1)  # 第二次 DFS 换根枚举所有可能的根
        return ans  # 返回合法根的个数
