// 题目：472. 连接词（Concatenated Words）
// 思路：把所有单词按长度升序处理，边处理边插入字典树；对当前单词用 DFS 在 Trie 上枚举可切分的词根，能切完即为连接词。
// 时间复杂度：O(L^2) 量级（L 为单词长度，每个词 DFS 枚举切分点并沿 Trie 前进）；空间复杂度：O(总字符数)，即字典树的节点数。
class Trie {  // 字典树节点，用于快速判断某个前缀是否是已见过的完整单词
public:  // 成员对外可见
    vector<Trie*> children;  // 26 个孩子指针，分别对应字母 a~z
    bool isEnd;  // 标记「从根走到本节点」是否构成一个完整单词
    Trie()  // 构造函数
        : children(26)  // 初始时 26 个孩子全部为空
        , isEnd(false) {}  // 新节点默认不是单词结尾

    void insert(string w) {  // 把单词 w 插入字典树
        Trie* node = this;  // 从根节点开始往下走
        for (char c : w) {  // 逐字符遍历单词
            c -= 'a';  // 把字符映射成 0~25 的下标
            if (!node->children[c]) node->children[c] = new Trie();  // 该字母的孩子不存在就先建节点（若已有则复用）
            node = node->children[c];  // 下移到对应孩子
        }
        node->isEnd = true;  // 最后一个字符对应的节点标记为单词结尾
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    Trie* trie = new Trie();  // 全局字典树，边处理单词边累积收集

    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {  // words 是给定的单词表
        sort(words.begin(), words.end(), [&](const string& a, const string& b) {  // 按长度升序排序
            return a.size() < b.size();  // 短词在前，保证拼接所需的词根一定已经插入 Trie
        });
        vector<string> ans;  // 收集所有连接词
        for (auto& w : words) {  // 依次处理每个单词
            if (dfs(w))  // 能在 Trie 上被完整切分成至少两个词根
                ans.push_back(w);  // 是连接词，加入答案
            else  // 不能切分说明它是「词根」
                trie->insert(w);  // 把它加入字典树，供更长的单词拆分时使用
        }
        return ans;  // 返回全部连接词
    }

    bool dfs(string w) {  // 判断 w 能否由 Trie 中已有的单词拼接而成
        if (w == "") return true;  // 空串说明已经全部切分成功，是递归的终止条件
        Trie* node = trie;  // 从 Trie 根节点开始匹配前缀
        for (int i = 0; i < w.size(); ++i) {  // 逐字符沿 Trie 向下走
            int idx = w[i] - 'a';  // 当前字符对应的下标
            if (!node->children[idx]) return false;  // 前缀在 Trie 中不存在，这条切分路走不通
            node = node->children[idx];  // 下移到对应孩子
            if (node->isEnd && dfs(w.substr(i + 1))) return true;  // 前 i+1 个字符是完整词根，则递归检查剩余后缀
        }
        return false;  // 所有切分点都失败，该单词不是连接词
    }
};