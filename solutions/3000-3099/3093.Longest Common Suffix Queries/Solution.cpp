// 题目：3093. 最长公共后缀查询（Longest Common Suffix Queries）
// 思路：把所有容器串「倒序」插入字典树，每个结点记下经过它的串中最短的长度与对应下标（长度相同保留更早的下标）；查询时沿倒序尽量向下走，停住处的记录就是答案。
// 时间复杂度：O(Σ|wordsContainer| + Σ|wordsQuery|)，每个字符只走一步；空间复杂度：O(26 × Σ|wordsContainer|)，字典树结点开销。
class Trie {  // 倒序字典树：根结点代表空后缀
private:  // 内部数据
    const int inf = 1 << 30;  // 无穷大哨兵，表示「尚未被任何串记录」
    Trie* children[26];  // 26 个小写字母对应的子结点
    int length = inf;  // 经过本结点的串的最短长度（越短越优先）
    int idx = inf;  // 该最短串在容器数组中的下标

public:  // 对外接口
    Trie() {  // 构造函数：把所有子结点置空
        for (int i = 0; i < 26; ++i) {  // 遍历 26 个字母
            children[i] = nullptr;  // 初始都没有子结点
        }
    }

    void insert(string w, int i) {  // 把下标为 i 的串 w 倒序插入
        Trie* node = this;  // 从根结点开始
        if (node->length > w.length()) {  // 根结点代表空后缀，也可能被这个串更新
            node->length = w.length();  // 记录更短的长度
            node->idx = i;  // 记录该串下标
        }
        for (int k = w.length() - 1; k >= 0; --k) {  // 从串尾往前遍历字符
            int idx = w[k] - 'a';  // 字符映射到 0..25
            if (node->children[idx] == nullptr) {  // 该分支不存在就先建出来
                node->children[idx] = new Trie();  // 新建子结点
            }
            node = node->children[idx];  // 走到子结点
            if (node->length > w.length()) {  // 用当前串尝试更新该结点的记录
                node->length = w.length();  // 只有当前串更短才覆盖（等长时保留更早的下标）
                node->idx = i;  // 记录下标
            }
        }
    }

    int query(string w) {  // 查询串 w 的最长公共后缀对应的最优下标
        Trie* node = this;  // 从根结点开始
        for (int k = w.length() - 1; k >= 0; --k) {  // 同样从串尾往前
            int idx = w[k] - 'a';  // 字符映射到 0..25
            if (node->children[idx] == nullptr) {  // 再往下就没有公共后缀了
                break;  // 提前结束，当前结点就是最长公共后缀所在
            }
            node = node->children[idx];  // 继续深入
        }
        return node->idx;  // 返回该结点记录的最优下标（根结点对应空后缀）
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {  // 容器串集合与查询串集合
        Trie* trie = new Trie();  // 建一棵空字典树
        for (int i = 0; i < wordsContainer.size(); ++i) {  // 遍历容器中的每个串
            trie->insert(wordsContainer[i], i);  // 带着下标插入，供后续查询返回
        }
        int n = wordsQuery.size();  // 查询个数
        vector<int> ans(n);  // 每个查询的答案
        for (int i = 0; i < n; ++i) {  // 逐个回答查询
            ans[i] = trie->query(wordsQuery[i]);  // 查询得到最优下标
        }
        return ans;  // 返回答案数组
    }
};