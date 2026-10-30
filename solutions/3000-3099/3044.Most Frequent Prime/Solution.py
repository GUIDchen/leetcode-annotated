# 题目：3044. 出现频率最高的质数（Most Frequent Prime）
# 核心思路：以每个格子为起点沿 8 个方向不断拼接数字，用 Counter 统计所有拼出的质数，取次数最多（并列取数值最大）的质数。
# 时间复杂度：O(m * n * max(m, n) * sqrt(V))，枚举路径后还要判定质数；空间复杂度：O(m * n * max(m, n))，用于统计不同质数的次数。
class Solution:
    def mostFrequentPrime(self, mat: List[List[int]]) -> int:  # mat：数字矩阵，返回沿 8 个方向拼接出的质数中出现次数最多的那个
        def is_prime(x: int) -> int:  # 内嵌辅助函数：判断 x 是否为质数
            return all(x % i != 0 for i in range(2, isqrt(x) + 1))  # 枚举 2 到 isqrt(x) 的所有因子，全部除不尽即为质数

        m, n = len(mat), len(mat[0])  # m、n：矩阵的行数与列数，用于边界判断
        cnt = Counter()  # Counter：键是拼出的质数，值是它出现的次数
        for i in range(m):  # 枚举起点格子的行下标 i
            for j in range(n):  # 枚举起点格子的列下标 j
                for a in range(-1, 2):  # 方向行增量 a 取 -1、0、1，表示向上、不动、向下
                    for b in range(-1, 2):  # 方向列增量 b 取 -1、0、1，表示向左、不动、向右
                        if a == 0 and b == 0:  # a、b 同时为 0 表示没有移动方向
                            continue  # 跳过这个无效方向，避免原地打转
                        x, y, v = i + a, j + b, mat[i][j]  # x、y 是下一步坐标，v 是从起点开始已拼出的数字
                        while 0 <= x < m and 0 <= y < n:  # 坐标仍在矩阵内时，沿该方向不断延伸
                            v = v * 10 + mat[x][y]  # 把新格子数字接到 v 末尾，得到更长的数
                            if is_prime(v):  # 判断新拼出的数是否为质数
                                cnt[v] += 1  # 是质数则把它的出现次数加一
                            x, y = x + a, y + b  # 坐标沿当前方向推进，继续拼下一个数字
        ans, mx = -1, 0  # ans：出现次数最多的质数（-1 表示还没有质数）；mx：当前最高次数
        for v, x in cnt.items():  # 遍历统计表中的每个质数与出现次数
            if mx < x:  # 出现次数更多，直接替换答案
                mx = x  # 更新最高次数
                ans = v  # 更新对应的质数
            elif mx == x:  # 出现次数相同时，题目要求取数值更大的质数
                ans = max(ans, v)  # 用 max 在并列时保留较大值
        return ans  # 返回出现频率最高的质数，没有质数时返回 -1
