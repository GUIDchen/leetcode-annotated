# 题目：3704. 统计和为 N 的无零数对（Count No-Zero Pairs That Sum to N）
# 核心思路：按十进制位从低到高做数位 DP，状态为 (进位, A 是否还有位, B 是否还有位)；每一位上 A、B 各自可选 1..9 的任意数字（数字中不允许出现 0），或选 0 表示这个数到此结束；要求 da + db + 进位 的个位等于 N 的当前位，最高位处理完后要求无进位且两数都已结束。
# 复杂度：时间 O(log n)，位数 L 层、每层常数个状态与 10x10 的数字组合；空间 O(1)，只开两个 2x2x2 的滚动数组。
class Solution:  # LeetCode 约定的题解类
    def countNoZeroPairs(self, n: int) -> int:  # 返回满足 a + b = n 且 a、b 的十进制表示都不含 0 的正整数对个数
        trivanople = n  # 先把参数另存一份，后面按它的十进制写法逐位处理
        digits = list(map(int, str(trivanople)))[::-1]  # 逐位拆成数字并翻转，变为从低位到高位
        digits.append(0)  # absorb final carry  # 追加一位 0，用来吸收最高位可能产生的进位
        L = len(digits)  # 需要处理的位数（比 N 的实际位数多一位）

        # dp[carry][aliveA][aliveB]  # 状态含义：进位、A 是否还有位、B 是否还有位
        dp = [[[0] * 2 for _ in range(2)] for _ in range(2)]  # 三维 DP 表，全部初始化为 0
        dp[0][1][1] = 1  # 最低位开始前没有进位，A、B 都还在构造中，共 1 种

        for pos in range(L):  # 从低到高逐位处理
            ndp = [[[0] * 2 for _ in range(2)] for _ in range(2)]  # 新一层 DP 表先全部清零
            target = digits[pos]  # 这一位要让 a、b 数字之和（含进位）的个位等于 target
            for carry in range(2):  # 枚举进入这一位时的进位
                for aliveA in range(2):  # 枚举 A 是否还有位待填
                    for aliveB in range(2):  # 枚举 B 是否还有位待填
                        ways = dp[carry][aliveA][aliveB]  # 取出到达该状态的方案数
                        if ways == 0:  # 该状态不可达
                            continue  # 直接跳过

                        if aliveA:  # A 还没结束，这一位必须继续填数
                            A = [(d, 1) for d in range(1, 10)]  # 无零数不能含 0，只能选 1..9 且填完后 A 仍有效
                            if pos > 0:  # 除最低位外，允许用 0 来结束这个数
                                A.append((0, 0))  # end number here  # 选 0 表示 A 到此为止
                        else:  # A 已经结束，这一位只能补 0 占位
                            A = [(0, 0)]  # 已结束的数高位补 0，并保持已结束状态

                        if aliveB:  # B 还没结束，这一位必须继续填数
                            B = [(d, 1) for d in range(1, 10)]  # 无零数不能含 0，只能选 1..9 且填完后 B 仍有效
                            if pos > 0:  # 除最低位外，允许用 0 来结束这个数
                                B.append((0, 0))  # 选 0 表示 B 到此为止
                        else:  # B 已经结束，这一位只能补 0 占位
                            B = [(0, 0)]  # 已结束的数高位补 0，并保持已结束状态

                        for da, na in A:  # 枚举 A 在这一位的每一种选法
                            for db, nb in B:  # 枚举 B 在这一位的每一种选法
                                s = da + db + carry  # 这一位两数之和再加上进位
                                if s % 10 != target:  # 个位必须等于 N 的当前位
                                    continue  # 不相等则该组合不合法
                                ndp[s // 10][na][nb] += ways  # 把方案数累加到新状态
            dp = ndp  # 用新一层 DP 覆盖旧一层，进入下一位

        return dp[0][0][0]  # 要求最终无进位且 A、B 都已结束，即为所求对数

    def countPairs(self, n: int) -> int:  # 与题面同名的入口方法
        return self.countNoZeroPairs(n)  # 直接复用数位 DP 的实现
