# 题目：737. 句子相似性 II（Sentence Similarity II）
# 思路：相似关系可传递，等价于判断两个单词是否在同一连通块——给单词编号后用并查集合并 similarPairs，再逐位置比较。
# 时间复杂度：O((m + n)·α(m))，m 为单词对数、n 为句子长度；空间复杂度：O(m)，并查集数组与编号字典都正比于单词数。
class Solution:  # LeetCode 约定的题解类
    def areSentencesSimilarTwo(  # sentence1/sentence2 为两个待比较的句子
        self, sentence1: List[str], sentence2: List[str], similarPairs: List[List[str]]  # similarPairs 为相似单词对列表
    ) -> bool:  # 返回两个句子是否在传递意义下相似
        if len(sentence1) != len(sentence2):  # 长度不同无法逐位置比较，直接不相似
            return False  # 返回 False
        n = len(similarPairs)  # 相似对的数量
        p = list(range(n << 1))  # 每对最多引入 2 个新单词，所以并查集容量取 2n；初始时每个编号自成一个集合

        def find(x):  # 内嵌的并查集查找：返回 x 所在集合的根
            if p[x] != x:  # 父指针不是自己说明还没到根
                p[x] = find(p[x])  # 沿路径回溯，同时做路径压缩，摊还代价接近 O(1)
            return p[x]  # 返回根编号

        words = {}  # 哈希表：单词 → 并查集编号
        idx = 0  # 下一个可分配的编号
        for a, b in similarPairs:  # 遍历每一对相似单词
            if a not in words:  # 单词 a 还没编号就分配一个
                words[a] = idx  # 记录 a 的编号
                idx += 1  # 编号计数器自增
            if b not in words:  # 单词 b 还没编号就分配一个
                words[b] = idx  # 记录 b 的编号
                idx += 1  # 编号计数器自增
            p[find(words[a])] = find(words[b])  # 合并两个集合：把 a 的根挂到 b 的根下面，从而支持相似关系的传递

        for i in range(len(sentence1)):  # 逐位置检查两个句子
            if sentence1[i] == sentence2[i]:  # 同一个单词自然相似，跳过
                continue  # 继续下一位置
            if (  # 下面三种情况任一成立即该位置不相似：
                sentence1[i] not in words  # sentence1[i] 从未出现在相似对中
                or sentence2[i] not in words  # sentence2[i] 从未出现在相似对中
                or find(words[sentence1[i]]) != find(words[sentence2[i]])  # 两个单词不在同一个并查集集合里
            ):  # 结束 if 条件
                return False  # 返回 False
        return True  # 所有位置都满足相似条件
