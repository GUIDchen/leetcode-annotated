# 题目：2564. 子字符串异或查询（Substring XOR Queries）
# 核心思路：预处理 s 中所有长度不超过 32 的二进制子串，用字典记录「数值 → 首次出现的区间」；查询时把 first ^ second 当键直接查表。
# 时间复杂度：O(32n + q)，n 为字符串长度、q 为查询数；空间复杂度：O(32n)，字典最多保存这么多个不同数值。
class Solution:  # LeetCode 约定的题解类
    def substringXorQueries(self, s: str, queries: List[List[int]]) -> List[List[int]]:  # s：二进制字符串；queries：若干 [first, second]
        d = {}  # 字典：键是子串的二进制数值，值是首次出现时的 [左下标, 右下标]
        n = len(s)  # 字符串长度
        for i in range(n):  # 枚举子串左端点 i
            x = 0  # 从空串开始累积数值
            for j in range(32):  # 子串长度上限 32 位，避免超出 int 范围
                if i + j >= n:  # 右端点越界，本行没有更长的子串了
                    break  # 结束内层循环
                x = x << 1 | int(s[i + j])  # 左移一位后把当前字符的 0/1 拼到最低位
                if x not in d:  # 只保留第一次出现，即该数值最短的区间
                    d[x] = [i, i + j]  # 记录区间左右端点
                if x == 0:  # 值为 0 时继续追加前导 0 仍是 0，无需再扩展
                    break  # 提前结束内层循环
        return [d.get(first ^ second, [-1, -1]) for first, second in queries]  # 逐个查询：命中则给区间，否则给默认值 [-1, -1]
