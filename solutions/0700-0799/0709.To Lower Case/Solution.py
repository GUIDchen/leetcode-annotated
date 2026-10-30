# 题目：709. 转换成小写字母（To Lower Case）
# 思路：列表推导逐字符处理，遇到大写字母就用 ord / chr 做按位或 32 转小写，其余字符原样保留后拼接成字符串。
# 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(n)，需要保存结果字符列表。
class Solution:  # LeetCode 约定的题解类
    def toLowerCase(self, s: str) -> str:  # s 是输入字符串，返回它的小写形式
        return "".join([chr(ord(c) | 32) if c.isupper() else c for c in s])  # 列表推导：isupper 判断是否需要转换，ord 取编码后按位或 32 得到小写编码，再用 chr 还原成字符，最后 join 拼接
