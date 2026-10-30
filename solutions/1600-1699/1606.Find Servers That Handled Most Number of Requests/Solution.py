# 题目：1606. 找到处理最多请求的服务器（Find Servers That Handled Most Number of Requests）
# 思路：SortedList 存空闲服务器、小根堆存忙碌服务器的忙完时刻；每个请求先归还空闲的，再从 i%k 起环形找可用服务器。
# 时间复杂度：O((n + k) log k)，每次查找/插入/删除为对数级；空间复杂度：O(k)。
class Solution:  # 题解类
    def busiestServers(self, k: int, arrival: List[int], load: List[int]) -> List[int]:  # k 为服务器个数，arrival 为到达时间数组，load 为各请求的处理耗时数组
        free = SortedList(range(k))  # SortedList 是自动保持有序的容器，存放当前空闲的服务器编号
        busy = []  # 小根堆：(忙完时刻, 服务器编号)，堆顶是最早空闲的
        cnt = [0] * k  # 每台服务器已处理的请求数，初始都是 0
        for i, (start, t) in enumerate(zip(arrival, load)):  # 按时间顺序处理每个请求，i 是请求下标
            while busy and busy[0][0] <= start:  # 把已忙完（忙完时刻 ≤ 当前到达时间）的服务器还回空闲集合
                free.add(busy[0][1])  # 该服务器重新空闲
                heappop(busy)  # 从堆中弹出已归还的项
            if not free:  # 没有任何空闲服务器
                continue  # 该请求被丢弃，处理下一个
            j = free.bisect_left(i % k)  # 环形规则：从 i % k 开始找编号不小于它的空闲服务器（二分定位）
            if j == len(free):  # 后面没有更大的编号了
                j = 0  # 回绕到编号最小的空闲服务器
            server = free[j]  # 选中的服务器编号
            cnt[server] += 1  # 该服务器处理请求数加一
            heappush(busy, (start + t, server))  # 把它的忙完时刻压入堆
            free.remove(server)  # 并从空闲集合中移除，表示进入忙碌

        mx = max(cnt)  # 所有服务器中的最大处理请求数
        return [i for i, v in enumerate(cnt) if v == mx]  # 取出处理数等于最大值的所有服务器编号
