# 题目：800. 相似 RGB 颜色（Similar RGB Color）
# 思路：每个两位十六进制分量要换成 aa 形式（值 = 17a），把所有候选 17a 与原值比较，等价于对分量值除以 17 取最近的倍数：余数超过 8 就向上进位。
# 时间复杂度：O(1)，只处理 3 个分量；空间复杂度：O(1)，只用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def similarRGB(self, color: str) -> str:  # color：形如 "#RRGGBB" 的十六进制颜色串
        def f(x):  # f(x)：把一个两位十六进制分量替换成最接近的 aa 形式
            y, z = divmod(int(x, 16), 17)  # 17 = 0x11：商 y 是向下取整的候选序号，余数 z 用于判断是否进位
            if z > 8:  # 余数超过 8 说明上一个候选更近，需要进位
                y += 1  # 进位成 y+1
            return '{:02x}'.format(17 * y)  # 17*y 就是 0xaa 形式的值，格式化成两位小写十六进制

        a, b, c = color[1:3], color[3:5], color[5:7]  # 拆出 R、G、B 三个两位分量
        return f'#{f(a)}{f(b)}{f(c)}'  # 三段分别取最近色后拼回带 # 的颜色串
