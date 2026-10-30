# 题目：166. 分数到小数（Fraction to Recurring Decimal）
# 核心思路：符号与整数部分单独处理，小数部分做长除法；用字典记录「余数 → 该位小数的下标」，余数重复出现即为循环节起点。
# 时间复杂度：O(k)，k 为不重复余数的个数（不超过分母）；空间复杂度：O(k)，字典最多保存 k 个余数。
class Solution:  # LeetCode 约定的题解类
    def fractionToDecimal(self, numerator: int, denominator: int) -> str:  # 把分数转成小数字符串
        if numerator == 0:  # 分子为 0 时结果恒为 "0"，不带负号
            return "0"  # 直接返回
        ans = []  # 用列表收集片段，最后 join，避免字符串反复拼接产生额外开销
        neg = (numerator > 0) ^ (denominator > 0)  # 异或判断符号：一正一负结果为负
        if neg:  # 结果为负数
            ans.append("-")  # 先追加负号
        a, b = abs(numerator), abs(denominator)  # 取绝对值，后续都按正数做长除法
        ans.append(str(a // b))  # 整数部分
        a %= b  # 余数作为小数部分长除法的起点
        if a == 0:  # 能整除则没有小数部分
            return "".join(ans)  # 直接拼接返回
        ans.append(".")  # 追加小数点
        d = {}  # 余数 → 该位小数在 ans 中的下标，用于定位循环节
        while a:  # 余数非 0 就持续长除
            d[a] = len(ans)  # 记录当前余数对应的位置：它再次出现时循环节从这里开始
            a *= 10  # 余数乘 10 得到这一位的被除数
            ans.append(str(a // b))  # 追加这一位的小数数字
            a %= b  # 更新余数，进入下一位
            if a in d:  # 余数重复出现，说明进入循环节
                ans.insert(d[a], "(")  # 在循环节起点插入左括号（其后元素自动右移）
                ans.append(")")  # 末尾补上右括号
                break  # 循环节已标记完毕，结束长除法
        return "".join(ans)  # 拼接成最终字符串返回
