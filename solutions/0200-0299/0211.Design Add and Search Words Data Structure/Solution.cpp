// 题目：211. 添加与搜索单词 - 数据结构设计（Design Add and Search Words Data Structure）
// 思路：前缀树存单词；搜索时遇到普通字符只走唯一分支，遇到通配符 . 就枚举 26 个分支做 DFS 回溯。
// 时间复杂度：addWord 为 O(L)；search 最坏 O(26^L)，L 为单词长度（通配符很多时）；空间复杂度：O(总字符数)。
class trie {  // 前缀树节点：26 个儿子 + 单词结尾标记（供 WordDictionary 复用）
public:  // 成员公开，方便外部直接访问孩子数组
    vector<trie*> children;  // 26 个槽位对应 a~z，空指针表示分支不存在
    bool is_end;  // 标记从根到本节点是否构成一个完整单词

    trie() {  // 构造函数：初始化 26 个孩子与结尾标记
        children = vector<trie*>(26, nullptr);  // 开 26 个槽位，全部置空
        is_end = false;  // 新节点默认不是单词结尾
    }  // 构造结束

    void insert(const string& word) {  // 把单词插入前缀树
        trie* cur = this;  // 从当前节点（根）出发
        for (char c : word) {  // 逐个字符向下建路径
            c -= 'a';  // 把字符就地换算成 0~25 的下标（复用变量 c）
            if (cur->children[c] == nullptr) {  // 该字母分支还不存在
                cur->children[c] = new trie;  // 新建一个节点挂到该分支上
            }  // if 分支结束
            cur = cur->children[c];  // 走到该分支的子节点
        }  // 单词遍历结束
        cur->is_end = true;  // 末尾节点打上是一个完整单词的标记
    }  // insert 结束
};  // 前缀树类定义结束

class WordDictionary {  // 支持 . 通配的单词字典
private:  // 以下成员只在内部使用
    trie* root;  // 前缀树根节点，所有单词都挂在它下面

public:  // 对外提供的接口
    WordDictionary()  // 构造函数：创建一棵空前缀树
        : root(new trie) {}  // 初始化列表里 new 出一个根节点

    void addWord(string word) {  // 添加单词：直接转交给前缀树插入
        root->insert(word);  // 从根节点插入 word
    }  // addWord 结束

    bool search(string word) {  // 查询单词，word 中的 . 可以匹配任意一个字母
        return dfs(word, 0, root);  // 从第 0 个字符和根节点开始做深度优先搜索
    }  // search 结束

private:  // 以下为内部辅助方法
    bool dfs(const string& word, int i, trie* cur) {  // 判断 word[i..] 能否从节点 cur 继续匹配完
        if (i == word.size()) {  // 所有字符都匹配完了
            return cur->is_end;  // 只有当前节点是单词结尾，才算真正命中
        }  // 递归出口分支结束
        char c = word[i];  // 取出当前要匹配的字符
        if (c != '.') {  // 普通字符：只能沿唯一确定的分支走
            trie* child = cur->children[c - 'a'];  // 找到该字母对应的子节点
            if (child != nullptr && dfs(word, i + 1, child)) {  // 子节点存在，且剩余部分也能匹配
                return true;  // 整体匹配成功
            }  // if 分支结束
        } else {  // 通配符 . ：任意一个存在的子节点都可能匹配
            for (trie* child : cur->children) {  // 枚举全部 26 个分支
                if (child != nullptr && dfs(word, i + 1, child)) {  // 该分支存在，且剩余部分能匹配
                    return true;  // 只要有一条分支走通就成功
                }  // if 分支结束
            }  // 26 个分支枚举结束
        }  // 分支判断结束
        return false;  // 所有可能都走不通，匹配失败
    }  // dfs 结束
};  // WordDictionary 类定义结束（后面的注释是题目给的构造示例，保持原样）

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */