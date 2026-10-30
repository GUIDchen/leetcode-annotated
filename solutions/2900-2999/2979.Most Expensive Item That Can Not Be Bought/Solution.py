# 题目：2979. 最贵的无法购买的商品（Most Expensive Item That Can Not Be Bought）
# 思路：麦乐鸡定理（Frobenius 数）：两个互质正整数 a、b 不能表示成的最大整数为 a*b-a-b；题目保证二者是质数即互质，直接套公式。
# 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def mostExpensiveItem(self, primeOne: int, primeTwo: int) -> int:  # primeOne、primeTwo 为两个不同的质数
        return primeOne * primeTwo - primeOne - primeTwo  # 由麦乐鸡定理直接返回最大不可购买的价格 a*b-a-b
