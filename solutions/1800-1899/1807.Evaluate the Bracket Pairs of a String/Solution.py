# 题目：1807. 替换字符串中的括号内容（Evaluate the Bracket Pairs of a String）
# 思路：先把 knowledge 建成哈希表，再从左到右扫描字符串；遇到括号就整段截出键名并替换，然后跳到右括号继续。
# 时间复杂度：O(n + k)，n 为字符串长度、k 为映射表规模；空间复杂度：O(k)，用于存放哈希表与结果列表。
class Solution:  # LeetCode 约定的题解类
    def evaluate(self, s: str, knowledge: List[List[str]]) -> str:  # s：待求值的字符串；knowledge：形如 [key, value] 的映射表
        d = {a: b for a, b in knowledge}  # 字典推导式：把 knowledge 的键值对直接建成哈希表
        i, n = 0, len(s)  # i 是扫描下标，n 是字符串长度
        ans = []  # 用列表收集结果片段，最后再一次性拼接，避免字符串反复相加
        while i < n:  # 只要还没扫描完就继续
            if s[i] == '(':  # 遇到左括号，说明接下来是一段待替换的键
                j = s.find(')', i + 1)  # 找到与之配对的右括号位置 j
                ans.append(d.get(s[i + 1 : j], '?'))  # 切片取出括号内的键，查表命中就取对应值，否则填一个问号
                i = j  # 跳过整个括号片段，下一轮从右括号之后继续
            else:  # 普通字符，无需替换
                ans.append(s[i])  # 原样追加到结果
            i += 1  # 下标前进一步（上面若跳到了右括号，这里才真正越过它）
        return ''.join(ans)  # 把结果片段拼成一个字符串返回
