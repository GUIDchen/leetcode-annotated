# 题目：788. 旋转数字（Rotated Digits）
# 思路：用映射表 d 做 180° 旋转；逐位把 x 旋转拼成 y，遇到 3/4/7 立即失败，最后只统计 y != x 的数。
# 时间复杂度：O(n log n)，每个数要处理它的每位数字；空间复杂度：O(1)，只有定长表与常数个变量。
class Solution:  # LeetCode 约定的题解类
    def rotatedDigits(self, n: int) -> int:  # 统计 [1, n] 中旋转 180° 后仍合法且与原数不同的个数
        def check(x):  # 判断单个数字 x 是否为好数的内部函数
            y, t = 0, x  # y 存旋转结果，t 是待逐位剥离的剩余部分
            k = 1  # k 是当前位的位权，从个位的 1 开始
            while t:  # 从低位到高位逐位处理
                v = t % 10  # 取最低位数字
                if d[v] == -1:  # 该位旋转后不合法（3、4、7）
                    return False  # 整个数作废，直接返回 False
                y = d[v] * k + y  # 把旋转后的数字按原位权拼进 y
                k *= 10  # 位权升一档
                t //= 10  # 去掉最低位（整除，保持整数类型）
            return x != y  # 旋转后与原数不同才是好数

        d = [0, 1, 5, -1, -1, 2, 9, -1, 8, 6]  # d[i] 是数字 i 旋转后的值，-1 表示不合法
        return sum(check(i) for i in range(1, n + 1))  # check 返回 bool 参与求和，True 计 1、False 计 0，即好数总数
