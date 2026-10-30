# 题目：441. 排列硬币（Arranging Coins）
# 思路：铺满 k 行需要 k(k+1)/2 枚硬币，由 k(k+1)/2 = n 解出 k = (sqrt(8n+1)-1)/2；代码用等价形式 sqrt(2)*sqrt(n+0.125)-0.5，避免 8n 溢出。
# 复杂度：时间复杂度 O(1)，只做常数次浮点运算；空间复杂度 O(1)，只用常数个变量。
class Solution:  # 题解类：排列硬币
    def arrangeCoins(self, n: int) -> int:  # n 是硬币总数，返回能够完整排满的行数
        return int(math.sqrt(2) * math.sqrt(n + 0.125) - 0.5)  # 套用求根公式 sqrt(2)*sqrt(n+0.125)-0.5，int() 向下取整得到完整行数
