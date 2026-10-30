# 题目：2299. 强密码检验器 II（Strong Password Checker II）
# 思路：一次遍历，用位掩码标记小写、大写、数字、特殊字符四类是否出现，同时用前一字符排除相邻重复。
# 时间复杂度：O(n)，password 只扫一遍；空间复杂度：O(1)，只用到常数个变量。
class Solution:  # LeetCode 约定的题解类
    def strongPasswordCheckerII(self, password: str) -> bool:  # password：待检验的密码字符串
        if len(password) < 8:  # 条件一：长度至少 8 位
            return False  # 长度不满足，直接返回假
        mask = 0  # 位掩码：bit0 小写、bit1 大写、bit2 数字、bit3 特殊字符
        for i, c in enumerate(password):  # 同时拿到下标 i 与字符 c，方便与前一字符比较
            if i and c == password[i - 1]:  # 条件二：i 大于 0 时与前一个字符相同即为相邻重复
                return False  # 出现相邻重复，返回假
            if c.islower():  # 小写字母
                mask |= 1  # 置上小写字母对应的 bit0
            elif c.isupper():  # 否则判断大写字母
                mask |= 2  # 置上大写字母对应的 bit1
            elif c.isdigit():  # 再判断数字
                mask |= 4  # 置上数字对应的 bit2
            else:  # 其余归为特殊字符
                mask |= 8  # 置上特殊字符对应的 bit3
        return mask == 15  # 四类齐全（15 即 0b1111）才是强密码
