# 题目：2080. 区间内查询数字的频率（Range Frequency Queries）
# 思路：预处理把每个值出现的下标按顺序存进字典；查询时对该值的下标列表做两次二分，差值就是区间内的出现次数。
# 时间复杂度：构造函数 O(n)，每次查询 O(log n)；空间复杂度：O(n)，字典里存下所有下标。
class RangeFreqQuery:  # 设计类：预处理 + 二分查询

    def __init__(self, arr: List[int]):  # 构造函数：arr 为初始数组，预处理一次以支持多次查询
        self.g = defaultdict(list)  # 字典：值 -> 该值出现的下标列表，缺失的键自动得到空列表
        for i, x in enumerate(arr):  # 同时取得下标 i 与值 x
            self.g[x].append(i)  # 追加下标，天然保持升序

    def query(self, left: int, right: int, value: int) -> int:  # 查询 value 在闭区间 [left, right] 中的出现次数
        idx = self.g[value]  # 取出该值的有序下标列表
        l = bisect_left(idx, left)  # 第一个 >= left 的位置
        r = bisect_left(idx, right + 1)  # 第一个 >= right+1 的位置，也就是第一个 > right 的位置
        return r - l  # 两位置之差即区间内的出现次数


# 下面是判题器创建对象并调用方法的示例，属于题面说明，不是需要提交的代码
# Your RangeFreqQuery object will be instantiated and called as such:
# obj = RangeFreqQuery(arr)
# param_1 = obj.query(left,right,value)
