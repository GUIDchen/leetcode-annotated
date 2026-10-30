# 题目：1357. 每隔 n 个顾客打折（Apply Discount Every n Orders）
# 思路：用字典建立「商品编号 → 单价」的映射，并用计数器对 n 取模判断当前顾客是否为第 n 位，是则按折扣比例减免。
# 时间复杂度：构造函数 O(m)，getBill 为 O(k)（k 为本次购买的商品种数）；空间复杂度：O(m)。
class Cashier:  # 收银台类：跨次调用保存顾客计数与商品价格表

    def __init__(self, n: int, discount: int, products: List[int], prices: List[int]):  # 构造函数：初始化计数器并建立价格表
        self.i = 0  # 已接待顾客数对 n 取模后的值
        self.n = n  # 折扣周期：每 n 位顾客打一次折
        self.discount = discount  # 折扣百分比
        self.d = {a: b for a, b in zip(products, prices)}  # 用 zip 把商品编号与单价配对，建立字典

    def getBill(self, product: List[int], amount: List[int]) -> float:  # 计算本次账单：product 是商品编号列表，amount 是对应数量列表
        self.i = (self.i + 1) % self.n  # 顾客序号自增；为 0 说明这位顾客正好是第 n 位，可享折扣
        x = sum(self.d[a] * b for a, b in zip(product, amount))  # 用生成器表达式累加 单价 × 数量，得到未打折总额
        if self.i == 0:  # 本顾客是第 n 位，需要打折
            return x - (self.discount * x) / 100  # Python 的 / 是浮点除法，正好得到折后价
        return x  # 不打折，原价返回


# Your Cashier object will be instantiated and called as such:  # 下面是 LeetCode 判题器给出的调用示例，属于模板注释，原样保留
# obj = Cashier(n, discount, products, prices)
# param_1 = obj.getBill(product,amount)
