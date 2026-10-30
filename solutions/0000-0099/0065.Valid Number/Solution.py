# 题目：65. 有效数字（Valid Number）
# 思路：先跳过可选正负号并排除以小数点开头且后面没有数字的情况，再逐字符扫描：小数点最多一次且不能出现在指数后，e 最多一次且两侧都要有数字。
# 时间复杂度：O(n)，一次线性扫描；空间复杂度：O(1)，只用几个计数变量。
class Solution:  # LeetCode 约定的题解类
    def isNumber(self, s: str) -> bool:  # s：待判定的字符串，判断它是否是合法十进制数（可带指数）
        n = len(s)  # 记下长度，便于判断边界
        i = 0  # 扫描起点
        if s[i] in '+-':  # 开头允许有一个正负号（题目保证 s 非空）
            i += 1  # 跳过这个符号
        if i == n:  # 只有符号没有数字
            return False  # 非法
        if s[i] == '.' and (i + 1 == n or s[i + 1] in 'eE'):  # 小数点后必须跟数字：'.' 结尾或 '.e' 都非法
            return False  # 提前判掉这种形式
        dot = e = 0  # dot 统计小数点个数，e 统计指数符号个数
        j = i  # j 从符号之后开始扫描
        while j < n:  # 逐个字符检查
            if s[j] == '.':  # 遇到小数点
                if e or dot:  # 指数里不能有小数点，且小数点只能出现一次
                    return False  # 违反规则即非法
                dot += 1  # 记下这个小数点
            elif s[j] in 'eE':  # 遇到指数符号
                if e or j == i or j == n - 1:  # 指数符号只能有一个，且前后都必须是数字
                    return False  # 不满足则非法
                e += 1  # 记下这个指数符号
                if s[j + 1] in '+-':  # 指数部分允许带符号
                    j += 1  # 先把符号位跳过
                    if j == n - 1:  # 符号后已到串尾，说明缺少指数数字
                        return False  # 非法
            elif not s[j].isnumeric():  # 既不是小数点、指数符，也不是数字字符
                return False  # 出现非法字符
            j += 1  # 继续检查下一个字符
        return True  # 全部字符都合法，返回真
