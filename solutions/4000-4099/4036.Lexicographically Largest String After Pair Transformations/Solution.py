# 题目：4036. 字符对转换后字典序最大的字符串 / Lexicographically Largest String After Pair Transformations
# 核心思路：每个数字的二进制位 j 就代表字母 ('a'+j) 能取几次，从字母 z 往 a 依次取出对应个数并抹掉高位
# 复杂度：时间复杂度 O(26 + 输出总长度)，空间复杂度 O(输出总长度)
class Solution:  # 定义 LeetCode 题解类
    def largestString(self, nums: List[int]) -> List[str]:  # 对每个数字构造字典序最大的字符串
        ans = []  # 答案列表
        for x in nums:  # 逐个处理数字 x
            s = []  # 用字符列表收集当前数字的构造结果
            for j in range(25, -1, -1):  # 从最大字母（索引 25，即 z）向下枚举到 a
                t = x >> j  # 当前字母需要重复的次数
                s.append(chr(ord('a') + j) * t)  # 追加 t 个对应的字母
                x &= (1 << j) - 1  # 抹掉已使用的高位，只保留低位
            ans.append(''.join(s))  # 拼成一个字符串并加入答案
        return ans  # 返回所有构造结果
