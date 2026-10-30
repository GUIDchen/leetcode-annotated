# 题目：582. 杀掉进程（Kill Process）
# 核心思路：用邻接表把 ppid 映射到其子进程，再从 kill 出发做一次 DFS，把整棵进程子树的进程号收集起来。
# 时间复杂度：O(n)，建图与遍历各访问每个进程一次；空间复杂度：O(n)，邻接表与答案列表。
class Solution:  # LeetCode 约定的题解类
    def killProcess(self, pid: List[int], ppid: List[int], kill: int) -> List[int]:  # pid 与 ppid 下标一一对应，kill 为被杀进程号
        def dfs(i: int):  # 递归终止进程 i 以及它的全部后代（返回值由外层 ans 累积）
            ans.append(i)  # 当前进程被终止，记入答案
            for j in g[i]:  # 遍历当前进程的所有子进程
                dfs(j)  # 递归终止该子进程及其后代

        g = defaultdict(list)  # 邻接表：父进程号 -> 子进程号列表，缺键时自动创建空列表
        for i, p in zip(pid, ppid):  # 同时遍历子进程号与父进程号
            g[p].append(i)  # 把子进程 i 挂到父进程 p 的子进程列表中
        ans = []  # 收集所有被终止的进程号，须在 dfs 调用前定义
        dfs(kill)  # 从被 kill 的进程开始递归
        return ans  # 返回被终止的进程号列表（DFS 先序）
