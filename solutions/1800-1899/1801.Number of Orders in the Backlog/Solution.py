# 题目：1801. 积压订单中的订单总数（Number of Orders in the Backlog）
# 思路：用两个堆分别维护卖单（价格升序）与买单（价格降序，存负价格）；新订单先与对手盘撮合，余量入堆，最后统计两堆剩余总量取模。
# 时间复杂度：O(n log n)，每笔订单的撮合与入堆都是堆操作；空间复杂度：O(n)，堆中最多保存 n 笔订单。
class Solution:  # LeetCode 约定的题解类
    def getNumberOfBacklogOrders(self, orders: List[List[int]]) -> int:  # orders[i] = [price, amount, orderType]，type 为 0 是买单、1 是卖单
        buy, sell = [], []  # buy 用小根堆存 (-价格, 数量) 模拟大根堆；sell 用小根堆存 (价格, 数量)
        for p, a, t in orders:  # 逐笔处理订单
            if t == 0:  # t == 0：买单，去和卖单撮合
                while a and sell and sell[0][0] <= p:  # 还有剩余量，且最便宜的卖单价格不高于出价时继续成交
                    x, y = heappop(sell)  # 弹出价格最低的卖单，x 为价格、y 为数量
                    if a >= y:  # 买单足以整笔吃掉这笔卖单
                        a -= y  # 扣掉已成交的数量
                    else:  # 否则买单不够，只能部分成交
                        heappush(sell, (x, y - a))  # 卖单剩余部分按原价放回堆中
                        a = 0  # 买单被完全消耗
                if a:  # 撮合后仍有剩余，挂进买单积压队列
                    heappush(buy, (-p, a))  # 价格取负入小根堆，等价于按价格从高到低的优先队列
            else:  # 否则是卖单，去和买单撮合
                while a and buy and -buy[0][0] >= p:  # 还有剩余量，且最高买价不低于卖价时继续成交
                    x, y = heappop(buy)  # 弹出出价最高的买单，x 为取负后的价格、y 为数量
                    if a >= y:  # 卖单足以整笔吃掉这笔买单
                        a -= y  # 扣掉已成交的数量
                    else:  # 否则卖单不够，只能部分成交
                        heappush(buy, (x, y - a))  # 买单剩余部分放回堆中
                        a = 0  # 卖单被完全消耗
                if a:  # 卖单仍有剩余，挂进卖单积压队列
                    heappush(sell, (p, a))  # 按原价与剩余量存入卖单堆
        mod = 10**9 + 7  # 题目要求对 1e9+7 取模
        return sum(v[1] for v in buy + sell) % mod  # 两个堆中剩余数量之和即为积压订单数
