# 题目：3270. 求出数字答案（Find the Key of the Numbers）
# 思路：把三个数都视作补足前导零的四位数，逐位取三者在同一位置上的数字最小值，再按位权拼回四位答案。
# 时间复杂度：O(1)（固定处理 4 位）；空间复杂度：O(1)。
class Solution:  # LeetCode 约定的题解类
    def generateKey(self, num1: int, num2: int, num3: int) -> int:  # num1、num2、num3：三个四位数（不足四位视为带前导零）；返回按位取最小值得到的四位答案
        ans, k = 0, 1  # ans：拼接中的答案；k：当前位的位权，从个位的 1 开始
        for _ in range(4):  # 固定处理四位：k 依次为 1、10、100、1000
            x = min(num1 // k % 10, num2 // k % 10, num3 // k % 10)  # x：三个数在当前位上的数字的最小值（不足四位的高位按 0 处理）
            ans += x * k  # 把该位的最小数字乘上位权累加进答案
            k *= 10  # 位权进到高一位
        return ans  # 返回拼好的四位答案
