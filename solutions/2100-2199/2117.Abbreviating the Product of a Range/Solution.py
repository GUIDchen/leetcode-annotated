# 题目：2117. 一个区间内所有数乘积的缩写（Abbreviating the Product of a Range）
# 思路：乘积写成 m * 10^c，c 由因子 2 与 5 的较小个数决定；后缀取模保低位，前缀用浮点只留约 5 位有效数字。
# 时间复杂度：O((right-left+1) * log right)，每个数剥离因子开销很小；空间复杂度：O(1)。
class Solution:# LeetCode 约定的题解类
    def abbreviateProduct(self, left: int, right: int) -> str:# left..right 闭区间；返回缩写后的乘积字符串
        cnt2 = cnt5 = 0# 分别统计乘积中因子 2 与因子 5 的个数
        for x in range(left, right + 1):# 第一遍：扫描区间内的每个数
            while x % 2 == 0:# 反复除以 2，统计因子 2
                cnt2 += 1# 因子 2 计数加一
                x //= 2# 整除去掉一个因子 2
            while x % 5 == 0:# 反复除以 5，统计因子 5
                cnt5 += 1# 因子 5 计数加一
                x //= 5# 整除去掉一个因子 5
        c = cnt2 = cnt5 = min(cnt2, cnt5)# 每个 2 和 5 配成一个 10，c 就是末尾 0 的个数
        pre = suf = 1# pre 用浮点数维护前缀，suf 用取模维护后缀
        gt = False# 标记乘积是否超过 10 位、需要缩写
        for x in range(left, right + 1):# 第二遍：真正累乘，同时剥离 10 的因子
            suf *= x# 后缀乘上当前数
            while cnt2 and suf % 2 == 0:# 按配额从 suf 中剥离因子 2
                suf //= 2# 去掉一个因子 2
                cnt2 -= 1# 可用配额减一
            while cnt5 and suf % 5 == 0:# 按配额从 suf 中剥离因子 5
                suf //= 5# 去掉一个因子 5
                cnt5 -= 1# 可用配额减一
            if suf >= 1e10:# 后缀已经超过 10 位
                gt = True# 标记结果很长，需要省略中间部分
                suf %= int(1e10)# 只保留末尾 10 位，防止整数无限增大
            pre *= x# 前缀累乘当前数
            while pre > 1e5:# 前缀只需保留约 5 位有效数字
                pre /= 10# 不断缩小量级，这点精度损失可以忽略
        if gt:# 乘积太长，输出「前 5 位...后 5 位e指数」
            return str(int(pre)) + "..." + str(suf % int(1e5)).zfill(5) + "e" + str(c)# 前 5 位直接取整，后 5 位用 zfill 补足前导 0
        return str(suf) + "e" + str(c)# 乘积不长，直接输出后缀与 10 的指数
