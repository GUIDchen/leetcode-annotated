# 题目：937. 重新排列日志文件（Reorder Data in Log Files）
# 思路：给每条日志构造排序键。字母日志用 (0, 内容, 标识符)，数字日志用 (1,)，元组比较天然实现「字母在前、内容优先、稳定保序」。
# 时间复杂度：O(n log n * L)，每次比较都要比较长度为 L 的内容；空间复杂度：O(n)，排序后的新列表。
class Solution:  # LeetCode 约定的题解类
    def reorderLogFiles(self, logs: List[str]) -> List[str]:  # logs 是若干条日志，返回重排后的日志数组
        def f(log: str):  # 排序键函数：为一条日志生成可比较的元组
            id_, rest = log.split(" ", 1)  # 只按第一个空格切一次，得到标识符与内容两部分
            return (0, rest, id_) if rest[0].isalpha() else (1,)  # 字母日志键为 (0, 内容, 标识符)；数字日志键为 (1,)，彼此相等，sorted 稳定所以保持原顺序

        return sorted(logs, key=f)  # sorted 是稳定排序，数字日志之间的相对顺序因此不变
