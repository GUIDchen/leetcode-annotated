# 题目：1146. 快照数组（Snapshot Array）
# 思路：每个下标维护一条按快照号递增的「(快照号, 值)」记录，set 只追加记录，get 用二分找到不超过 snap_id 的最后一条修改。
# 时间复杂度：set 为 O(1)，snap 为 O(1)，get 为 O(log L)（L 为该下标的修改次数）；空间复杂度：O(修改总次数)。
class SnapshotArray:  # 每个下标保存一条按快照号递增的修改记录

    def __init__(self, length: int):  # 构造函数：length 是数组长度
        self.arr = [[] for _ in range(length)]  # 为每个下标准备一个空的记录列表
        self.i = 0  # 当前快照号，从 0 开始

    def set(self, index: int, val: int) -> None:  # 把 index 位置的值设为 val
        self.arr[index].append((self.i, val))  # 追加 (当前快照号, 值) 记录，保留历史版本

    def snap(self) -> int:  # 拍一次快照，返回快照编号
        self.i += 1  # 快照号先自增
        return self.i - 1  # 再返回自增前的编号

    def get(self, index: int, snap_id: int) -> int:  # 查询 index 在快照 snap_id 时的值
        i = bisect_left(self.arr[index], (snap_id, inf)) - 1  # 二分定位第一条快照号 >= snap_id 的记录，它前一条才是该快照真正生效的修改
        return 0 if i < 0 else self.arr[index][i][1]  # 没有更早的修改就返回 0，否则取那条记录的值


# Your SnapshotArray object will be instantiated and called as such:
# obj = SnapshotArray(length)
# obj.set(index,val)
# param_2 = obj.snap()
# param_3 = obj.get(index,snap_id)
