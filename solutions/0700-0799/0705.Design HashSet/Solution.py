# 题目：705. 设计哈希集合（Design HashSet）
# 思路：键的取值范围是 0 到 1000000，直接用定长布尔列表做桶，下标即键，True 表示存在，用空间换时间。
# 时间复杂度：add / remove / contains 均为 O(1)；空间复杂度：O(C)，C = 1000001 个布尔槽位。
class MyHashSet:  # 自定义哈希集合类
    def __init__(self):  # 构造函数：把列表全部置为 False，得到空集合
        self.data = [False] * 1000001  # 下标就是键，值表示该键是否存在于集合中

    def add(self, key: int) -> None:  # 加入 key
        self.data[key] = True  # 按下标置 True，重复加入也安全，天然去重

    def remove(self, key: int) -> None:  # 删除 key
        self.data[key] = False  # 按下标置 False，键本来不存在时也无副作用

    def contains(self, key: int) -> bool:  # 查询 key 是否在集合中
        return self.data[key]  # 返回该下标上的布尔值


# Your MyHashSet object will be instantiated and called as such:
# obj = MyHashSet()
# obj.add(key)
# obj.remove(key)
# param_3 = obj.contains(key)
