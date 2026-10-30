# 题目：604. 迭代压缩字符串（Design Compressed String Iterator）
# 思路：初始化时把压缩串解析成 [字符, 次数] 的二维列表，next 时消耗当前段的次数，次数归零就把指针移到下一段。
# 时间复杂度：构造 O(L)、next/hasNext O(1)；空间复杂度：O(k)，k 是压缩串中的字符段数。
class StringIterator:  # 压缩字符串迭代器类
    def __init__(self, compressedString: str):  # 构造函数：解析形如 a2b3 的压缩串
        self.d = []  # 预解析结果，每项是 [字符, 剩余次数]
        self.p = 0  # 当前正在消耗的段下标
        n = len(compressedString)  # 压缩串长度，作为扫描边界
        i = 0  # 扫描下标，从串首开始
        while i < n:  # 每轮解析一段「字母 + 若干位数字」
            c = compressedString[i]  # 当前位置的字母就是这一段的字符
            x = 0  # 重复次数，先清零再逐位累加
            i += 1  # 先跳过字符本身，指向紧随其后的数字
            while i < n and compressedString[i].isdigit():  # 继续读取属于同一段的所有数字字符
                x = x * 10 + int(compressedString[i])  # 按十进制拼接，兼容多位数的重复次数
                i += 1  # 处理下一个数字位
            self.d.append([c, x])  # 把这一段解析结果存进列表

    def next(self) -> str:  # 取出下一个字符，并消耗一次计数
        if not self.hasNext():  # 已经没有剩余字符时不能继续迭代
            return ' '  # 按题目约定返回一个空格
        ans = self.d[self.p][0]  # 先记下当前段的字符，作为本次返回值
        self.d[self.p][1] -= 1  # 该字符的剩余次数减一
        if self.d[self.p][1] == 0:  # 次数用光，需要切换到下一段
            self.p += 1  # 指针后移
        return ans  # 返回取到的字符

    def hasNext(self) -> bool:  # 判断迭代器是否还能返回字符
        return self.p < len(self.d) and self.d[self.p][1] > 0  # 指针未越界且当前段仍有剩余次数才算还有字符


# Your StringIterator object will be instantiated and called as such:
# obj = StringIterator(compressedString)
# param_1 = obj.next()
# param_2 = obj.hasNext()
