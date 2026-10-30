# 题目：3249. 统计好节点的数目（Count the Number of Good Nodes）
# 思路：从根 0 做一次 DFS 返回每棵子树的大小；若某节点各子节点的子树大小都相同，它就是好节点。
# 时间复杂度：O(n)，每条边只被访问两次；空间复杂度：O(n)，邻接表与递归栈。
class Solution:  # # LeetCode 约定的题解类
    def countGoodNodes(self, edges: List[List[int]]) -> int:  # # edges 是树的 n-1 条无向边，返回好节点的个数
        def dfs(a: int, fa: int) -> int:  # # DFS：返回以 a 为根的子树大小，fa 是父节点
            pre = -1  # # pre 记录第一个子节点的子树大小（-1 表示还没设置基准）
            cnt = ok = 1  # # cnt 是当前子树大小（含自己），ok 表示各子节点子树大小是否全相同
            for b in g[a]:  # # 遍历 a 的所有邻居
                if b != fa:  # # 跳过父节点 fa，只往子节点方向递归
                    cur = dfs(b, a)  # # 递归求子节点 b 的子树大小
                    cnt += cur  # # 把子树的节点数累加到当前子树
                    if pre < 0:  # # 第一个子节点只用来设置比较基准
                        pre = cur  # # 记下这个基准值
                    elif pre != cur:  # # 之后的子节点必须与基准相同，否则不是好节点
                        ok = 0  # # 子树大小不一致，标记 ok = 0
            nonlocal ans  # # 声明 ans 来自外层函数，允许在内层 dfs 中修改
            ans += ok  # # ok 为 1 时 ans 加一，正好把 bool 当整数用
            return cnt  # # 返回当前子树的大小给父节点

        g = defaultdict(list)  # # 邻接表：defaultdict 访问不存在的键会自动创建空列表
        for a, b in edges:  # # 逐条读入无向边
            g[a].append(b)  # # 把 b 记入 a 的邻接表
            g[b].append(a)  # # 把 a 记入 b 的邻接表（无向边要存两次）
        ans = 0  # # ans 累计好节点的个数
        dfs(0, -1)  # # 从根节点 0 开始遍历，根的父节点记为 -1
        return ans  # # 返回好节点总数
