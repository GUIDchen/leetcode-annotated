# 题目：1554. 只有一个不同字符的字符串（Strings Differ by One Character）
# 思路：把每个单词的每个位置都替换成通配符 "*" 生成模式串，放进集合查重；模式串相同即说明某两个单词只差这一位。
# 时间复杂度：O(L^2·n)（每个单词生成 L 个长度为 L 的字符串）；空间复杂度：O(n·L^2)（集合中保存所有模式串）。
class Solution:  # LeetCode 约定的题解类
    def differByOne(self, dict: List[str]) -> bool:  # dict：给定的等长单词列表（名字沿用了题目参数名）
        s = set()  # 集合：存放已经生成过的模式串
        for word in dict:  # 逐个处理每个单词
            for i in range(len(word)):  # 枚举单词的每一个字符位置
                t = word[:i] + "*" + word[i + 1 :]  # 用切片拼接，把第 i 位替换成通配符 "*"
                if t in s:  # 集合里已有同一个模式串，说明两个单词只在这一位不同
                    return True  # 找到合法的单词对，立即返回 True
                s.add(t)  # 否则把模式串记入集合，供后面的单词比对
        return False  # 所有模式串都不重复，说明不存在只差一个字符的两个单词
