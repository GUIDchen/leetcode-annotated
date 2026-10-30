# 题目：1390. 四因数（Four Divisors）
# 思路：内层辅助函数 f 试除到 sqrt(x)，把成对的因数同时计入个数与和，只有恰好 4 个因数时才返回和；外层把所有 f(x) 累加。
# 时间复杂度：O(n * sqrt(max(nums)))，每个数枚举到平方根；空间复杂度：O(1)，只使用常数个变量。
class Solution:  # LeetCode 约定的题解类
    def sumFourDivisors(self, nums: List[int]) -> int:  # nums 是待统计的数组
        def f(x: int) -> int:  # 内部辅助函数：求 x 的因数之和，仅当因数个数恰为 4 时有效
            i = 2  # 试除的因子从 2 开始
            cnt, s = 2, x + 1  # 1 和 x 本身已是两个因数，先把个数记为 2、和记为 x + 1
            while i <= x // i:  # 只枚举到 sqrt(x)，用整除 x // i 比较可避免浮点误差
                if x % i == 0:  # i 能整除 x，说明 i 是一个因数
                    cnt += 1  # 因数个数加一
                    s += i  # 累加较小的因数 i
                    if i * i != x:  # 配对因数 x // i 与 i 不同，即 x 不是完全平方数
                        cnt += 1  # 另一个因数个数也要加一
                        s += x // i  # 累加较大的因数 x // i
                i += 1  # 继续尝试下一个因子
            return s if cnt == 4 else 0  # 恰好 4 个因数就返回和，否则这个数不合格返回 0

        return sum(f(x) for x in nums)  # 对所有数分别求四因数之和，再用 sum 累加返回
