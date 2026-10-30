// 题目：676. 实现一个魔法字典（Implement Magic Dictionary）
// 思路：把所有单词插入字典树，查询时 DFS 逐字符匹配并记录已经用掉的「替换次数」diff，走到词尾时恰好用掉一次替换且是单词结尾即命中。
// 时间复杂度：插入 O(L)；查询最坏 O(26^2 * L)，每个位置允许一次岔路；空间复杂度：O(总字符数 * 26)，字典树节点开销。
class Trie {  // 字典树节点
private:  // 内部数据不对外暴露
    Trie* children[26];  // 26 个子节点指针，下标为字符相对 'a' 的偏移
    bool isEnd = false;  // 标记从根到该节点是否构成一个完整单词

public:  // 构造函数与操作对外可见
    Trie() {  // 构造节点
        fill(begin(children), end(children), nullptr);  // 26 个孩子指针全部初始化为空
    }

    void insert(const string& w) {  // 把一个单词插入字典树
        Trie* node = this;  // 从根节点开始
        for (char c : w) {  // 逐字符向下
            int i = c - 'a';  // 计算字符对应的孩子下标
            if (!node->children[i]) {  // 该分支还不存在
                node->children[i] = new Trie();  // 新建一个节点补上
            }
            node = node->children[i];  // 走到对应的孩子节点
        }
        node->isEnd = true;  // 最后一个字符处标记单词结束
    }

    bool search(const string& w) {  // 查询是否存在「恰好替换一个字母」后等于 w 的单词
        function<bool(int, Trie*, int)> dfs = [&](int i, Trie* node, int diff) {  // i 是当前字符下标，diff 是已用掉的替换次数
            if (i >= w.size()) {  // 已经走完整个待查串
                return diff == 1 && node->isEnd;  // 必须恰好替换一次，且落在某个单词的结尾
            }
            int j = w[i] - 'a';  // 当前字符对应的孩子下标
            if (node->children[j] && dfs(i + 1, node->children[j], diff)) {  // 不走岔路：原样匹配当前字符，继续往下
                return true;  // 后续能匹配成功就返回
            }
            if (diff == 0) {  // 还没用过替换机会，可以在这里换一个字母
                for (int k = 0; k < 26; ++k) {  // 枚举 26 个可能的替换字母
                    if (k != j && node->children[k]) {  // 与原字符不同且该分支存在
                        if (dfs(i + 1, node->children[k], 1)) {  // 用掉唯一的替换机会继续匹配
                            return true;  // 命中即返回
                        }
                    }
                }
            }
            return false;  // 两种情况都失败
        };
        return dfs(0, this, 0);  // 从根节点、第 0 个字符、还没替换过开始搜索
    }
};

class MagicDictionary {  // 题目要求的魔法字典类
public:  // 对外接口
    MagicDictionary() {  // 构造字典
        trie = new Trie();  // 创建空的字典树根节点
    }

    void buildDict(vector<string> dictionary) {  // 用给定词表构建字典
        for (auto& w : dictionary) {  // 逐个单词
            trie->insert(w);  // 插入字典树
        }
    }

    bool search(string searchWord) {  // 判断 searchWord 能否由字典中恰好替换一个字母得到
        return trie->search(searchWord);  // 交给字典树去搜索
    }

private:  // 内部数据
    Trie* trie;  // 字典树的根节点
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */