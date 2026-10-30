# 题目：3271. 哈希分割字符串（Hash Divided String）
# 思路：把字符串按长度 k 依次切块，每块内部把字符折算成 0..25 求和后对 26 取模，再映射回小写字母拼成结果。
# 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(n/k)，用于存放结果。
class Solution:  # LeetCode 约定的题解类
    def stringHash(self, s: str, k: int) -> str:  # s：输入字符串；k：每个块的字符个数；返回各块哈希后拼成的字符串
        ans = []  # ans：用列表收集每一块哈希出的字符
        for i in range(0, len(s), k):  # 每 k 个字符为一个块，i 是当前块的首下标
            t = 0  # t：当前块内所有字符折算值之和
            for j in range(i, i + k):  # 遍历当前块内的每个字符
                t += ord(s[j]) - ord("a")  # 把字符折算成 0..25 的数字并累加
            hashedChar = t % 26  # 对 26 取模，得到哈希后的数字
            ans.append(chr(ord("a") + hashedChar))  # 数字映射回小写字母，追加到结果末尾
        return "".join(ans)  # 把字符列表拼成字符串返回
