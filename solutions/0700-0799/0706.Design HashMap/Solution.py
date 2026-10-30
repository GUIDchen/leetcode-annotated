# 题目：706. 设计哈希映射（Design HashMap）
# 思路：键的取值范围是 0 到 1000000，直接用定长列表做桶，下标即键，值即 value，用 -1 表示键不存在。
# 时间复杂度：put / get / remove 均为 O(1)；空间复杂度：O(C)，C = 1000001 个槽位。
class MyHashMap:  # 自定义哈希映射类
    def __init__(self):  # 构造函数：把所有槽位初始化为 -1，得到空的映射
        self.data = [-1] * 1000001  # 下标是键，元素值是 value，-1 表示该键尚未插入

    def put(self, key: int, value: int) -> None:  # put：插入或更新一个键值对
        self.data[key] = value  # 直接覆盖写，键已存在时即更新其值

    def get(self, key: int) -> int:  # get：查询键对应的值
        return self.data[key]  # 未插入过的键保持 -1，正好符合题目「不存在返回 -1」的要求

    def remove(self, key: int) -> None:  # remove：删除一个键
        self.data[key] = -1  # 把值改回 -1，表示该键又变回不存在


# Your MyHashMap object will be instantiated and called as such:
# obj = MyHashMap()
# obj.put(key,value)
# param_2 = obj.get(key)
# obj.remove(key)
