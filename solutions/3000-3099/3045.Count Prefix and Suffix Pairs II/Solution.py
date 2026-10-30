# 题目：3045. 统计前后缀下标对 II（Count Prefix and Suffix Pairs II）
# 核心思路：用 zip(s, reversed(s)) 把首尾字符配成对插入字典树，节点记录以该前后缀路径结尾的单词数，处理每个单词时逐层累加即可在线统计。
# 时间复杂度：O(总字符数)，每个单词只做一次字典树插入；空间复杂度：O(总字符数)，字典树节点总数与字符总数同阶。
class Node:  # 字典树节点：用它记录此前插入过的所有「前后缀路径」
    __slots__ = ["children", "cnt"]  # __slots__ 限定属性，省掉 __dict__，节点多时更省内存也更快

    def __init__(self):  # 构造函数：初始化节点
        self.children = {}  # children：键是（前缀字符, 后缀字符）元组，值是对应的子节点
        self.cnt = 0  # cnt：以当前前后缀路径结尾的单词个数


class Solution:  # LeetCode 约定的题解类
    def countPrefixSuffixPairs(self, words: List[str]) -> int:  # words：单词数组，返回满足 words[i] 同时是 words[j] 前后缀的下标对数量
        ans = 0  # ans：累计的合法下标对数量
        trie = Node()  # trie：字典树根节点，保存此前插入过的所有前后缀路径
        for s in words:  # 按输入顺序逐个处理单词，保证只统计 i < j 的对
            node = trie  # 从根节点开始向下走
            for p in zip(s, reversed(s)):  # zip 把单词首尾对称的字符配成对，逐步构建前后缀路径
                if p not in node.children:  # 这条边还不存在，说明该前后缀组合首次出现
                    node.children[p] = Node()  # 新建子节点并挂到当前节点上
                node = node.children[p]  # 指针下移到该子节点
                ans += node.cnt  # 此前以这条路径结尾的单词数，就是当前单词新增的合法对数
            node.cnt += 1  # 当前单词结束，终点节点计数加一，供后面的单词统计
        return ans  # 返回累计的合法下标对数量
