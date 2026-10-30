# 题目：3043. 最长公共前缀的长度（Find the Length of the Longest Common Prefix）
# 核心思路：先把 arr1 每个数的所有十进制前缀放进集合，再对 arr2 每个数从长到短查集合，记录数值最大的公共前缀，其位数即答案。
# 时间复杂度：O((n + m) * log10 V)，每个数只按位数枚举；空间复杂度：O(n * log10 V)，保存 arr1 的全部前缀。
class Solution:
    def longestCommonPrefix(self, arr1: List[int], arr2: List[int]) -> int:  # arr1、arr2：两个正整数数组，返回它们任意元素之间最长的公共十进制前缀长度
        s = set()  # 集合 s：保存 arr1 中每个数的所有十进制前缀（含数字本身）
        for x in arr1:  # 枚举 arr1 中的每个数
            while x:  # x 变为 0 时结束，正好覆盖所有非空前缀
                s.add(x)  # 把当前前缀加入集合，重复元素由集合去重
                x //= 10  # 整除 10 去掉末位，得到更短的前缀
        mx = 0  # mx：两个数组公共前缀中数值最大的那个
        for x in arr2:  # 枚举 arr2 中的每个数
            while x:  # 同样从长到短枚举当前数的前缀
                if x in s:  # 一旦命中 arr1 的前缀集合，就得到当前数的最长公共前缀
                    mx = max(mx, x)  # 数值越大前缀越长，用 max 保留更优解
                    break  # 已经取到最长公共前缀，无需继续缩短
                x //= 10  # 去掉末位，尝试更短的前缀
        return len(str(mx)) if mx else 0  # 有公共前缀时它的十进制位数就是答案，否则答案为 0
