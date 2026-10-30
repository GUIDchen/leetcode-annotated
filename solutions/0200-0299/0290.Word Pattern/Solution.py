# 题目：290. 单词规律（Word Pattern）—— 判断 s 的单词序列是否与 pattern 的字符序列一一对应。
# 核心思路：维护双向映射（字符→单词、单词→字符），逐位比对，任一方向冲突即不匹配；先比较两个序列长度。
# 时间复杂度：O(L)，L 为两个字符串总长度；空间复杂度：O(k)，k 为不同字符/单词数量。
class Solution:  # LeetCode 约定的题解类
    def wordPattern(self, pattern: str, s: str) -> bool:  # pattern：规律串；s：以空格分隔的单词串
        ws = s.split()  # split() 不传参数会按任意空白切分，并自动忽略多余空格
        if len(pattern) != len(ws):  # 字符数与单词数不同，不可能一一对应
            return False  # 直接返回不匹配
        d1 = {}  # 正向映射：字符 -> 单词
        d2 = {}  # 反向映射：单词 -> 字符，保证不同字符不会映射到同一个单词
        for a, b in zip(pattern, ws):  # zip 按位置成对遍历两个序列
            if (a in d1 and d1[a] != b) or (b in d2 and d2[b] != a):  # 任一方向已有映射且与当前位置冲突，说明不是双射
                return False  # 返回不匹配
            d1[a] = b  # 记录正向映射
            d2[b] = a  # 记录反向映射
        return True  # 全部位置匹配成功
