# 题目：1352. 最后 K 个数的乘积（Product of the Last K Numbers）
# 思路：维护「以最后一次清零为起点」的前缀乘积数组，查询最后 k 个数的乘积时用两次前缀乘积相除还原区间积；遇到 0 就把数组重置为 [1]。
# 时间复杂度：add 与 getProduct 均摊都是 O(1)；空间复杂度：O(n)，n 为两次 0 之间加入的元素个数。
class ProductOfNumbers:  # 设计题：用一个类同时维护数据流和前缀乘积
    def __init__(self):  # 构造函数：初始化内部的前缀乘积数组
        self.s = [1]  # 先放一个哨兵 1，使得第一个元素也能用「相除」的方式取区间乘积

    def add(self, num: int) -> None:  # 向数据流末尾追加一个数 num
        if num == 0:  # 遇到 0 时，任何跨过它的区间乘积都会变成 0，历史前缀全部失效
            self.s = [1]  # 重置前缀乘积数组，重新开始统计（同时保留哨兵 1）
            return  # 本次 add 处理完毕，直接返回
        self.s.append(self.s[-1] * num)  # 非 0：继续累乘前缀，s[i] = a[0] * a[1] * ... * a[i]

    def getProduct(self, k: int) -> int:  # 查询最后 k 个数的乘积
        return 0 if len(self.s) <= k else self.s[-1] // self.s[-k - 1]  # 元素不足 k 个说明中间出现过 0，返回 0；否则用前缀相除得到区间积（// 保证结果是整数）


# Your ProductOfNumbers object will be instantiated and called as such:
# obj = ProductOfNumbers()
# obj.add(num)
# param_2 = obj.getProduct(k)
