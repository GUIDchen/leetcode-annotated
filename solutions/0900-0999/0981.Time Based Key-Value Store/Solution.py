# 题目：981. 基于时间的键值存储（Time Based Key-Value Store）
# 思路：每个 key 用列表保存按时间戳递增的 (时间戳, 值)，set 追加；get 用 bisect_right 越过 (timestamp, 最大字符) 哨兵后取前一条的值。
# 时间复杂度：set 为 O(1) 均摊，get 为 O(log n)；空间复杂度：O(n)，保存全部键值对。
class TimeMap:  # 设计题要求的 TimeMap 类
    def __init__(self):  # 构造函数
        self.ktv = defaultdict(list)  # 哈希表：键 → (时间戳, 值) 列表，缺失键自动得到空列表

    def set(self, key: str, value: str, timestamp: int) -> None:  # 记录 key 在 timestamp 时刻的值
        self.ktv[key].append((timestamp, value))  # 追加到列表尾部，题目保证同一 key 的时间戳严格递增，所以天然有序

    def get(self, key: str, timestamp: int) -> str:  # 查询 key 在 timestamp 及之前最近一次写入的值
        if key not in self.ktv:  # 该 key 从未写入过
            return ''  # 按要求返回空字符串
        tv = self.ktv[key]  # 取出该 key 的历史记录列表
        i = bisect_right(tv, (timestamp, chr(127)))  # 二分找第一个大于 (timestamp, 最大字符) 的位置，从而跳过同一时间戳的所有记录
        return tv[i - 1][1] if i else ''  # i 为 0 表示没有更早的记录，返回空串；否则返回前一条的值


# Your TimeMap object will be instantiated and called as such:
# obj = TimeMap()
# obj.set(key,value,timestamp)
# param_2 = obj.get(key,timestamp)
