# 题目：359. 日志速率限制器（Logger Rate Limiter）
# 思路：字典保存每条消息「下一次允许打印的时间戳」，新消息到来时与当前时间戳比较，未到解禁时间就拒绝。
# 时间复杂度：O(1) 均摊，字典查询；空间复杂度：O(m)，m 为不同消息条数。
class Logger:  # 日志速率限制器类

    def __init__(self):  # 构造函数
        self.ts = {}  # 字典：消息 → 下次允许打印的时间戳

    def shouldPrintMessage(self, timestamp: int, message: str) -> bool:  # 判断某条日志在当前时间戳能否打印
        t = self.ts.get(message, 0)  # 取该消息的解禁时间，没记录过就当 0
        if t > timestamp:  # 解禁时间还没到，说明 10 秒内重复
            return False  # 不允许打印
        self.ts[message] = timestamp + 10  # 更新解禁时间为当前时间 + 10
        return True  # 允许打印


# 下面是 LeetCode 判题器自动生成的调用示例（代码本体已在上面结束）
# Your Logger object will be instantiated and called as such:
# obj = Logger()
# param_1 = obj.shouldPrintMessage(timestamp,message)  # 调用示例结束
