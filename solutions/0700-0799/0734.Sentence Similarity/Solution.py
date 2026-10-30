# 题目：734. 句子相似性（Sentence Similarity）
# 思路：两个句子长度必须相同；把相似对收进集合，再逐位置比较，单词相同或（任一方向）出现在集合中即视为相似。
# 时间复杂度：O(L + P)，L 为句子长度、P 为相似对数量；空间复杂度：O(P)，集合存放 P 条有序对。
class Solution:  # LeetCode 约定的题解类
    def areSentencesSimilar(  # 函数签名换行书写，参数在下一行继续
        self, sentence1: List[str], sentence2: List[str], similarPairs: List[List[str]]  # sentence1、sentence2 是待比较的两个句子，similarPairs 是相似词对
    ) -> bool:  # 返回两个句子是否相似
        if len(sentence1) != len(sentence2):  # 两个句子必须有相同数量的单词才有可比性
            return False  # 长度不同直接判定不相似
        s = {(x, y) for x, y in similarPairs}  # 把相似对收集成元组集合，便于 O(1) 判断
        for x, y in zip(sentence1, sentence2):  # zip 按位置同时取出两个句子的单词
            if x != y and (x, y) not in s and (y, x) not in s:  # 单词不同，且两个方向都不在相似集合里，则该位置不相似
                return False  # 存在不相似的位置，返回 False
        return True  # 所有位置都相同或相似，返回 True
