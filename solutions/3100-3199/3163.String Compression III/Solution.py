# 题目：3163. 压缩字符串 III（String Compression III）
# 思路：用 groupby 把相邻的相同字符合成一组，再把每组的长度拆成不超过 9 的次数依次输出。
# 时间复杂度：O(n)，每个字符只被读一次；空间复杂度：O(n)，结果列表最多存 2n 个片段。
class Solution:  # LeetCode 约定的题解类
    def compressedString(self, word: str) -> str:  # word 是待压缩的字符串，返回压缩后的结果
        g = groupby(word)  # groupby 只合并「相邻」且相同的字符，正好对应题目要求的连续段
        ans = []  # 用列表收集片段，最后 join 比反复拼接字符串更快
        for c, v in g:  # c 是当前组的字符，v 是该字符连续出现构成的迭代器
            k = len(list(v))  # 把迭代器物化成列表才能求长度（同一迭代器只能消费一次）
            while k:  # 该组的长度 k 需要拆成若干个不超过 9 的次数
                x = min(9, k)  # 一次最多写 9 个
                ans.append(str(x) + c)  # 次数在前、字符在后，拼成一段写入结果
                k -= x  # 扣掉已写出的次数，继续拆剩下的
        return "".join(ans)  # 拼接所有片段，得到最终的压缩字符串
