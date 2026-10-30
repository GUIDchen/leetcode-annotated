# 题目：402. 移掉 K 位数字（Remove K Digits）
# 思路：单调栈 + 贪心。边扫描边把比当前位更大的栈顶弹掉，让高位尽量小；最后按保留位数截取并去掉前导 0。
# 时间复杂度：O(n)，每个字符最多入栈出栈各一次；空间复杂度：O(n)，栈最多存 n 个字符。
class Solution:  # LeetCode 约定的题解类
    def removeKdigits(self, num: str, k: int) -> str:  # 从数字字符串 num 中删掉 k 个字符，使剩下的数字最小
        stk = []  # 用列表当单调栈，保证栈内数字不降
        remain = len(num) - k  # 提前算好最终要保留的位数（因为下面循环里 k 会被递减）
        for c in num:  # 从左到右逐位扫描
            while k and stk and stk[-1] > c:  # 还能删、栈非空且栈顶更大时，弹掉栈顶让高位变小
                stk.pop()  # 弹出比当前位大的栈顶
                k -= 1  # 消耗一次删除名额
            stk.append(c)  # 当前位入栈
        return ''.join(stk[:remain]).lstrip('0') or '0'  # 只取前 remain 位，去掉前导 0；结果为空串时按题目要求返回 '0'
