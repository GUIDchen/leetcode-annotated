# 题目：1603. 设计停车系统（Design Parking System）
# 思路：self.cnt[carType] 直接记录该类车位的剩余数量，取车时判断非零再减一。
# 时间复杂度：构造与 addCar 均为 O(1)；空间复杂度：O(1)，只占 4 个元素。
class ParkingSystem:  # 设计题要实现的类
    def __init__(self, big: int, medium: int, small: int):  # 构造函数：big/medium/small 是三种车位的初始数量
        self.cnt = [0, big, medium, small]  # 下标 0 留作占位，1/2/3 分别对应大/中/小车位，便于用 carType 直接索引

    def addCar(self, carType: int) -> bool:  # 停车：carType 取 1/2/3
        if self.cnt[carType] == 0:  # 该类型车位已停满
            return False  # 停车失败
        self.cnt[carType] -= 1  # 占用一个车位，剩余数量减一
        return True  # 停车成功


# Your ParkingSystem object will be instantiated and called as such:
# obj = ParkingSystem(big, medium, small)
# param_1 = obj.addCar(carType)
