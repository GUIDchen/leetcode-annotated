# 题目：1656. 设计有序流（Design an Ordered Stream）
# 思路：用数组按 idKey 直接存 value，ptr 始终指向下一个应该输出的位置；每次插入后只要 ptr 处非空就连续输出并后移。
# 时间复杂度：每次 insert 均摊 O(1)，每个元素只输出一次；空间复杂度：O(n)，数组长度 n+1。
class OrderedStream:  # 有序流类
    def __init__(self, n: int):  # 构造函数：n 为流的总长度
        self.ptr = 1  # 指针从 1 开始（idKey 是 1-based）
        self.data = [None] * (n + 1)  # n+1 个槽位，下标 0 空置

    def insert(self, idKey: int, value: str) -> List[str]:  # 插入 (idKey, value)，返回本次能按序输出的片段
        self.data[idKey] = value  # 按 idKey 直接落位
        ans = []  # 存放本次连续输出的结果
        while self.ptr < len(self.data) and self.data[self.ptr]:  # ptr 不越界且对应位置有值时可继续输出
            ans.append(self.data[self.ptr])  # 追加该值
            self.ptr += 1  # 指针后移一位
        return ans  # 返回这段有序结果


# 下面是 LeetCode 判题器自带的调用示例注释，原样保留
# Your OrderedStream object will be instantiated and called as such:
# obj = OrderedStream(n)
# param_1 = obj.insert(idKey,value)
