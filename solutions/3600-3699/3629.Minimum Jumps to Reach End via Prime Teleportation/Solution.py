# 3629. 通过质数传送到达终点的最少跳跃次数 / Minimum Jumps to Reach End via Prime Teleportation
# 核心思路：线性筛预处理每个数的质因子，把含有同一质因子的下标连成传送边，再按层 BFS 求最少跳跃次数
# 时间复杂度 O(mx log log mx + n·ω)，空间复杂度 O(mx log log mx + n)，其中 ω 为质因子个数
#
mx = 10**6 + 1  # mx 为数值上限 1e6 加一
factors = [[] for _ in range(mx)]  # factors[x] 保存 x 的所有质因子
for i in range(2, mx):  # 从小到大枚举候选质因子 i
    if not factors[i]:  # factors[i] 为空说明 i 没被更小的质数标记过，即 i 是质数
        for j in range(i, mx, i):  # 用质数 i 去筛它的所有倍数 j
            factors[j].append(i)  # 把质因子 i 追加到 j 的因子列表中


class Solution:  # 题目要求实现的类
    def minJumps(self, nums: List[int]) -> int:  # 返回从下标 0 跳到下标 n-1 的最少跳跃次数
        n = len(nums)  # n 为数组长度
        g = defaultdict(list)  # g[p] 记录所有含有质因子 p 的下标，等价于传送图
        for i, x in enumerate(nums):  # 同时枚举下标与数值
            for p in factors[x]:  # 枚举该数值的每个质因子
                g[p].append(i)  # 把下标 i 挂到质因子 p 的传送列表上
        ans = 0  # ans 记录当前 BFS 层数，也就是跳跃次数
        vis = [False] * n  # vis 标记下标是否已经访问过
        vis[0] = True  # 起点 0 标记为已访问
        q = [0]  # 队列存放当前层的下标，初始只有起点
        while 1:  # 按层 BFS 扩展，由内部 return 结束
            nq = []  # nq 收集下一层的下标
            for i in q:  # 处理当前层的全部下标
                if i == n - 1:  # 到达最后一个下标即抵达终点
                    return ans  # 返回当前层数作为最少跳跃次数
                idx = g[nums[i]]  # 该数值能传送到的所有下标
                idx.append(i + 1)  # 总是可以向后走一步到 i+1
                if i:  # 如果不在数组首元素（i 非零）
                    idx.append(i - 1)  # 就可以向前走一步到 i-1
                for j in idx:  # 枚举所有一步可到达的下标
                    if not vis[j]:  # 只扩展还没访问过的下标
                        vis[j] = True  # 标记为已访问，防止重复入队
                        nq.append(j)  # 加入下一层队列
                idx.clear()  # 清空该质因子的传送列表，后续无需再次枚举
            q = nq  # 把下一层作为新的当前层
            ans += 1  # 跳跃次数加一
