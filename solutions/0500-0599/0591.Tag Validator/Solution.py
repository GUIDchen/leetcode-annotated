# 题目：591. 标签验证器（Tag Validator）
# 思路：用栈模拟解析：遇到 <![CDATA[ 整段跳过，遇到 </ 就校验并弹出栈顶同名标签，遇到 < 就校验标签名并入栈；最后要求栈空。
# 时间复杂度：O(n)，每次 find 都只向前推进；空间复杂度：O(n)，栈最深为嵌套标签层数。
class Solution:  # LeetCode 约定的题解类
    def isValid(self, code: str) -> bool:  # code 是待验证的代码片段
        def check(tag):  # 校验标签名：1~9 位且全部是大写字母
            return 1 <= len(tag) <= 9 and all(c.isupper() for c in tag)  # 两个条件必须同时满足

        stk = []  # 栈里存放尚未闭合的标签名
        i, n = 0, len(code)  # i 是当前扫描位置，n 是字符串总长度
        while i < n:  # 从左到右扫描整个字符串
            if i and not stk:  # 首个标签之后栈已空，说明根标签提前闭合
                return False  # 根标签之外不允许还有其他内容
            if code[i : i + 9] == '<![CDATA[':  # 进入 CDATA 段，段内内容不需要转义
                i = code.find(']]>', i + 9)  # 直接跳到 CDATA 的结束标记 ]]> 处
                if i < 0:  # 找不到结束标记
                    return False  # CDATA 没有闭合，非法
                i += 2  # 循环末尾还要 +1，这里补 2 正好让 i 停在 '>' 上
            elif code[i : i + 2] == '</':  # 以 </ 开头的是结束标签
                j = i + 2  # 标签名起点
                i = code.find('>', j)  # 找到结束尖括号
                if i < 0:  # 没有 '>'
                    return False  # 标签没有闭合
                t = code[j:i]  # 取出标签名
                if not check(t) or not stk or stk.pop() != t:  # 短路求值：名字非法或栈空时不会执行 pop；三者任一不满足都失败
                    return False  # 匹配失败，直接返回 False
            elif code[i] == '<':  # 以 < 开头的是开始标签
                j = i + 1  # 标签名起点
                i = code.find('>', j)  # 找结束尖括号
                if i < 0:  # 没有 '>'
                    return False  # 标签没有闭合
                t = code[j:i]  # 取出标签名
                if not check(t):  # 名字格式不合法
                    return False  # 直接失败
                stk.append(t)  # 合法则入栈，等待后续闭合
            i += 1  # 移动到下一个字符（CDATA 与标签分支已跳到 '>' 上）
        return not stk  # 扫描结束，栈空说明所有标签都正确闭合
