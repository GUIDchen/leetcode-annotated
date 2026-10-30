// 题目：737. 句子相似性 II（Sentence Similarity II）
// 思路：相似关系具有传递性，等价于判断两个单词是否在同一连通块——给每个单词编号后用并查集合并 similarPairs，再逐位置比较即可。
// 时间复杂度：O((m + n)·α(n))，m 为单词对数、n 为句子长度，α 为近似常数的反阿克曼函数；空间复杂度：O(m)，并查集与编号表都正比于单词数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> p;  // 并查集父指针数组（成员变量，供 find 使用）
    bool areSentencesSimilarTwo(vector<string>& sentence1, vector<string>& sentence2, vector<vector<string>>& similarPairs) {  // sentence1/sentence2 为待比较的两个句子，similarPairs 为相似单词对
        if (sentence1.size() != sentence2.size())  // 两个句子长度不同，按位置比较没有意义，直接不相似
            return false;  // 返回 false
        int n = similarPairs.size();  // 相似对的数量
        p.resize(n << 1);  // 每对最多引入 2 个新单词，所以并查集容量取 2n 就够
        for (int i = 0; i < p.size(); ++i)  // 初始化并查集：每个编号先各自成为一个集合
            p[i] = i;  // 父指针指向自己表示它是集合的根
        unordered_map<string, int> words;  // 哈希表：单词 → 编号，用于把字符串映射到并查集下标
        int idx = 0;  // 下一个可分配的编号
        for (auto e : similarPairs) {  // 遍历每一对相似单词
            string a = e[0], b = e[1];  // 取出这一对的两个单词
            if (!words.count(a))  // 单词 a 还没编号就分配一个
                words[a] = idx++;  // 记录编号并让计数器自增
            if (!words.count(b))  // 单词 b 还没编号就分配一个
                words[b] = idx++;  // 记录编号并让计数器自增
            p[find(words[a])] = find(words[b]);  // 合并：把 a 所在集合的根挂到 b 所在集合的根下面（相似关系可传递）
        }  // 结束对相似对的遍历
        for (int i = 0; i < sentence1.size(); ++i) {  // 逐位置检查两个句子
            if (sentence1[i] == sentence2[i])  // 同一个单词自然相似，直接跳过
                continue;  // 继续下一位置
            if (!words.count(sentence1[i]) || !words.count(sentence2[i]) || find(words[sentence1[i]]) != find(words[sentence2[i]]))  // 任一单词从未出现过（孤立点不可能与别人相似）或两者根不同 ⇒ 该位置不相似
                return false;  // 返回 false
        }  // 结束 for 循环
        return true;  // 所有位置都满足相似条件
    }  // 结束 areSentencesSimilarTwo

    int find(int x) {  // 并查集查找：返回 x 所在集合的根
        if (p[x] != x)  // 父指针不是自己说明还没到根
            p[x] = find(p[x]);  // 沿路径回溯，同时做路径压缩
        return p[x];  // 返回根节点
    }  // 结束 find
};  // 结束 Solution 类