# 题目：1067. 范围内的数字计数（Digit Count in Range）
# 思路：数位 DP，f(n) 统计 d 在 [0, n] 的十进制表示中出现多少次，答案用前缀和相减 f(high) - f(low - 1)。
# 时间复杂度：O(位数 × 计数 × 10)，记忆化后状态数为 O(位数²)；空间复杂度：O(位数²)。
class Solution:  # LeetCode 约定的题解类
    def digitsCount(self, d: int, low: int, high: int) -> int:  # d：目标数字；[low, high]：统计区间，返回区间内 d 出现的总次数
        return self.f(high, d) - self.f(low - 1, d)  # 前缀和差分：[0, high] 的次数减去 [0, low-1] 的次数

    def f(self, n, d):  # 统计 d 在 [0, n] 所有数字的十进制表示中出现的总次数
        @cache  # 记忆化装饰器，缓存 dfs(pos, cnt, lead, limit) 的结果，避免重复搜索
        def dfs(pos, cnt, lead, limit):  # pos：当前填到第几位；cnt：已确定部分中 d 的个数；lead：是否全是前导零；limit：是否贴着上界
            if pos <= 0:  # 所有位都填完，累计值就是这一支路的贡献
                return cnt  # 返回该支路中 d 的个数
            up = a[pos] if limit else 9  # 贴上界时当前位最大只能取 a[pos]，否则可以取到 9
            ans = 0  # 累计当前状态下的总贡献
            for i in range(up + 1):  # 枚举当前位可填的数字
                if i == 0 and lead:  # 仍是前导零：这个 0 不构成数字的一部分，不能计入
                    ans += dfs(pos - 1, cnt, lead, limit and i == up)  # 保持前导零标记继续下一位，计数不变
                else:  # 已经进入有效数字位
                    ans += dfs(pos - 1, cnt + (i == d), False, limit and i == up)  # 填的就是 d 则计数加一，解除前导零标记；只有与上界前缀相同 limit 才继续为真
            return ans  # 返回本状态的总贡献

        a = [0] * 11  # a[1..l] 从低位到高位保存 n 的每一位数字
        l = 0  # 当前拆出的位数
        while n:  # 逐位拆解 n
            l += 1  # 位数加一
            a[l] = n % 10  # 取最低位，从 a[1] 开始存放
            n //= 10  # 去掉已经拆出的最低位
        return dfs(l, 0, True, True)  # 从最高位开始深搜：已计 0 个、处于前导零状态、贴着上界
