# 3869. 统计区间内奇妙数的数目 / Count Fancy Numbers in a Range
# 核心思路：区间计数转为前缀差 count(r) - count(l-1)，用数位 DP 同时枚举数位与数位和；状态 st 记录单调性（0 前导零 / 1 严格增 / 2 严格减 / 3 已破坏），数位本身单调即好数，否则再判断数位和是否为好数。
# 复杂度：时间复杂度 O(位数 × 数位和 × 10 × 4)（记忆化状态数），空间复杂度 O(位数 × 数位和 × 10 × 4)。
class Solution:  # LeetCode 题解类
    def countFancy(self, l: int, r: int) -> int:  # 返回闭区间 [l, r] 内奇妙数的个数
        def check(s: int) -> bool:  # 判断数位和 s 本身是否为好数
            if s < 100:  # 一位数或两位数
                return s % 11 != 0  # 一位数恒为好数；两位数两数码不同（严格增或严格减）等价于不是 11 的倍数
            return 1 < s // 10 % 10 < s % 10  # 三位数：百位恒为 1，严格递增即 1 < 十位 < 个位，不存在严格递减

        @cache  # 记忆化装饰器，自动缓存递归结果
        def dfs(pos: int, s: int, prev: int, st: int, lim: bool) -> int:  # 数位 DP：位次、数位和、前一位、单调性状态、是否贴上限
            if pos >= len(num):  # 所有数位都已填完
                if st != 3:  # 数位严格单调（含只有一位的情形）
                    return 1  # 本身即好数，计 1
                return int(check(s))  # 数位不单调，退化为判断数位和是否为好数
            up = int(num[pos]) if lim else 9  # 当前位可填的最大数字
            res = 0  # 当前状态下的方案数
            for i in range(up + 1):  # 枚举当前位填入的数字
                nxt_st = st  # 下一状态先继承当前状态
                if st == 0:  # 之前全是前导零
                    if prev == 0:  # 前一位仍是前导零
                        nxt_st = 0  # 继续保持前导零状态
                    elif i > prev:  # 当前位比前一位大
                        nxt_st = 1  # 转入严格递增状态
                    elif i < prev:  # 当前位比前一位小
                        nxt_st = 2  # 转入严格递减状态
                    else:  # 与前一位相等
                        nxt_st = 3  # 单调性被破坏
                elif st == 1:  # 已处于严格递增状态
                    if i > prev:  # 仍然严格递增
                        nxt_st = 1  # 保持严格递增
                    else:  # 不再递增
                        nxt_st = 3  # 单调性被破坏
                elif st == 2:  # 已处于严格递减状态
                    if i < prev:  # 仍然严格递减
                        nxt_st = 2  # 保持严格递减
                    else:  # 不再递减
                        nxt_st = 3  # 单调性被破坏
                else:  # 状态已是 3
                    nxt_st = 3  # 单调性已破坏，状态不再变化
                res += dfs(pos + 1, s + i, i, nxt_st, lim and i == up)  # 递归下一位并累加方案数
            return res  # 返回当前状态的方案数

        num = str(l - 1)  # 取上界 l-1 的十进制字符串
        a = dfs(0, 0, 0, 0, True)  # 统计 [0, l-1] 内的奇妙数个数
        dfs.cache_clear()  # 清空缓存，因为闭包里的 num 已改变
        num = str(r)  # 换成上界 r 的字符串
        b = dfs(0, 0, 0, 0, True)  # 统计 [0, r] 内的奇妙数个数
        return b - a  # 前缀计数相减得到 [l, r] 的答案
