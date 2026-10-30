# 3437. 全排列 III / Permutations III
# 核心思路：DFS 回溯枚举 1..n 的排列，仅当相邻元素奇偶性不同时才可相邻（首个位置不限制），vis 标记已用数字。
# 复杂度：时间 O(n * n!)，空间 O(n)（不计结果存储）。
class Solution:  # 定义题解类
    def permute(self, n: int) -> List[List[int]]:  # 返回 1..n 中相邻元素奇偶交替的全部排列
        def dfs(i: int) -> None:  # 递归回溯：i 为当前已填位置数
            if i >= n:  # 已填满 n 个位置
                ans.append(t[:])  # 追加当前排列的副本
                return  # 结束本层递归
            for j in range(1, n + 1):  # 枚举下一个可放的数字
                if not vis[j] and (i == 0 or t[-1] % 2 != j % 2):  # 未被使用，且与上一个数字奇偶性不同
                    t.append(j)  # 把 j 加入当前排列
                    vis[j] = True  # 标记数字 j 已使用
                    dfs(i + 1)  # 递归填下一个位置
                    vis[j] = False  # 回溯：取消使用标记
                    t.pop()  # 回溯：弹出 j

        ans = []  # 结果集合
        t = []  # 当前正在构造的排列
        vis = [False] * (n + 1)  # vis[x] 表示数字 x 是否已被使用
        dfs(0)  # 从第 0 个位置开始搜索
        return ans  # 返回全部合法排列
