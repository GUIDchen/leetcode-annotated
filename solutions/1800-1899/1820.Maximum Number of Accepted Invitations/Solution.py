# 题目：1820. 最多邀请的个数（Maximum Number of Accepted Invitations）
# 核心思路：把男生与女生视作二分图的两侧，用 DFS 版匈牙利算法逐个男生寻找增广路（必要时让已有匹配的男生改约），成功匹配的男生数就是最多接受的邀请数。
# 时间复杂度：O(m·E)，最坏 O(m²n)；空间复杂度：O(n) 保存 match 与递归栈，vis 每轮重建。
class Solution:  # LeetCode 约定的题解类
    def maximumInvitations(self, grid: List[List[int]]) -> int:  # grid[i][j] 为 1 表示第 i 个男生愿意邀请第 j 个女生
        def find(i):  # 递归函数 find：为男生 i 寻找增广路，返回是否匹配成功
            for j, v in enumerate(grid[i]):  # 同时取出女生下标 j 与 grid[i][j] 的取值 v
                if v and j not in vis:  # 女生愿意合作且本轮还没访问过
                    vis.add(j)  # 标记已访问，避免同一轮内重复搜索
                    if match[j] == -1 or find(match[j]):  # 女生 j 空闲，或她的原配男生能改约其他女生
                        match[j] = i  # 把女生 j 改匹配给男生 i
                        return True  # 找到增广路，返回成功
            return False  # 没有可行增广路，返回失败

        m, n = len(grid), len(grid[0])  # m 个男生、n 个女生
        match = [-1] * n  # match[j] 记录女生 j 当前匹配的男生，-1 表示空闲
        ans = 0  # ans 记录匹配成功的男生数
        for i in range(m):  # 逐个男生尝试匹配
            vis = set()  # 每个男生单独重建访问集合，使各轮互不影响
            ans += find(i)  # True/False 当作 1/0 累加，即为匹配总数
        return ans  # 返回最多能接受的邀请数
