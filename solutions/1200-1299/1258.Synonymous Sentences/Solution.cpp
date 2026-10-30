// 题目：1258. 近义词句子（Synonymous Sentences）
// 思路：近义词关系具有传递性，先用并查集把近义词合并成若干等价类；再把每一类里的单词按字典序排好，最后对原句的每个位置枚举同类可替换单词做回溯，拼出全部句子。
// 时间复杂度：O(L + S·W)，L 为近义词与单词的总规模、S 为生成的句子总数、W 为句子平均单词数；空间复杂度：O(L + S·W)，用于并查集、分组表与答案。
class UnionFind {  // 并查集：维护近义词之间的传递性等价关系
public:  // 对外暴露构造、合并、查找三个接口
    UnionFind(int n) {  // 构造函数：n 是节点（单词）个数
        p = vector<int>(n);  // p 是父指针数组，先开好 n 个位置，下面用 iota 填初值
        size = vector<int>(n, 1);  // size 记录每个集合的大小，按大小合并可以让树更矮
        iota(p.begin(), p.end(), 0);  // iota 把 p 依次写成 0,1,2,...，表示初始时每个节点各自成一个集合
    }

    void unite(int a, int b) {  // 合并 a、b 所在的两个集合
        int pa = find(a), pb = find(b);  // 先找到两个元素各自的根
        if (pa != pb) {  // 根不同说明原本属于不同集合，需要真正合并
            if (size[pa] > size[pb]) {  // 集合 a 更大，就把它当作合并后的根，控制树高
                p[pb] = pa;  // 小集合的根指向大集合的根
                size[pa] += size[pb];  // 大集合的大小累加上小集合的大小
            } else {  // else 分支：b 集合更大或等大，于是把 a 集合挂到 b 集合下面（两分支对称）
                p[pa] = pb;  // b 集合的根成为新的根
                size[pb] += size[pa];  // 合并后的大小累加
            }
        }
    }

    int find(int x) {  // 查找 x 所在集合的根，同时做路径压缩
        if (p[x] != x) {  // 父指针不指向自己，说明 x 还不是根
            p[x] = find(p[x]);  // 递归找到根，并把 x 直接挂到根上，加速后续查询
        }
        return p[x];  // 返回根节点编号
    }

private:  // 以下成员只供类内部使用
    vector<int> p, size;  // p 为父指针数组，size 为各集合大小
};

class Solution {  // 题解类：生成所有近义句
public:  // 题解方法对外可见
    vector<string> generateSentences(vector<vector<string>>& synonyms, string text) {  // synonyms：近义词对；text：原句；返回所有可替换后的句子（按字典序）
        unordered_set<string> ss;  // ss 收集所有出现过的近义单词并去重
        for (auto& pairs : synonyms) {  // 遍历每一对近义词
            ss.insert(pairs[0]);  // 记录第一个词
            ss.insert(pairs[1]);  // 记录第二个词
        }
        vector<string> words{ss.begin(), ss.end()};  // 把集合摊平成数组，方便用下标给单词编号
        unordered_map<string, int> d;  // d 建立「单词 → 下标」的映射
        int n = words.size();  // n 是不同近义单词的个数
        for (int i = 0; i < n; ++i) {  // 给每个单词分配 0~n-1 的编号
            d[words[i]] = i;  // 记录编号，后续按编号做并查集操作
        }
        UnionFind uf(n);  // 用 n 个节点初始化并查集
        for (auto& pairs : synonyms) {  // 把所有近义词对合并到同一个集合
            uf.unite(d[pairs[0]], d[pairs[1]]);  // 按单词编号合并两个词
        }
        vector<vector<int>> g(n);  // g[root] 存放同一等价类内的所有单词编号，即可以互相替换的候选
        for (int i = 0; i < n; ++i) {  // 把每个单词挂到它所在集合的根下
            g[uf.find(i)].push_back(i);  // 找到根并把编号追加进该组
        }
        for (int i = 0; i < n; ++i) {  // 逐组排序，保证最终输出的句子按字典序排列
            sort(g[i].begin(), g[i].end(), [&](int a, int b) {  // 按单词字典序比较两个编号，从而让组内单词有序
                return words[a] < words[b];  // 比较器：把编号还原成单词再比大小
            });
        }
        vector<string> sentence;  // sentence 存原句切分后的单词
        string s;  // s 作为读取单词的临时缓冲
        istringstream iss(text);  // 用字符串流按空白切分原句
        while (iss >> s) {  // 逐个取出单词，取空即表示切分结束
            sentence.emplace_back(s);  // 收集切好的单词
        }
        vector<string> ans;  // ans 收集所有生成好的句子
        vector<string> t;  // t 是回溯过程中的当前句子（单词列表）
        function<void(int)> dfs = [&](int i) {  // 从第 0 个位置开始回溯；i 表示当前处理到原句的第几个单词
            if (i >= sentence.size()) {  // 所有位置都处理完了，可以把当前句子收进答案
                string s;  // 用空格把 t 拼成一个完整句子
                for (int j = 0; j < t.size(); ++j) {  // 依次拼接每个单词
                    if (j) {  // 除第一个单词外，前面都需要补一个空格
                        s += " ";  // 追加分隔空格
                    }
                    s += t[j];  // 追加当前单词
                }
                ans.emplace_back(s);  // 保存这个可行的句子
                return;  // 本分支结束，回溯返回上一层
            }
            if (!d.count(sentence[i])) {  // 该位置不是近义单词，只能用原词，没有别的选择
                t.emplace_back(sentence[i]);  // 把原词压入当前句子
                dfs(i + 1);  // 递归处理下一个位置
                t.pop_back();  // 撤销选择，恢复现场
            } else {  // else 分支：该位置是近义单词，需要枚举它所在等价类里的每个候选
                for (int j : g[uf.find(d[sentence[i]])]) {  // 取出该单词所属等价类，逐个尝试里面的候选编号
                    t.emplace_back(words[j]);  // 把候选单词压入当前句子
                    dfs(i + 1);  // 递归处理下一个位置
                    t.pop_back();  // 撤销选择，尝试下一个候选
                }
            }
        };
        dfs(0);  // 从句子开头启动回溯
        return ans;  // 返回收集到的所有句子
    }
};