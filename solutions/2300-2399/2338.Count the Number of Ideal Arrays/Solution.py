# 题目：2338. 统计理想数组的数目（Count the Number of Ideal Arrays）
# 核心思路：把理想数组压缩成「相邻不同值构成的整除链」，链上每个值可重复多次；f[i][j] 统计长度为 j、以 i 结尾的整除链条数，再用组合数 C(n-1, j-1) 把 j 个不同值放回 n 个位置，累加即为答案。
# 时间复杂度：O(n*16 + 15*maxValue*log(maxValue))；空间复杂度：O(n*16 + maxValue*16)。
class Solution:  # LeetCode 约定的题解类
    def idealArrays(self, n: int, maxValue: int) -> int:  # n：数组长度；maxValue：元素取值上限；返回值是理想数组个数取模
        c = [[0] * 16 for _ in range(n)]  # c[i][j] 存组合数 C(i, j)；整除链最长约 15，故 16 列足够
        mod = 10**9 + 7  # 取模常量，避免计数溢出
        for i in range(n):  # 逐行递推杨辉三角
            for j in range(min(16, i + 1)):  # 列 j 不超过 i，同时不超过 16 列的上限
                c[i][j] = 1 if j == 0 else (c[i - 1][j] + c[i - 1][j - 1]) % mod  # 边界 C(i,0)=1，其余用 C(i-1,j)+C(i-1,j-1) 递推并取模
        f = [[0] * 16 for _ in range(maxValue + 1)]  # f[i][j]：长度为 j、以数值 i 结尾的整除链条数
        for i in range(1, maxValue + 1):  # 初始化长度为 1 的链
            f[i][1] = 1  # 任何值自己单独成链，条数为 1
        for j in range(1, 15):  # 按链长度 j 从小到大递推，最长链约 14
            for i in range(1, maxValue + 1):  # 枚举链当前的末尾值 i
                k = 2  # 倍数 k 从 2 开始枚举，保证下一个值严格更大
                while k * i <= maxValue:  # k*i 不超过上限时，它可以作为链的下一个值
                    f[k * i][j + 1] = (f[k * i][j + 1] + f[i][j]) % mod  # 把以 i 结尾、长度为 j 的链延伸为以 k*i 结尾、长度为 j+1 的链
                    k += 1  # 倍数加一，继续尝试下一个倍数
        ans = 0  # ans 累加所有理想数组的个数
        for i in range(1, maxValue + 1):  # 枚举压缩后整除链的最后一个值
            for j in range(1, 16):  # 枚举链中不同值的个数 j（即链长度）
                ans = (ans + f[i][j] * c[-1][j - 1]) % mod  # 链有 j 个不同值，用 c[-1][j-1] 即 C(n-1, j-1) 种方式放回 n 个位置
        return ans  # 返回答案（已对 1e9+7 取模）
