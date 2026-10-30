# 题目：738. 单调递增的数字（Monotone Increasing Digits）
# 思路：从高位找第一处下降，把下降位置的前一位减一（并向前连锁处理相等的情况），其后的所有位统一改成 9。
# 时间复杂度：O(log n)，只扫描数字的位数；空间复杂度：O(log n)，保存数字的字符列表。
class Solution:  # LeetCode 约定的题解类
    def monotoneIncreasingDigits(self, n: int) -> int:  # n：待转换的整数，返回不超过 n 的最大单调递增数
        s = list(str(n))  # 把数字拆成字符列表，方便按下标修改某一位
        i = 1  # 从第二位开始寻找第一处下降
        while i < len(s) and s[i - 1] <= s[i]:  # 只要仍然非递减就继续右移
            i += 1  # 指针右移一位
        if i < len(s):  # 存在下降位置时才需要调整（否则原数本身就单调）
            while i and s[i - 1] > s[i]:  # 从下降位置向前回溯：前一位大于当前位就要借位
                s[i - 1] = str(int(s[i - 1]) - 1)  # 把前一位数字减一（转成 int 计算再转回字符串）
                i -= 1  # 指针前移，继续检查前面的位
            i += 1  # 回溯结束后 i 指向被减一位的下一位
            while i < len(s):  # 把这之后的所有位都填成 9 才能取到最大值
                s[i] = '9'  # 该位改成字符 '9'
                i += 1  # 指针右移一位
        return int(''.join(s))  # 拼回字符串再转成整数作为答案
