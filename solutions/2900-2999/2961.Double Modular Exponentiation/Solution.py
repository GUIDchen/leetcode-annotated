# 题目：2961. 双模幂运算（Double Modular Exponentiation）
# 思路：用列表推导遍历每个四元组，借助内置三参数 pow 做模幂，按公式 (a^b mod 10)^c mod m 与 target 比较。
# 时间复杂度：O(n * (log b + log c))，每个四元组两次快速幂；空间复杂度：O(1)，除答案列表外只用常数空间。
class Solution:  # LeetCode 约定的题解类
    def getGoodIndices(self, variables: List[List[int]], target: int) -> List[int]:  # variables 每项为 [a, b, c, m]，target 为目标值
        return [  # 用列表推导收集所有满足条件的下标
            i  # 满足条件的那一组下标 i
            for i, (a, b, c, m) in enumerate(variables)  # 遍历并解包每组参数
            if pow(pow(a, b, 10), c, m) == target  # 内置三参数 pow 即模幂运算，先 mod 10 再 mod m
        ]  # 列表推导结束
