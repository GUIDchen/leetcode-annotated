# 题目：3337. 字符串转换后的长度 II（Total Characters in String After Transformations II）
# 思路：用 26×26 转移矩阵描述「字母 i 一步能变成哪些字母」，矩阵快速幂求 t 步后的矩阵，再让初始计数行向量右乘它，各分量求和即答案。
# 时间复杂度：O(26^3 log t)，26 为常数；空间复杂度：O(26^2)。
class Solution:  # LeetCode 约定的题解类
    def lengthAfterTransformations(self, s: str, t: int, nums: List[int]) -> int:  # s 是原字符串，t 是变换次数，nums[i] 是字母 i 一次能扩展出的字母个数
        mod = 10**9 + 7  # 取模常量，防止方案数过大
        m = 26  # 字母表大小，也是转移矩阵的维度

        cnt = [0] * m  # cnt[c] 统计字母 c 当前的出现次数
        for c in s:  # 遍历原字符串的每个字符
            cnt[ord(c) - ord("a")] += 1  # ord(c) - ord("a") 把字符映射到 0..25 的下标后自增计数

        matrix = [[0] * m for _ in range(m)]  # 构造转移矩阵：matrix[i][j] = 1 表示字母 i 一步能变成字母 j
        for i, x in enumerate(nums):  # 枚举起始字母 i 与它的扩展个数 x
            for j in range(1, x + 1):  # 字母 i 能变成它后面的第 1..x 个字母（超出 z 会回绕）
                matrix[i][(i + j) % m] = 1  # (i + j) % 26 循环映射回 0..25，标记这条转移边

        def matmul(a: List[List[int]], b: List[List[int]]) -> List[List[int]]:  # 内层辅助函数：朴素矩阵乘法，结果逐项取模
            n, p, q = len(a), len(b), len(b[0])  # 结果矩阵是 n×q，中间维是 p
            res = [[0] * q for _ in range(n)]  # 结果矩阵初始化为全 0
            for i in range(n):  # 枚举结果矩阵的行 i
                for k in range(p):  # 枚举中间维 k，即 a 的列号 / b 的行号
                    if a[i][k]:  # 稀疏剪枝：系数为 0 时整项贡献为 0，跳过内层循环
                        for j in range(q):  # 枚举结果矩阵的列 j
                            res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % mod  # 累加乘积后立刻取模；Python 大整数不会溢出
            return res  # 返回乘积矩阵

        def matpow(mat: List[List[int]], power: int) -> List[List[int]]:  # 内层辅助函数：矩阵快速幂，求 mat 的 power 次方
            res = [[int(i == j) for j in range(m)] for i in range(m)]  # 单位矩阵：对角为 1、其余为 0，相当于幂运算的初值 1
            while power:  # 二进制拆分指数，逐位处理
                if power % 2:  # 当前最低位为 1，说明这一位对应的幂要乘进结果
                    res = matmul(res, mat)  # 结果乘以当前的底数
                mat = matmul(mat, mat)  # 底数自乘，对应指数翻倍
                power //= 2  # 指数右移一位（整除 2）
            return res  # 返回幂矩阵

        cnt = [cnt]  # 把一维计数列表包装成 1×26 的矩阵，方便复用 matmul
        factor = matpow(matrix, t)  # t 步的总转移矩阵
        result = matmul(cnt, factor)[0]  # 行向量右乘转移矩阵，取第 0 行即 t 步后各字母的数量

        ans = sum(result) % mod  # 所有字母数量求和再取模，就是变换后字符串的长度
        return ans  # 返回答案
