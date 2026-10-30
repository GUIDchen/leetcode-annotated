# 题目：1834. 单线程 CPU（Single-Threaded CPU）
# 思路：任务追加原始下标后按入队时间排序，用最小堆按 (耗时, 下标) 取出可执行的最优先任务；堆空时时间跳到下一任务入队时刻，逐步模拟。
# 时间复杂度：O(n log n)，排序与每次堆操作均为对数级；空间复杂度：O(n)，堆与答案列表最多各存 n 项。
class Solution:  # LeetCode 约定的题解类
    def getOrder(self, tasks: List[List[int]]) -> List[int]:  # tasks 每行为 [入队时间, 处理耗时]，返回任务原始下标的执行顺序
        for i, task in enumerate(tasks):  # 枚举任务，同时拿到该任务的原始下标 i
            task.append(i)  # 把原始下标追加到任务末尾，排序后仍能还原原位置
        tasks.sort()  # 按 [入队时间, 耗时, 原始下标] 字典序升序原地排序
        ans = []  # 记录任务的执行顺序（原始下标）
        q = []  # 当作小根堆使用，元素为 (耗时, 原始下标)
        n = len(tasks)  # 任务总数
        i = t = 0  # i 是下一个待入堆任务的下标，t 是 CPU 当前时间
        while q or i < n:  # 堆非空或还有任务没入堆，就继续模拟（heappush/heappop 来自 heapq）
            if not q:  # 堆空说明 CPU 空闲
                t = max(t, tasks[i][0])  # 时间跳到下一个任务最早可入堆的时刻
            while i < n and tasks[i][0] <= t:  # 把所有入队时间已到（不大于 t）的任务压入堆
                heappush(q, (tasks[i][1], tasks[i][2]))  # 入堆 (耗时, 原始下标)，此后按耗时优先出堆
                i += 1  # 该任务已入堆，指针后移
            pt, j = heappop(q)  # 弹出最优任务：耗时最小、下标最小的那个
            ans.append(j)  # 把原始下标加入答案
            t += pt  # 时间推进该任务的耗时
        return ans  # 所有任务执行完，返回顺序
