# 题目：1805. 字符串中不同整数的数目（Number of Different Integers in a String）
# 思路：用双指针扫描字符串，遇到数字段就跳过前导零、截取到该段结尾，把去零后的子串加入集合去重，最后返回集合大小。
# 时间复杂度：O(n)，每个字符只被扫描常数次；空间复杂度：O(n)，集合中存放各段数字子串。
class Solution:  # LeetCode 约定的题解类
    def numDifferentIntegers(self, word: str) -> int:  # word 只含字母和数字，返回其中不同非负整数的个数
        s = set()  # 集合用来存放去掉前导零后的整数子串，自动去重
        i, n = 0, len(word)  # i 是扫描指针，n 是字符串长度
        while i < n:  # 手动控制指针向前推进
            if word[i].isdigit():  # 发现一段数字的开头
                while i < n and word[i] == '0':  # 跳过前导零，使 "001" 与 "1" 归一
                    i += 1  # 指针前移，越过一个前导零
                j = i  # j 指向有效数字的起点，同时用作向后扫描的指针
                while j < n and word[j].isdigit():  # 一直走到这段数字结束
                    j += 1  # 指针前移，直到遇到非数字字符
                s.add(word[i:j])  # 切片取出有效数字部分加入集合，自动去重
                i = j  # 跳过整段数字，避免重复处理
            i += 1  # 当前不是数字（或整段数字已处理完）时指针前移一位
        return len(s)  # 集合大小就是不同整数的个数
