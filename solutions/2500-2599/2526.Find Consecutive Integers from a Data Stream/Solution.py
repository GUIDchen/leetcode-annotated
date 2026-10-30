# 题目：2526. 找到数据流中的连续整数（Find Consecutive Integers from a Data Stream）
# 思路：只维护「末尾连续等于 value 的个数」cnt；新元素等于 value 就加一，否则清零。
# 时间复杂度：O(1) 每次 consec 调用；空间复杂度：O(1)，只存 val、k、cnt 三个变量。
class DataStream:  # 题目要求的 DataStream 类
    def __init__(self, value: int, k: int):  # 构造函数：value 是目标值，k 是要求的连续出现次数
        self.val, self.k = value, k  # 一行同时保存目标值与 k，放进 self 避免与参数重名冲突
        self.cnt = 0  # 连续计数初始为 0
# 空行，分隔构造与查询方法
    def consec(self, num: int) -> bool:  # 插入新数字 num，返回末尾是否至少有 k 个连续的 value
        self.cnt = 0 if num != self.val else self.cnt + 1  # 等于目标值则计数加一，否则清零（连续性被打断）
        return self.cnt >= self.k  # 计数达到 k 就说明末尾存在连续 k 个 value
# 空行，分隔类方法与判题器给的调用说明
# 判题器调用说明（以下为题目自带注释）
# Your DataStream object will be instantiated and called as such:  # 说明：对象会被这样实例化
# obj = DataStream(value, k)  # 说明：这里创建 DataStream 对象
# param_1 = obj.consec(num)  # 说明：这里调用 consec 查询
