# 题目：1845. 座位预约管理系统（Seat Reservation Manager）
# 思路：用一个列表当小根堆保存所有空闲座位号；reserve 用 heappop 取最小号，unreserve 用 heappush 把归还的号放回堆中。
# 时间复杂度：构造 O(n)；reserve/unreserve 均为 O(log n)；空间复杂度：O(n)，堆中最多保存 n 个座位号。
class SeatManager:  # 题目要求的座位管理器类
    def __init__(self, n: int):  # 构造：座位编号从 1 到 n 全部空闲
        self.q = list(range(1, n + 1))  # 生成 1..n 的升序列表，它天然就是一个合法的小根堆

    def reserve(self) -> int:  # 预约并返回编号最小的可用座位
        return heappop(self.q)  # 弹出堆顶（最小值），同时把它从可用集合中移除

    def unreserve(self, seatNumber: int) -> None:  # 释放指定座位，使其重新可用
        heappush(self.q, seatNumber)  # 把归还的座位号压回堆中，heappush 会自行维护堆序


# Your SeatManager object will be instantiated and called as such:
# obj = SeatManager(n)
# param_1 = obj.reserve()
# obj.unreserve(seatNumber)
