# 3959. 判定好整数 / Check Good Integer
# 核心思路：用 divmod 不断拆出 n 的十进制末位数字 x，累加每位的贡献 x * (x-1)，最后判断总和是否达到 50。
# 复杂度：时间 O(log n)（十进制位数），空间 O(1)。

class Solution:
    def checkGoodInteger(self, n: int) -> bool:  # 判断整数 n 是否为“好整数”
        s = 0  # 保存各位数字贡献的累加和
        while n:  # 只要 n 还有剩余的位就继续循环
            n, x = divmod(n, 10)  # 同时得到去掉末位后的商和末位数字 x
            s += x * (x - 1)  # 该位贡献 x * (x-1)，累加进总和
        return s >= 50  # 总和达到 50 及以上即返回 True
