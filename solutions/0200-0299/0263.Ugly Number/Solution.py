# 题目：263. 丑数（Ugly Number）
# 思路：依次把 n 里的因子 2、3、5 除干净，最终剩 1 即丑数。
# 时间复杂度：O(log n)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def isUgly(self, n: int) -> bool:  # n 为待判断的整数，返回它是否为丑数
        if n < 1:  # 非正数按约定不是丑数
            return False  # 直接返回 False
        for x in [2, 3, 5]:  # 依次处理 2、3、5 这三个允许的质因子
            while n % x == 0:  # 只要还能整除，就一直除下去
                n //= x  # 用整除消掉一个因子
        return n == 1  # 除尽后若只剩 1，说明不含其它质因子
