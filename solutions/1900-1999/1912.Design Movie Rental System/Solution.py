# 题目：1912. 设计电影租借系统（Design Movie Rental System）
# 思路：按电影用 SortedList 保存未租出的 (price, shop)，再用一个全局 SortedList 保存已租出的 (price, shop, movie)；search 与 report 直接切片取前 5。
# 时间复杂度：构造 O(n log n)，search/rent/drop 为 O(log n)，report 为 O(1) 切片；空间复杂度：O(n)，需要保存全部条目与租借记录。
class MovieRentingSystem:  # 电影租借系统类

    def __init__(self, n: int, entries: List[List[int]]):  # n：商店数量（本实现不需要使用）；entries：每项为 [shop, movie, price]
        self.available = defaultdict(lambda: SortedList())  # available[movie] 是该片当前可租的 (price, shop) 有序列表，缺省时自动创建空 SortedList
        self.price_map = {}  # price_map：键是 (shop, movie) 编码后的整数，值为租金，rent/drop 时据此反查价格
        for shop, movie, price in entries:  # 逐条建立索引，同时取出商店、电影、价格
            self.available[movie].add((price, shop))  # 在该电影的可租列表中登记 (价格, 商店)，SortedList 自动保持升序
            self.price_map[self.f(shop, movie)] = price  # 记录这部片在该店的租金
        self.rented = SortedList()  # rented：全局已租记录 (price, shop, movie) 的有序列表

    def search(self, movie: int) -> List[int]:  # 查询某部电影最便宜的 5 家可租商店
        return [shop for _, shop in self.available[movie][:5]]  # 切片取前 5 个 (price, shop)，只保留商店编号

    def rent(self, shop: int, movie: int) -> None:  # 租借：把该片从某店的可租列表移到已租列表
        price = self.price_map[self.f(shop, movie)]  # 查出租金，作为两个列表排序的第一关键字
        self.available[movie].remove((price, shop))  # 从该电影的可租列表中删掉这条记录
        self.rented.add((price, shop, movie))  # 加入全局已租列表

    def drop(self, shop: int, movie: int) -> None:  # 归还：把记录从已租列表移回可租列表
        price = self.price_map[self.f(shop, movie)]  # 同样先查出这条记录的租金
        self.rented.remove((price, shop, movie))  # 从已租列表中删除该记录
        self.available[movie].add((price, shop))  # 重新放回该电影的可租列表

    def report(self) -> List[List[int]]:  # 报表：返回租金最低的 5 条已租记录 [shop, movie]
        return [[shop, movie] for _, shop, movie in self.rented[:5]]  # 已租列表按 (price, shop, movie) 升序，取前 5 条并整理成 [shop, movie]

    def f(self, shop: int, movie: int) -> int:  # 把 (商店编号, 电影编号) 压缩成一个整数键，便于查价
        return shop << 30 | movie  # 商店编号左移 30 位后与电影编号按位或，两者位段互不重叠


# Your MovieRentingSystem object will be instantiated and called as such:
# obj = MovieRentingSystem(n, entries)
# param_1 = obj.search(movie)
# obj.rent(shop,movie)
# obj.drop(shop,movie)
# param_4 = obj.report()
