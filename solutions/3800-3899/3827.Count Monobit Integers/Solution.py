# 3827. Count Monobit Integers | 3827. 统计单比特整数
# 核心思路：单比特数是二进制各位全相同者（0 或全为 1，即 0、1、3、7、15…），逐个累加直到超过 n 并计数
# 复杂度：时间 O(log n)，空间 O(1)
class Solution:
    def countMonobit(self, n: int) -> int:  # 统计 [0, n] 内二进制各位全相同的整数个数
        ans = x = 1  # ans 先把 0 计入；x 为当前的全 1 整数，从 1 开始
        i = 1  # 下一个全 1 整数需要补的 1 所在位数
        while x <= n:  # 只要当前全 1 整数不超过 n 就继续枚举
            ans += 1  # 计入答案
            x += 1 << i  # 下一个全 1 整数：在二进制末尾再补一个 1
            i += 1  # 补的位数加一
        return ans  # 返回统计个数
