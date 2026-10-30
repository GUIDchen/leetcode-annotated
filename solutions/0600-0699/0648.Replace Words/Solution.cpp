// 题目：648. 单词替换（Replace Words）
// 思路：先把所有词根建成字典树，再对句子里的每个单词沿树下行，遇到第一个词根结尾就把它换成长度最短的那个词根。
// 时间复杂度：O(总字符数)，建树与查询都是每个字符走一步；空间复杂度：O(总词根字符数)，即字典树节点数。
class Trie {  // 字典树（前缀树）节点，每个节点代表一个前缀
public:  // 成员对外可见
    Trie* children[26]{};  // 26 个小写字母对应的子节点指针，值初始化为 nullptr
    bool isEnd = false;  // 标记从根走到本节点形成的字符串是否是一个完整词根

    void insert(const string& w) {  // 把词根 w 插入字典树
        Trie* node = this;  // 游标从根节点开始
        for (char c : w) {  // 逐个字符沿树下行
            int idx = c - 'a';  // 把字母映射到 0~25 的子节点下标
            if (!node->children[idx]) {  // 该分支还不存在时才需要新建节点
                node->children[idx] = new Trie();  // 分配新节点并挂到当前节点下
            }
            node = node->children[idx];  // 游标下移一位
        }
        node->isEnd = true;  // 在词尾节点打上结束标记
    }

    string search(const string& w) {  // 返回 w 的最短词根；找不到词根时原样返回 w
        Trie* node = this;  // 游标从根节点开始
        for (int i = 0; i < w.size(); ++i) {  // 逐个字符下行，i 恰好等于当前前缀长度减一
            int idx = w[i] - 'a';  // 当前字符对应的子节点下标
            if (!node->children[idx]) {  // 前缀在树中中断，说明没有任何词根是 w 的前缀
                return w;  // 无法替换，返回原单词
            }
            node = node->children[idx];  // 游标下移一位
            if (node->isEnd) {  // 第一次遇到词根结尾，就是能匹配到的最短词根
                return w.substr(0, i + 1);  // 取前 i+1 个字符作为词根返回
            }
        }
        return w;  // 整词走完仍没有词根结尾，说明没有可替换的词根
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string replaceWords(vector<string>& dictionary, string sentence) {  // dictionary 是词根表，sentence 是待替换句子
        Trie trie;  // 建一棵空字典树
        for (auto& w : dictionary) {  // 把每个词根逐个插入字典树
            trie.insert(w);  // 插入一个词根
        }

        stringstream ss(sentence);  // 用字符串流按空格切分句子
        string word, res;  // word 承接每次切出的单词，res 拼装最终结果
        while (ss >> word) {  // 依次取出每个单词，直到流结束
            if (!res.empty()) res += " ";  // 非首个单词前补一个空格，保持原句的词间距
            res += trie.search(word);  // 追加替换后的单词（命中词根就替换，否则原样保留）
        }
        return res;  // 返回替换完成的句子
    }
};
