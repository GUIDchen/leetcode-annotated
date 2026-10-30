# 题目：502. IPO（IPO）
# 思路：用按启动资本排序的小根堆把「现在买得起」的项目逐个解锁到另一个堆里，每轮贪心取利润最大的那个，最多取 k 轮。
# 时间复杂度：O(n log n + k log n)，建堆与每轮取堆顶；空间复杂度：O(n)，两个堆最多共 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def findMaximizedCapital(  # 方法签名的开始：k 是最多可选项目数，w 是初始资本
        self, k: int, w: int, profits: List[int], capital: List[int]  # profits 与 capital 分别是各项目的利润和启动资本
    ) -> int:  # 返回最终能获得的最大资本
        h1 = [(c, p) for c, p in zip(capital, profits)]  # 把 (启动资本, 利润) 打包成元组，便于用堆按资本排序
        heapify(h1)  # 原地建堆，h1 变成按启动资本升序的小根堆
        h2 = []  # h2 存放当前买得起的项目的利润（存负数以模拟大根堆）
        while k:  # 最多挑选 k 个项目
            while h1 and h1[0][0] <= w:  # 把启动资本不超过当前资本的解锁
                heappush(h2, -heappop(h1)[1])  # 取负后入堆：Python 只有小根堆，负数即等价于大根堆
            if not h2:  # 没有买得起的项目，资本无法继续增长
                break  # 提前结束选项目
            w -= heappop(h2)  # 贪心选出利润最大的项目（负数取回实际利润）并累加资本
            k -= 1  # 已经用一个项目名额
        return w  # 返回最终资本
