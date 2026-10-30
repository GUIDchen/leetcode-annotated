# 题目：3700. 锯齿形数组的总数 II（Number of ZigZag Arrays II）
# 核心思路：把每个取值拆成「下降态」和「上升态」共 2m 个状态，构造 0/1 转移矩阵，用二进制快速幂求 trans 的 n-1 次方，再乘全 1 的初始向量并把各分量求和。
# 复杂度：时间 O((2m)^3 * log n)；空间 O((2m)^2)，只存转移矩阵及其幂。
class Solution:  # LeetCode 约定的题解类
    def zigZagArrays(self, n: int, l: int, r: int) -> int:  # 返回长度 n、取值在 [l, r] 内的锯齿形数组总数
        mod = 10**9 + 7  # 结果对 1e9+7 取模
        m = r - l + 1  # 可选数字的个数，把区间 [l, r] 平移映射到 0..m-1
        size = 2 * m  # 状态数：前 m 个表示下降态，后 m 个表示上升态
        trans = [[0] * size for _ in range(size)]  # 转移矩阵，trans[新][旧] 表示旧状态能否走到新状态
        for x in range(m):  # 构造「下降态 -> 上升态」的边
            for y in range(x):  # 上一位取值 y 必须严格小于当前位取值 x
                trans[y][m + x] = 1  # 由下降态 y 转到上升态 x，方案数记 1
        for x in range(m):  # 构造「上升态 -> 下降态」的边
            for y in range(x + 1, m):  # 上一位取值 y 必须严格大于当前位取值 x
                trans[m + y][x] = 1  # 由上升态 y 转到下降态 x，方案数记 1

        def mul_mat(a, b):  # 内部函数：两个 size 阶方阵相乘
            res = [[0] * size for _ in range(size)]  # 结果方阵先全部置 0
            for i in range(size):  # 枚举结果的行
                for k in range(size):  # 枚举中间维度，i-k-j 顺序可跳过大量零元素
                    if a[i][k] == 0:  # a 的该元素为 0 时整段乘法都可跳过
                        continue  # 直接进入下一个 k
                    aik = a[i][k]  # 把公共因子提到内层循环之外
                    for j in range(size):  # 枚举结果的列
                        if b[k][j]:  # b 的该元素非 0 才有贡献
                            res[i][j] = (res[i][j] + aik * b[k][j]) % mod  # 累乘累加并取模
            return res  # 返回方阵乘积

        def mul_vec(mat, vec):  # 内部函数：方阵乘向量
            res = [0] * size  # 存放乘积向量
            for i in range(size):  # 逐行计算结果向量的第 i 个分量
                s = 0  # 第 i 个分量先清零
                for j in range(size):  # 遍历该行的每个元素做点积
                    s = (s + mat[i][j] * vec[j]) % mod  # 累加点积并随时取模防溢出
                res[i] = s  # 写回该分量
            return res  # 返回矩阵乘向量的结果

        power = [[int(i == j) for j in range(size)] for i in range(size)]  # 结果矩阵初始化为单位矩阵
        exp = n - 1  # 需要走 n-1 步转移
        while exp:  # 按二进制位从低到高处理指数
            if exp & 1:  # 当前二进制位为 1 时需要把这一份乘进结果
                power = mul_mat(power, trans)  # 累乘当前的 trans
            trans = mul_mat(trans, trans)  # trans 自乘，为下一位准备平方
            exp >>= 1  # 指数右移一位
        init = [1] * size  # 长度为 1 时每个状态各 1 种初始方案
        return sum(mul_vec(power, init)) % mod  # 求出长度 n 的各状态方案数并求和取模
