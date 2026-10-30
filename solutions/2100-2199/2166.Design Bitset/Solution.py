# 题目：2166. 设计位集（Design Bitset）
# 思路：同时维护正向列表 a 与取反列表 b，并记录 a 中 '1' 的个数；flip 时交换两个列表并把计数改成 size - cnt。
# 时间复杂度：除 toString 为 O(n) 外各操作均 O(1)；空间复杂度：O(n)，两个等长列表。
class Bitset:  # 位集类，需实现 fix/unfix/flip/all/one/count/toString
    def __init__(self, size: int):  # 构造：size 是位集长度
        self.a = ['0'] * size  # 正向表示，初始全为 '0'
        self.b = ['1'] * size  # 取反表示，初始全为 '1'
        self.cnt = 0  # 正向表示中 '1' 的个数

    def fix(self, idx: int) -> None:  # 把第 idx 位置为 '1'
        if self.a[idx] == '0':  # 当前是 '0' 才需要改计数，否则会重复累加
            self.a[idx] = '1'  # 把该位改成 '1'
            self.cnt += 1  # 计数加一
        self.b[idx] = '0'  # 取反表示里该位相应地变成 '0'

    def unfix(self, idx: int) -> None:  # 把第 idx 位置为 '0'
        if self.a[idx] == '1':  # 当前是 '1' 才需要改计数，否则会重复相减
            self.a[idx] = '0'  # 把该位改成 '0'
            self.cnt -= 1  # 计数减一
        self.b[idx] = '1'  # 取反表示里该位相应地变成 '1'

    def flip(self) -> None:  # 整体翻转所有位
        self.a, self.b = self.b, self.a  # 交换正反两个列表，等价于逐位取反且不需要遍历
        self.cnt = len(self.a) - self.cnt  # 翻转后 '1' 的个数变成总长度减去原来的个数

    def all(self) -> bool:  # 判断是否全为 '1'
        return self.cnt == len(self.a)  # 1 的个数等于长度就说明全为 1

    def one(self) -> bool:  # 判断是否至少有一个 '1'
        return self.cnt > 0  # 计数大于 0 即存在 1

    def count(self) -> int:  # 返回 '1' 的个数
        return self.cnt  # 直接返回维护好的计数

    def toString(self) -> str:  # 把当前位集转成字符串
        return ''.join(self.a)  # join 把字符列表拼成字符串，顺序与下标一致


# 下面这段是 LeetCode 判题器要求的对象创建与调用示例注释，原样保留
# Your Bitset object will be instantiated and called as such:
# obj = Bitset(size)
# obj.fix(idx)
# obj.unfix(idx)
# obj.flip()
# param_4 = obj.all()
# param_5 = obj.one()
# param_6 = obj.count()
# param_7 = obj.toString()
