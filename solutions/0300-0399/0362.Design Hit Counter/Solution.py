# 题目：362. 敲击计数器（Design Hit Counter）
# 思路：按时间顺序保存所有敲击时间戳，查询时用二分找到窗口左端位置，总长度减去该位置即窗口内敲击数。
# 时间复杂度：hit 均摊 O(1)，getHits O(log n)；空间复杂度：O(n)，保存全部时间戳。
class HitCounter:  # 敲击计数器类

    def __init__(self):  # 构造函数
        self.ts = []  # 按时间顺序保存所有敲击的时间戳

    def hit(self, timestamp: int) -> None:  # 记录一次敲击
        self.ts.append(timestamp)  # 追加时间戳（题目保证单调递增）

    def getHits(self, timestamp: int) -> int:  # 统计最近 300 秒的敲击数
        return len(self.ts) - bisect_left(self.ts, timestamp - 300 + 1)  # 二分定位窗口左端，总长度减去左端下标即窗口内数量


# 下面是 LeetCode 判题器自动生成的调用示例（代码本体已在上面结束）
# Your HitCounter object will be instantiated and called as such:
# obj = HitCounter()
# obj.hit(timestamp)
# param_2 = obj.getHits(timestamp)  # 调用示例结束
