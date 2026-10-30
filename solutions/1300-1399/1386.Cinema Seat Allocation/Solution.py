# 题目：1386. 安排电影院座位（Cinema Seat Allocation）
# 思路：用位掩码记录每行已预定座位，没被预定的行各贡献 2 组，其余行依次尝试三种四人组合占位。
# 时间复杂度：O(n + r)，n 为预定记录数、r 为被预定过的行数；空间复杂度：O(r)，字典每行存一个掩码。
class Solution:  # LeetCode 约定的题解类
    def maxNumberOfFamilies(self, n: int, reservedSeats: List[List[int]]) -> int:  # n 为总行数
        d = defaultdict(int)  # 行号 → 已占座位的位掩码，缺省值为 0
        for i, j in reservedSeats:  # 逐条处理预定记录
            d[i] |= 1 << (10 - j)  # 座位 j 映射到第 (10-j) 位并置 1
        masks = (0b0111100000, 0b0000011110, 0b0001111000)  # 座位 2-5、6-9、4-7 三种四人组合
        ans = (n - len(d)) * 2  # 完全没有预定的行，每行可安排两组
        for x in d.values():  # 只遍历被预定过的行
            for mask in masks:  # 依次尝试三种组合
                if (x & mask) == 0:  # 该组合的四个座位都空
                    x |= mask  # 占用这四个座位，防止与后续组合冲突
                    ans += 1  # 成功安排一组
        return ans  # 返回最多可安排的家庭数量
