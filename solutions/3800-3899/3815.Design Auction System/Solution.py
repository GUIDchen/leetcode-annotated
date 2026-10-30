# 题目：3815. 设计拍卖系统（Design Auction System）
# 思路：双向索引。users 记录每个用户对各物品的出价，items 记录每件物品的「(出价, 用户)」有序列表。每次新增或改价都先删旧记录再插新记录，最高出价者直接取有序列表的尾部元素。
# 时间复杂度：addBid/updateBid/removeBid 均为 O(log m)，getHighestBidder 为 O(1)；空间复杂度：O(k)，k 为当前有效出价总数。
class AuctionSystem:  # LeetCode 约定的设计类

    def __init__(self):  # 构造函数，初始化两套索引
        self.items = defaultdict(SortedList)  # itemId -> 有序列表[(出价, userId)]，缺失时自动建空列表，取最大值 O(1)
        self.users = {}  # userId -> (itemId -> 出价)，用于 O(1) 查到旧出价

    def addBid(self, userId: int, itemId: int, bidAmount: int) -> None:  # 为某用户对某物品新增一次出价
        if userId not in self.users:  # 该用户是第一次出现
            self.users[userId] = {}  # 为该用户建一张「物品 -> 出价」的表
        if itemId in self.users[userId]:  # 该用户对这件物品之前已经出过价
            self.removeBid(userId, itemId)  # 先撤销旧出价，保证每人对每件物品只保留一条记录
        self.users[userId][itemId] = bidAmount  # 记录该用户对这件物品的新出价
        self.items[itemId].add((bidAmount, userId))  # 同时把 (出价, 用户) 放进该物品的有序列表

    def updateBid(self, userId: int, itemId: int, newAmount: int) -> None:  # 修改一条已有的出价
        oldAmount = self.users[userId][itemId]  # 取出旧出价，用于在有序列表中定位旧的二元组
        self.items[itemId].remove((oldAmount, userId))  # 从有序列表里删掉旧出价记录
        self.items[itemId].add((newAmount, userId))  # 插入新出价记录，有序列表会自动保持按出价有序
        self.users[userId][itemId] = newAmount  # 同步更新用户维度的出价

    def removeBid(self, userId: int, itemId: int) -> None:  # 撤销一条出价
        oldAmount = self.users[userId][itemId]  # 取出该用户对该物品的当前出价
        self.items[itemId].remove((oldAmount, userId))  # 从有序列表中删除这条出价
        self.users[userId].pop(itemId)  # 再从用户维度删除这件物品，表示该用户已无出价

    def getHighestBidder(self, itemId: int) -> int:  # 查询某件物品的最高出价者
        ls = self.items[itemId]  # 取出该物品的有序列表（缺失时 defaultdict 会自动建一个空列表）
        return -1 if not ls else ls[-1][1]  # 列表为空返回 -1，否则尾部就是最高出价，取其 userId


# Your AuctionSystem object will be instantiated and called as such:  # 下面是 LeetCode 判题器的固定调用模板
# obj = AuctionSystem()  # 创建对象
# obj.addBid(userId,itemId,bidAmount)  # 新增出价
# obj.updateBid(userId,itemId,newAmount)  # 修改出价
# obj.removeBid(userId,itemId)  # 撤销出价
# param_4 = obj.getHighestBidder(itemId)  # 查询最高出价者
