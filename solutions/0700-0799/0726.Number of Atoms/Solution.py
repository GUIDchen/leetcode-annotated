# 题目：726. 原子的数量（Number of Atoms）
# 思路：从右往左扫描，先读到数字再读到元素名；遇到 ')' 把当前乘数压栈并乘以括号后的数字，遇到 '(' 出栈恢复外层乘数。
# 时间复杂度：O(n + E log E)，n 为化学式长度，E 为元素种数；空间复杂度：O(E)，哈希表与栈的开销。
class Solution:  # LeetCode 约定的题解类
    def countOfAtoms(self, formula: str) -> str:  # formula：化学式字符串
        cnt = defaultdict(int)  # 记录每个元素的原子总数（缺省 0）
        stack = []  # 栈：保存每一层括号外的乘数
        multiplier, freq = 1, 0  # multiplier 为当前层乘数；freq 为刚读到的数字（0 表示没写数字）
        i = len(formula) - 1  # 从右往左扫描的起始下标
        while i >= 0:  # 反向遍历化学式
            c = formula[i]  # 当前字符
            if c.islower():  # 小写字母：属于前面元素名的一部分
                end = i  # 记录元素名右端
                i -= 1  # 跳过右端字符，继续向左找首字母
                while i >= 0 and formula[i].islower():  # 继续吞掉前面的小写字母
                    i -= 1  # 指针左移
                cnt[formula[i : end + 1]] += max(freq, 1) * multiplier  # 元素名 = formula[i:end+1]；没写数字时按 1 计，再乘当前层乘数
                freq = 0  # 数字已消费，清零
            elif c.isupper():  # 大写字母：单字母元素名
                cnt[c] += max(freq, 1) * multiplier  # 累加个数（缺省为 1），再乘当前层乘数
                freq = 0  # 数字已消费，清零
            elif c.isdigit():  # 数字：反向解析出完整数值
                freq = ord(c) - 48  # 先取个位（48 即字符 0 的编码）
                p = 10  # 下一位的权重
                while i - 1 >= 0 and formula[i - 1].isdigit():  # 前面还是数字，继续拼高位
                    i -= 1  # 指针先左移
                    freq += p * (ord(formula[i]) - 48)  # 按权重累加
                    p *= 10  # 权重乘以 10
            elif c == ')':  # 右括号：进入新的一层
                stack.append(multiplier)  # 先把外层乘数压栈
                multiplier *= max(freq, 1)  # 内层乘数 = 外层乘数 * 括号后的数字（缺省为 1）
                freq = 0  # 数字已消费，清零
            else:  # 剩下只可能是左括号，表示这一层结束
                multiplier = stack.pop()  # 恢复外层乘数
            i -= 1  # 处理下一个字符
        ans = []  # 结果片段列表
        for key in sorted(cnt):  # 按元素名字典序遍历
            ans.append(key)  # 先追加元素名
            if cnt[key] > 1:  # 个数为 1 时按题意省略数字
                ans.append(str(cnt[key]))  # 追加个数
        return ''.join(ans)  # 拼接成最终字符串
