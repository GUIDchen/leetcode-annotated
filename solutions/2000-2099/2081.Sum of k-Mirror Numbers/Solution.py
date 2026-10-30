# 题目：2081. k 镜像数字的和（Sum of k-Mirror Numbers）
# 思路：按十进制回文数位数 l 递增枚举，用前半部分 i 拼出十进制回文数 v，再判断 v 在 k 进制下是否回文，凑满 n 个求和。
# 时间复杂度：约 O(10^(l/2) * log_k(v))，只需枚举到第 n 个答案出现；空间复杂度：O(log_k(x))，用于存放 k 进制各位。
class Solution:  # LeetCode 约定的题解类
    def kMirror(self, k: int, n: int) -> int:  # k 是进制，n 是需要收集的 k 镜像数个数，返回它们的和
        def check(x: int, k: int) -> bool:  # 内嵌函数：判断十进制数 x 在 k 进制下是否回文
            s = []  # s 用来存放 x 的 k 进制各位，低位在前
            while x:  # 不断取模，把 x 转成 k 进制
                s.append(x % k)  # 取出当前最低位并存入列表
                x //= k  # 整除去掉最低位
            return s == s[::-1]  # 正序与逆序完全相同即为回文（此时 x 已为 0）

        ans = 0  # 累加和，Python 整数无溢出，不必特殊处理
        for l in count(1):  # l 是十进制回文数的位数，count(1) 提供无限递增序列
            x = 10 ** ((l - 1) // 2)  # l 位回文数前半部分的下界
            y = 10 ** ((l + 1) // 2)  # l 位回文数前半部分的上界（开区间）
            for i in range(x, y):  # 枚举该位数下所有可能的「前半部分」
                v = i  # v 由前半部分 i 开始，待拼接成完整回文数
                j = i if l % 2 == 0 else i // 10  # 偶数位整体镜像；奇数位要丢掉末位后再镜像
                while j > 0:  # 把前半部分的低位逐位反序拼到末尾
                    v = v * 10 + j % 10  # 追加最低位
                    j //= 10  # 整除去掉已用过的位
                if check(v, k):  # v 在 k 进制下也是回文
                    ans += v  # 计入答案
                    n -= 1  # 还需收集的个数减一
                    if n == 0:  # 凑满 n 个就结束
                        return ans  # 返回前 n 个 k 镜像数字之和
