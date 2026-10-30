# 题目：816. 模糊坐标（Ambiguous Coordinates）
# 思路：枚举逗号切点分成两段，再枚举每段内部小数点的位置，用无前导零、无尾零的规则筛选后拼接成坐标。
# 时间复杂度：O(n^3)，n 为字符串长度；空间复杂度：O(n^3)，用于存放结果。
class Solution:  # LeetCode 约定的题解类
    def ambiguousCoordinates(self, s: str) -> List[str]:  # s 形如 (123)，返回所有可能还原的坐标
        def f(i, j):  # 辅助函数：把切片 [i, j) 解析成所有合法数字串
            res = []  # 收集该区间所有写法
            for k in range(1, j - i + 1):  # k 是整数部分的长度，从 1 枚举到区间长度
                l, r = s[i : i + k], s[i + k : j]  # l 为整数部分，r 为小数部分（左闭右开切片）
                ok = (l == '0' or not l.startswith('0')) and not r.endswith('0')  # l 是单个 0 或无前导零，并且 r 不能以 0 结尾
                if ok:  # 合法才记录
                    res.append(l + ('.' if k < j - i else '') + r)  # 小数点不在末尾时插入点号
            return res  # 返回该区间的所有写法

        n = len(s)  # n 是含括号的字符串总长度
        return [  # 列表推导：枚举逗号切点以及左右两段的所有写法
            f'({x}, {y})' for i in range(2, n - 1) for x in f(1, i) for y in f(i, n - 1)  # 左右两段各自的所有合法数字串，拼成坐标形式
        ]  # 列表推导结束
