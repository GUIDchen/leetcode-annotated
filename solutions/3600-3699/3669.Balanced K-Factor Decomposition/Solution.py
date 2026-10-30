# 3669. Balanced K-Factor Decomposition（K 因数分解）
# 核心思路：先预处理每个数的全部因子，再用回溯枚举 n 的 k 个因子的所有分解，取极差（最大值减最小值）最小的一组。
# 复杂度：预处理 O(MX log MX)，单次回溯枚举因子组合（最坏指数级），空间 O(MX log MX)。
mx = 10**5 + 1  # 预处理上界：10^5 + 1
g = [[] for _ in range(mx)]  # g[x] 存储 x 的所有因子
for i in range(1, mx):  # 枚举每一个可能的因子 i
    for j in range(i, mx, i):  # 枚举 i 的所有倍数 j
        g[j].append(i)  # i 是 j 的因子，加入 g[j]


class Solution:  # 定义 Solution 类
    def minDifference(self, n: int, k: int) -> List[int]:  # 把 n 分解成 k 个因子，使极差最小
        def dfs(i: int, x: int, mi: int, mx: int):  # i 为待填位置，x 为剩余待分解的数，mi/mx 为已选因子的最小/最大值
            if i == 0:  # 已经填到第 0 位，剩余的 x 就是最后一个因子
                nonlocal cur, ans  # 声明下面使用的是外层函数的 cur 与 ans
                d = max(mx, x) - min(mi, x)  # 计算当前 k 个因子分解的极差
                if d < cur:  # 发现更小的极差
                    cur = d  # 更新最优极差
                    path[i] = x  # 把最后一个因子写入 path
                    ans = path[:]  # 拷贝一份并保存为当前最优分解
                return  # 回溯，返回上一层继续枚举
            for y in g[x]:  # 枚举剩余部分 x 的每个因子 y
                path[i] = y  # 把因子 y 放在第 i 位
                dfs(i - 1, x // y, min(mi, y), max(mx, y))  # 继续分解 x // y，并更新已选因子的最小值和最大值

        ans = None  # 最优分解结果，初始为空
        path = [0] * k  # 长度为 k 的分解数组
        cur = inf  # 最优极差初始化为无穷大
        dfs(k - 1, n, inf, 0)  # 从第 k-1 位开始，在 n 上做因子分解
        return ans  # 返回最优分解结果
