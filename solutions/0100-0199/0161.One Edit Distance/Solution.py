# 题目：161. 相隔为 1 的编辑距离（One Edit Distance）
# 思路：保证 s 不短于 t；长度差超过 1 直接 False；找到第一个不同位置后，按「替换」或「删除」两种情形比较剩余部分是否相同。
# 时间复杂度：O(n)，只扫描到第一个不同位置（切片比较会再耗 O(n)）；空间复杂度：O(n)，切片产生新字符串。
class Solution:  # LeetCode 约定的题解类
    def isOneEditDistance(self, s: str, t: str) -> bool:  # s、t：两个字符串；判断能否恰好通过一次编辑互相转换
        if len(s) < len(t):  # 若 s 比 t 短就交换参数，保证下面只需处理 s 不短于 t 的情形
            return self.isOneEditDistance(t, s)  # 递归调用自己完成交换
        m, n = len(s), len(t)  # m、n 分别为两串长度
        if m - n > 1:  # 长度差大于 1，一次编辑无法弥补
            return False  # 直接判定为 False
        for i, c in enumerate(t):  # 遍历较短串 t 的每个位置，寻找第一处不同
            if c != s[i]:  # 找到第一个不同的字符
                return s[i + 1 :] == t[i + 1 :] if m == n else s[i + 1 :] == t[i:]  # 等长时比较替换后的剩余后缀；s 长一个字符时跳过 s 的当前位置再比较剩余部分
        return m == n + 1  # 扫描结束
