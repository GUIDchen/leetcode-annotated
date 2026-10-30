# 题目：273. 整数转换英文表示（Integer to English Words）
# 思路：从高位到低位每 3 位一组，用 transfer 递归拼出组内英文，再按组拼上 Billion/Million/Thousand 单位，最后去首尾空格。
# 时间复杂度：O(1)，整数最多 10 位、分 4 组；空间复杂度：O(1)，只用到几张常量表与结果列表。
class Solution:  # LeetCode 约定的题解类
    def numberToWords(self, num: int) -> str:  # num：待转换的非负整数
        if num == 0:  # 0 是需要特判的唯一情况
            return 'Zero'  # 直接返回单词 Zero

        lt20 = [  # 0~19 的英文单词表，下标就是数字本身
            '',
            'One',
            'Two',
            'Three',
            'Four',
            'Five',
            'Six',
            'Seven',
            'Eight',
            'Nine',
            'Ten',
            'Eleven',
            'Twelve',
            'Thirteen',
            'Fourteen',
            'Fifteen',
            'Sixteen',
            'Seventeen',
            'Eighteen',
            'Nineteen',
        ]  # 表结束：共 20 项
        tens = [  # 十位单词表，下标是十位上的数字
            '',
            'Ten',
            'Twenty',
            'Thirty',
            'Forty',
            'Fifty',
            'Sixty',
            'Seventy',
            'Eighty',
            'Ninety',
        ]  # 十位表结束
        thousands = ['Billion', 'Million', 'Thousand', '']  # 每 3 位一组的单位名，依次对应 10^9、10^6、10^3、个位

        def transfer(num):  # 内层函数：把 0~999 的数转成英文（每组末尾带一个空格）
            if num == 0:  # 0 返回空串，避免多出单词
                return ''  # 返回空串
            if num < 20:  # 20 以内直接查表
                return lt20[num] + ' '  # 单词后补空格，方便外层直接拼接
            if num < 100:  # 100 以内：十位单词 + 个位递归
                return tens[num // 10] + ' ' + transfer(num % 10)  # 拼接十位与个位
            return lt20[num // 100] + ' Hundred ' + transfer(num % 100)  # 百位以上：百位单词 + Hundred + 余下两位递归

        res = []  # 结果片段列表，最后统一拼接
        i, j = 1000000000, 0  # i：当前组权值，从 10^9 起；j：当前组对应的单位下标
        while i > 0:  # 从高位到低位逐组处理
            if num // i != 0:  # 这一组非 0 才输出
                res.append(transfer(num // i))  # 转换这 3 位
                res.append(thousands[j])  # 拼上单位名（个位组是空串）
                res.append(' ')  # 补一个分隔空格
                num %= i  # 去掉已经处理过的高位
            j += 1  # 下一组单位
            i //= 1000  # 权值缩小 1000 倍
        return ''.join(res).strip()  # 拼接所有片段并去掉首尾空格
