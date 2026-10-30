# 题目：710. 黑名单中的随机数（Random Pick with Blacklist）
# 思路：令 k = n - |blacklist|，把 [0, k) 视作压缩后的白名单区；若其中某些位置本身在黑名单里，就用尾部 [k, n) 中的合法位置替换它们并记录映射，之后只需在 [0, k) 上均匀随机。
# 时间复杂度：构造 O(b)，b 为黑名单长度，pick 为 O(1)；空间复杂度：O(b)，字典最多保存 b 条映射。
class Solution:  # 随机取数类
    def __init__(self, n: int, blacklist: List[int]):  # 构造函数：n 是数字范围 [0, n)，blacklist 是不能选的数
        self.k = n - len(blacklist)  # 白名单区大小 k = 总数减去黑名单个数
        self.d = {}  # 映射表：落在 [0, k) 的黑名单下标 -> [k, n) 中的某个合法下标
        i = self.k  # i 从 k 开始，作为可交换的尾部位置指针
        black = set(blacklist)  # 黑名单转集合，便于 O(1) 判断某个数是否被禁用
        for b in blacklist:  # 遍历黑名单中的每个元素
            if b < self.k:  # 只处理落在白名单区 [0, k) 内的元素，它们必须被替换
                while i in black:  # 跳过同样被禁用的位置，找到第一个可用的合法位置
                    i += 1  # i 后移，继续尝试下一个位置
                self.d[b] = i  # 建立映射：原本取到 b 时改取 i
                i += 1  # i 后移，避免重复使用同一个位置

    def pick(self) -> int:  # 随机返回一个不在黑名单中的数
        x = randrange(self.k)  # 在压缩后的白名单区 [0, k) 内均匀取一个随机下标
        return self.d.get(x, x)  # 被映射过就返回替换值，否则下标本身就是白名单中的合法数


# Your Solution object will be instantiated and called as such:
# obj = Solution(n, blacklist)
# param_1 = obj.pick()
