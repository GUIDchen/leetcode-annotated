# 题目：1882. 使用服务器处理任务（Process Tasks Using Servers）
# 思路：用小根堆维护空闲服务器（权重, 下标）与忙碌服务器（释放时刻, 权重, 下标），每个任务前先把已释放的服务器搬回空闲堆再分配。
# 时间复杂度：O((n + m) log n)，每次堆操作对数级；空间复杂度：O(n + m)，两个堆加答案数组。
class Solution:  # LeetCode 约定的题解类
    def assignTasks(self, servers: List[int], tasks: List[int]) -> List[int]:  # servers 是服务器权重，tasks 是任务耗时
        idle = [(x, i) for i, x in enumerate(servers)]  # 空闲堆元素：(权重, 下标)，初始全部空闲
        heapify(idle)  # 原地堆化，使字典序最小的 (权重, 下标) 位于堆顶
        busy = []  # 忙碌堆元素：(释放时刻, 权重, 下标)
        ans = []  # 依次记录每个任务选中的服务器下标
        for j, t in enumerate(tasks):  # 按下标处理任务，j 同时代表当前时刻
            while busy and busy[0][0] <= j:  # 把当前时刻已经忙完的服务器全部搬回空闲堆
                _, s, i = heappop(busy)  # 取出最早释放的那台（下划线占位，忽略释放时刻）
                heappush(idle, (s, i))  # 以 (权重, 下标) 重新加入空闲堆
            if idle:  # 有空闲服务器就直接分配
                s, i = heappop(idle)  # 取权重最小、权重相同则下标最小的空闲服务器
                heappush(busy, (j + t, s, i))  # 它要到 j + t 时刻才重新空闲
            else:  # 没有空闲服务器，只能让最早释放的那台继续工作
                w, s, i = heappop(busy)  # w 是它最早释放的时刻
                heappush(busy, (w + t, s, i))  # 释放时刻在 w 基础上顺延 t
            ans.append(i)  # 记录本轮选中的服务器下标
        return ans  # 返回所有任务的分配结果
