# 题目：1258. 近义词句子（Synonymous Sentences）
# 思路：近义词关系具有传递性，先用并查集把近义词合并成若干等价类；再把每一类里的单词按字典序排好，最后对原句的每个位置枚举同类可替换单词做回溯，拼出全部句子。
# 时间复杂度：O(L + S·W)，L 为近义词与单词的总规模、S 为生成的句子总数、W 为句子平均单词数；空间复杂度：O(L + S·W)，用于并查集、分组表与答案。
class UnionFind:  # 并查集：维护近义词之间的传递性等价关系
    def __init__(self, n):  # 构造函数：n 是节点（单词）个数
        self.p = list(range(n))  # p 是父指针数组，range(n) 让每个元素初始指向自己，即各自成集合
        self.size = [1] * n  # size 记录每个集合的大小，按大小合并可以让树更矮

    def find(self, x):  # 查找 x 所在集合的根，同时做路径压缩
        if self.p[x] != x:  # 父指针不指向自己，说明 x 还不是根
            self.p[x] = self.find(self.p[x])  # 递归找到根，并把 x 直接挂到根上，加速后续查询
        return self.p[x]  # 返回根节点编号

    def union(self, a, b):  # 合并 a、b 所在的两个集合
        pa, pb = self.find(a), self.find(b)  # 先找到两个元素各自的根
        if pa != pb:  # 根不同说明原本属于不同集合，需要真正合并
            if self.size[pa] > self.size[pb]:  # 集合 a 更大，就把它当作合并后的根，控制树高
                self.p[pb] = pa  # 小集合的根指向大集合的根
                self.size[pa] += self.size[pb]  # 大集合的大小累加上小集合的大小
            else:  # 否则把 a 集合挂到 b 集合下面，两个分支完全对称
                self.p[pa] = pb  # b 集合的根成为新的根
                self.size[pb] += self.size[pa]  # 合并后的大小累加


class Solution:  # 题解类：生成所有近义句
    def generateSentences(self, synonyms: List[List[str]], text: str) -> List[str]:  # synonyms：近义词对；text：原句；返回所有可替换后的句子（按字典序）
        def dfs(i):  # 回溯函数：i 表示当前处理到原句的第几个单词
            if i >= len(sentence):  # 所有位置都处理完了，可以把当前句子收进答案
                ans.append(' '.join(t))  # 用空格把 t 拼成一个完整句子并收集起来
                return  # 本分支结束，回溯返回上一层
            if sentence[i] not in d:  # 该位置不是近义单词，只能用原词，没有别的选择
                t.append(sentence[i])  # 把原词压入当前句子
                dfs(i + 1)  # 递归处理下一个位置
                t.pop()  # 撤销选择，恢复现场
            else:  # 否则该位置是近义单词，需要枚举它所在等价类里的每个候选
                root = uf.find(d[sentence[i]])  # 取出该单词所属等价类的根，进而拿到同类候选列表
                for j in g[root]:  # 逐个尝试等价类里的候选编号
                    t.append(words[j])  # 把候选单词压入当前句子
                    dfs(i + 1)  # 递归处理下一个位置
                    t.pop()  # 撤销选择，尝试下一个候选

        words = list(set(chain.from_iterable(synonyms)))  # chain 把二维的近义词对摊平成一维，再用 set 去重得到所有近义单词
        d = {w: i for i, w in enumerate(words)}  # 建立「单词 → 编号」的映射，编号用于并查集
        uf = UnionFind(len(d))  # 用单词个数初始化并查集
        for a, b in synonyms:  # 把所有近义词对合并到同一个集合
            uf.union(d[a], d[b])  # 按单词编号合并两个词
        g = defaultdict(list)  # g[root] 存放同一等价类内的所有单词编号，即可以互相替换的候选
        for i in range(len(words)):  # 把每个单词挂到它所在集合的根下
            g[uf.find(i)].append(i)  # 找到根并把编号追加进该组
        for k in g.keys():  # 逐组排序，保证最终输出的句子按字典序排列
            g[k].sort(key=lambda i: words[i])  # 按单词字典序排序编号，从而让组内单词有序
        sentence = text.split()  # sentence 存原句切分后的单词（split 默认按任意空白切分）
        ans = []  # ans 收集所有生成好的句子
        t = []  # t 是回溯过程中的当前句子（单词列表）
        dfs(0)  # 从句子开头启动回溯
        return ans  # 返回收集到的所有句子
