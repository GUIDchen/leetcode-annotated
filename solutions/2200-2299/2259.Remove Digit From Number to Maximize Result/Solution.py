# 题目：2259. 移除指定数字得到的最大结果（Remove Digit From Number to Maximize Result）
# 思路：枚举每个等于 digit 的下标，删掉该字符生成候选串，用 max 取字典序最大者（等长串的字典序即数值大小）。
# 时间复杂度：O(n^2)，每次切片拼接与比较都是 O(n)；空间复杂度：O(n)，生成器逐个产出候选串。
class Solution:  # LeetCode 约定的题解类
    def removeDigit(self, number: str, digit: str) -> str:  # number：数字串；digit：必须删掉一位的那个数字字符
        return max(  # 在所有合法候选中取字典序最大者，即数值最大的结果
            number[:i] + number[i + 1 :] for i, d in enumerate(number) if d == digit  # 生成器：对每个等于 digit 的下标 i，拼出删掉该位后的字符串
        )  # 结束 max 调用，返回最优结果
