# 题目：2381. 字母移位 II（Shifting Letters II）
# 思路：差分数组记录每个区间的带符号位移量，前缀和还原出每个下标的总位移，再对 26 取模环绕得到答案字符。
# 时间复杂度：O(n + m)，n 为字符串长度、m 为 shifts 长度；空间复杂度：O(n)，差分数组占 n + 1 个位置。
class Solution:  # LeetCode 约定的题解类
    def shiftingLetters(self, s: str, shifts: List[List[int]]) -> str:  # s：原字符串；shifts：每个元素是 [左端点, 右端点, 方向]
        n = len(s)  # 字符串长度，后续下标以此为界
        d = [0] * (n + 1)  # 差分数组，多留一位给右端点 +1 处的撤销操作
        for i, j, v in shifts:  # 逐个拆出三元素操作：区间左端、右端、方向
            if v == 0:  # 方向 0 表示向前移位
                v = -1  # 改写成 -1，后面统一按带符号位移量相加
            d[i] += v  # 区间起点处累加位移量
            d[j + 1] -= v  # 区间终点后一位减去位移量，使前缀和只影响 [i, j]
        for i in range(1, n + 1):  # 从左到右做前缀和
            d[i] += d[i - 1]  # 此时 d[i] 就是第 i 个字符的累计位移量
        return ''.join(  # 把每个字符的移位结果拼接成一个字符串返回
            chr(ord('a') + (ord(s[i]) - ord('a') + d[i] + 26) % 26) for i in range(n)  # 字母序号加位移后对 26 取模（+26 兼容负位移），再转回字符
        )
