# 题目：415. 字符串相加（Add Strings）
# 思路：addStrings 从个位往前逐位相加，用 c 保存进位；subStrings 是配套的大数减法，先比较大小确定符号，再逐位相减处理借位。
# 时间复杂度：O(max(m, n))；空间复杂度：O(max(m, n))，用于存放结果字符串。
class Solution:  # LeetCode 约定的题解类
    def addStrings(self, num1: str, num2: str) -> str:  # num1、num2 是十进制数字字符串，返回它们相加后的字符串
        i, j = len(num1) - 1, len(num2) - 1  # i、j 分别指向两个字符串的最低位（末尾字符）
        ans = []  # ans 用列表逆序累积每一位结果（列表 append 比字符串拼接更高效）
        c = 0  # c 保存进位（这里只会是 0 或 1）
        while i >= 0 or j >= 0 or c:  # 只要还有位没算完、或者还有进位，就继续循环
            a = 0 if i < 0 else int(num1[i])  # 取出 num1 当前位数字，i 越界（已处理完）时按 0 处理
            b = 0 if j < 0 else int(num2[j])  # 取出 num2 当前位数字，j 越界时同样按 0 处理
            c, v = divmod(a + b + c, 10)  # divmod 一次得到新的进位 c 与当前位数字 v
            ans.append(str(v))  # 把当前位追加到结果列表
            i, j = i - 1, j - 1  # 两个指针同时向高位移动一位
        return "".join(ans[::-1])  # 结果逆序累积，切片 [::-1] 反转后拼接成字符串返回

    def subStrings(self, num1: str, num2: str) -> str:  # 大数减法：计算 num1 - num2，结果可能为负（保留负号）
        m, n = len(num1), len(num2)  # 记录两个字符串的长度，用于比较大小
        neg = m < n or (m == n and num1 < num2)  # 位数更少，或位数相同但字典序更小，都说明 num1 < num2，结果为负
        if neg:  # 结果为负，交换两个串，先按「大减小」算绝对值
            num1, num2 = num2, num1  # 交换后 num1 一定是较大的那个数
        i, j = len(num1) - 1, len(num2) - 1  # i、j 重新指向两个串的最低位
        ans = []  # ans 用列表逆序累积差的每一位
        c = 0  # c 在这里表示「借位」
        while i >= 0:  # 只要被减数还有位就继续（高位直接落下）
            c = int(num1[i]) - c - (0 if j < 0 else int(num2[j]))  # 当前位 = 被减数位 - 借位 - 减数位（j 越界按 0）
            ans.append(str((c + 10) % 10))  # (c + 10) % 10 把可能为负的结果回绕成 0~9 的一位数字
            c = 1 if c < 0 else 0  # 当前位减出了负数，说明要向高位借 1
            i, j = i - 1, j - 1  # 两个指针一起向高位移动
        while len(ans) > 1 and ans[-1] == '0':  # 去掉多余的 0；用 len(ans) > 1 保证结果为 0 时仍保留一位
            ans.pop()  # 弹出当前最高位的那个 0
        if neg:  # 结果为负，需要补上负号
            ans.append('-')  # 追加负号，反转后它会出现在最前面
        return ''.join(ans[::-1])  # 反转得到正常的从高位到低位顺序，拼接成字符串返回
