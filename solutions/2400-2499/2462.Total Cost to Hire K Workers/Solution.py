# 题目：2462. 雇佣 K 位工人的总代价（Total Cost to Hire K Workers）
# 思路：用小根堆保存左右两端各 candidates 个候选工人，每轮弹出最小代价者并从同侧补人；两侧区间重叠时直接排序取前 k 小。
# 时间复杂度：O((n + k) log candidates)，堆规模不超过 2*candidates；空间复杂度：O(candidates)。
class Solution:  # LeetCode 约定的题解类
    def totalCost(self, costs: List[int], k: int, candidates: int) -> int:  # costs 是每个工人的代价，k 是雇佣人数，candidates 是两侧候选人数
        n = len(costs)  # 工人总数
        if candidates * 2 >= n:  # 两段候选区间重叠（甚至覆盖全部），此时每轮都能看到全局最小值
            return sum(sorted(costs)[:k])  # 等价于直接取最小的 k 个代价求和
        pq = []  # 小根堆，元素为元组（代价, 下标）
        for i, c in enumerate(costs[:candidates]):  # 左端 candidates 个人入堆
            heappush(pq, (c, i))  # 元组先比代价、同代价再比下标，保证弹出顺序确定
        for i in range(n - candidates, n):  # 右端 candidates 个人入堆
            heappush(pq, (costs[i], i))  # 保存原始下标，后面据此判断该从哪一侧补人
        heapify(pq)  # 一次性把列表调整为合法堆，比逐个 heappush 更高效
        l, r = candidates, n - candidates - 1  # l、r 分别指向左右两端下一个待补入的下标
        ans = 0  # 累计总代价
        for _ in range(k):  # 共 k 轮，每轮雇佣一名当前代价最小的工人
            c, i = heappop(pq)  # 弹出堆顶：当前可选工人中代价最小者及其下标
            ans += c  # 把这份代价累加进总代价
            if l > r:  # l > r 说明左右候选区间已经相遇，没有新候选可补
                continue  # 跳过补水逻辑，直接进入下一轮
            if i < l:  # 该工人来自左端
                heappush(pq, (costs[l], l))  # 从左端补入下一个候选
                l += 1  # 左指针右移一格
            else:  # 否则该工人来自右端
                heappush(pq, (costs[r], r))  # 从右端补入下一个候选
                r -= 1  # 右指针左移一格
        return ans  # 返回最小总代价
