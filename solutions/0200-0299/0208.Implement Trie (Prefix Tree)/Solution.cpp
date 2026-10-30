// 题目：208. 实现 Trie（Implement Trie (Prefix Tree)）
// 思路：每个节点开 26 个儿子指向下一层，外加 isEnd 标记；插入沿用已有路径缺则新建，查询先沿字符走到底再看标记。
// 时间复杂度：insert/search/startsWith 均为 O(L)，L 为字符串长度；空间复杂度：O(总字符数)，每个新字符最坏新建一个节点。
class Trie {  // 前缀树节点兼树根：26 个儿子 + 单词结尾标记
private:  // 以下成员只在本类内部使用
    vector<Trie*> children;  // 26 个槽位对应字母 a~z，空指针表示该字母分支不存在
    bool isEnd;  // 标记从根到本节点拼出的字符串是否是一个完整单词

    Trie* searchPrefix(string s) {  // 内部工具：沿 s 的每个字符向下走，返回走完后的节点
        Trie* node = this;  // 从当前节点（根）开始匹配
        for (char c : s) {  // 逐个字符遍历前缀
            int idx = c - 'a';  // 把字符映射到 0~25 的下标
            if (!node->children[idx]) return nullptr;  // 分支不存在说明没有这个前缀，直接返回空指针
            node = node->children[idx];  // 沿该分支走到子节点
        }  // 前缀遍历结束
        return node;  // 返回最后一个字符对应的节点（s 为空时即 this）
    }  // 工具方法结束

public:  // 以下成员对外提供
    Trie()  // 构造函数：初始化根节点的 26 个儿子与结尾标记
        : children(26)  // 初始化列表：开 26 个槽位，默认值均为 nullptr
        , isEnd(false) {}  // 根节点本身不代表任何单词

    void insert(string word) {  // 插入单词：沿字符逐层建节点，最后打上结尾标记
        Trie* node = this;  // 从根节点出发
        for (char c : word) {  // 逐个字符向下建路径
            int idx = c - 'a';  // 字符到下标 0~25 的映射
            if (!node->children[idx]) node->children[idx] = new Trie();  // 分支不存在就新建一个节点挂上去
            node = node->children[idx];  // 走到该分支的子节点
        }  // 单词遍历结束
        node->isEnd = true;  // 末尾节点置真，表示这里是一个完整单词的结尾
    }  // insert 结束

    bool search(string word) {  // 查询完整单词是否存在于前缀树中
        Trie* node = searchPrefix(word);  // 先沿 word 走到对应节点
        return node != nullptr && node->isEnd;  // 路径存在且该节点是单词结尾，才算找到了
    }  // search 结束

    bool startsWith(string prefix) {  // 查询是否存在以 prefix 为前缀的单词
        Trie* node = searchPrefix(prefix);  // 沿 prefix 向下走
        return node != nullptr;  // 只要路径存在，就说明有单词以它为前缀
    }  // startsWith 结束
};  // 类定义结束（后面的注释是题目给的构造示例，保持原样）

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */