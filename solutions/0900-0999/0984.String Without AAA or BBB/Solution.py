# 题目：984. 不含 AAA 或 BBB 的字符串（String Without AAA or BBB）
# 思路：贪心，字母多的一方每次输出两个自己夹一个对方，数量相同时输出 'ab'，从而避免出现三个连续相同字母。
# 时间复杂度：O(a+b)，与结果长度成正比；空间复杂度：O(a+b)，存储结果片段。
class Solution:  # LeetCode 约定的题解类
    def strWithout3a3b(self, a: int, b: int) -> str:  # a、b 分别是字母 'a' 与 'b' 的剩余个数
        ans = []  # 用列表收集片段，最后统一拼接更高效
        while a and b:  # 两种字母都还有剩余时成对处理
            if a > b:  # a 比 b 多
                ans.append('aab')  # 放两个 a 再夹一个 b，避免出现 aaa
                a, b = a - 2, b - 1  # 同时扣减 a 与 b 的数量
            elif a < b:  # b 比 a 多
                ans.append('bba')  # 对称处理：两个 b 夹一个 a
                a, b = a - 1, b - 2  # 同时扣减 a 与 b 的数量
            else:  # a 与 b 一样多
                ans.append('ab')  # 各放一个，交替出现不会违规
                a, b = a - 1, b - 1  # 两边各扣减一个
        if a:  # 只剩 a 时补充剩余的 a
            ans.append('a' * a)  # 剩余 a 个数最多为 2，直接重复拼接
        if b:  # 只剩 b 时补充剩余的 b
            ans.append('b' * b)  # 剩余 b 个数最多为 2，直接重复拼接
        return ''.join(ans)  # 拼接所有片段返回
