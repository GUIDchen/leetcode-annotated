# 题目：2843. 统计对称整数的数目（Count Symmetric Integers）
# 思路：把每个数转成字符串，位数为偶数时比较前一半与后一半的数字和是否相等，用生成器表达式累加计数。
# 时间复杂度：O((high - low) * log high)，逐个检查区间内的数；空间复杂度：O(log high)，用于保存字符串与切片。
class Solution:  # LeetCode 约定的题解类
    def countSymmetricIntegers(self, low: int, high: int) -> int:  # low / high：闭区间上下界，统计其中对称整数的个数
        def f(x: int) -> bool:  # 内部函数 f：判断单个整数 x 是否对称
            s = str(x)  # 转成十进制字符串，方便按位取数
            if len(s) & 1:  # 位数为奇数时无法平分两半，必然不对称
                return False  # 直接判为不对称
            n = len(s) // 2  # 每一半的长度
            return sum(map(int, s[:n])) == sum(map(int, s[n:]))  # 前半段数字和与后半段数字和相等即对称

        return sum(f(x) for x in range(low, high + 1))  # 枚举区间内每个整数，统计对称整数的个数
