# 题目：2049. 统计最高分的节点数目（Count Nodes With the Highest Score）
# 思路：先按 parents 建孩子表，后序 DFS 求每棵子树大小；删掉节点后，各连通块大小即各孩子子树大小与 n - 子树大小，乘积就是得分，同时维护最高分与个数。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，孩子表与递归栈。
class Solution:  # LeetCode 约定的题解类
    def countHighestScoreNodes(self, parents: List[int]) -> int:  # parents[i] 是节点 i 的父节点；返回得分最高的节点个数
        def dfs(i: int, fa: int):  # 后序 DFS：返回以 i 为根的子树的节点数，fa 是父节点用于跳过回边
            cnt = score = 1  # cnt 是子树大小（先算自己），score 是节点 i 的得分（乘积初值为 1）
            for j in g[i]:  # 遍历 i 的所有孩子
                if j != fa:  # 跳过父节点，避免往回走
                    t = dfs(j, i)  # 递归求出这个孩子的子树大小
                    score *= t  # 每个孩子子树是独立连通块，大小乘进得分
                    cnt += t  # 把孩子的节点数累加进子树大小
            if n - cnt:  # 父节点那一侧也是连通块，大小为 n - cnt
                score *= n - cnt  # 把上方连通块大小乘进得分；大小为 0 时跳过，免得得分被清零
            nonlocal ans, mx  # 声明 ans 与 mx 来自外层函数，需要在这里修改
            if mx < score:  # 出现更高的得分
                mx = score  # 更新最高分
                ans = 1  # 计数重置为 1
            elif mx == score:  # 与当前最高分并列
                ans += 1  # 计数加一
            return cnt  # 把子树大小返回给父节点

        n = len(parents)  # 节点总数
        g = [[] for _ in range(n)]  # 孩子表：g[i] 保存节点 i 的所有孩子
        for i in range(1, n):  # 0 号是根，从 1 号开始把每个节点挂到父节点下
            g[parents[i]].append(i)  # 把 i 加入它的父节点的孩子列表
        ans = mx = 0  # ans 记录最高分节点个数，mx 记录当前最高分
        dfs(0, -1)  # 从根节点开始后序遍历
        return ans  # 返回得分最高的节点个数
