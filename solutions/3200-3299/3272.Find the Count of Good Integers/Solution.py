# 题目：3272. 统计好整数的数目（Find the Count of Good Integers）
# 思路：只枚举回文数的前半部分拼出完整回文，先判断能否被 k 整除，再按「数字多重集」去重，用可重排列公式计数。
# 时间复杂度：O(10^(n/2) · n log n)；空间复杂度：O(10^(n/2) · n)，存放已访问的数字串。
class Solution:  # LeetCode 约定的题解类
    def countGoodIntegers(self, n: int, k: int) -> int:  # n：位数；k：要求整除的除数
        fac = [factorial(i) for i in range(n + 1)]  # 阶乘表，fac[i] = i!，用于可重排列计数
        ans = 0  # 累计答案：好整数的个数
        vis = set()  # 记录已统计过的数字多重集（排序后的字符串），避免重复计数
        base = 10 ** ((n - 1) // 2)  # 回文前半部分的最小值
        for i in range(base, base * 10):  # 枚举回文前半部分的所有取值
            s = str(i)  # 前半部分转成字符串
            s += s[::-1][n % 2 :]  # 拼接翻转后的后半部分；n 为奇数时跳过翻转串首位（中间位与前半末尾共用）
            if int(s) % k:  # 整个回文数不能被 k 整除，就不是好整数
                continue  # 直接跳过这个回文数
            t = "".join(sorted(s))  # 排序得到该回文数的数字多重集标识
            if t in vis:  # 这个数字组合已经统计过
                continue  # 跳过，保证每个多重集只计算一次，避免重复枚举
            vis.add(t)  # 标记该数字组合已处理
            cnt = Counter(t)  # 统计每个数字出现的次数
            res = (n - cnt["0"]) * fac[n - 1]  # 首位不能为 0：先选首位，再排列剩余 n-1 位
            for x in cnt.values():  # 依次除以每个数字重复次数的阶乘
                res //= fac[x]  # 可重排列公式的分母，去掉相同数字造成的重复
            ans += res  # 把该多重集能组成的好整数个数累加进答案
        return ans  # 返回好整数的总数
