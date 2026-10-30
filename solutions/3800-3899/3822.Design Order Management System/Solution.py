# 3822. Design Order Management System | 3822. 设计订单管理系统
# 核心思路：字典记录每单的 (类型, 价格)，再用 (类型, 价格) -> 订单列表 的字典索引支持按价位查询
# 复杂度：addOrder / getOrdersAtPrice 均摊 O(1)，modifyOrder / cancelOrder 为同价位列表线性 O(L)
class OrderManagementSystem:  # 订单管理系统：按订单类型与价格维护订单，并支持按价位查询

    def __init__(self):  # 构造函数：初始化订单表与价位索引
        self.orders = {}  # orderId -> (订单类型, 价格)
        self.t = defaultdict(list)  # (类型, 价格) -> 该价位的订单 id 列表（按加入先后顺序）

    def addOrder(self, orderId: int, orderType: str, price: int) -> None:  # 新增订单
        self.orders[orderId] = (orderType, price)  # 记录订单的类型与价格
        self.t[(orderType, price)].append(orderId)  # 把订单 id 追加到对应价位的列表尾部

    def modifyOrder(self, orderId: int, newPrice: int) -> None:  # 修改订单价格为 newPrice
        orderType, price = self.orders[orderId]  # 取出该订单的类型与旧价格
        self.orders[orderId] = (orderType, newPrice)  # 把订单表里的价格更新为新价格
        self.t[(orderType, price)].remove(orderId)  # 从旧价位列表中删除该订单 id
        self.t[(orderType, newPrice)].append(orderId)  # 追加到新价位的订单列表尾部

    def cancelOrder(self, orderId: int) -> None:  # 取消订单
        orderType, price = self.orders[orderId]  # 取出该订单的类型与价格
        del self.orders[orderId]  # 从订单表中删除该订单
        self.t[(orderType, price)].remove(orderId)  # 从该价位列表中删除该订单 id

    def getOrdersAtPrice(self, orderType: str, price: int) -> List[int]:  # 查询某类型某价格下的所有订单 id
        return self.t[(orderType, price)]  # 返回该价位的订单 id 列表


# Your OrderManagementSystem object will be instantiated and called as such:
# obj = OrderManagementSystem()
# obj.addOrder(orderId,orderType,price)
# obj.modifyOrder(orderId,newPrice)
# obj.cancelOrder(orderId)
# param_4 = obj.getOrdersAtPrice(orderType,price)
