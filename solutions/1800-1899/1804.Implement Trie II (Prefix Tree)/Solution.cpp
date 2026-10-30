// 题目：1804. 实现 Trie（前缀树）II（Implement Trie II (Prefix Tree)）
// 思路：每个节点维护 v（以该节点结尾的单词数）与 pv（经过该节点的单词数，即该前缀的单词数）；插入/删除沿路径增减计数，查询先定位节点再读计数。
// 时间复杂度：每次操作 O(L)，L 为单词长度；空间复杂度：O(总字符数)，每个字符最多一个新节点。
class Trie {  // LeetCode 约定的前缀树类
public:  // 对外提供 insert / countWordsEqualTo / countWordsStartingWith / erase
    Trie()  // 构造函数：26 个子节点指针，单词计数与前缀计数都为 0
        : children(26)  // 只考虑小写字母 a~z，所以子节点数组长度为 26
        , v(0)  // v：以当前节点结尾的单词数量
        , pv(0) {  // pv：经过当前节点的单词数量，也就是该前缀对应的单词数
    }

    void insert(string word) {  // 插入一个单词
        Trie* node = this;  // 从根节点开始向下走
        for (char c : word) {  // 逐字符沿路径向下建链
            c -= 'a';  // 把字母映射成 0~25 的下标
            if (!node->children[c]) {  // 该字母对应的子节点不存在
                node->children[c] = new Trie();  // 新建一个子节点挂上去
            }
            node = node->children[c];  // 走到该字母对应的子节点
            ++node->pv;  // 路径上每个节点的「前缀计数」都加一
        }
        ++node->v;  // 单词末尾节点的「结尾计数」加一，表示多了一个完全相同的单词
    }

    int countWordsEqualTo(string word) {  // 返回与 word 完全相同的单词个数
        Trie* node = search(word);  // 先定位到 word 末尾对应的节点
        return node ? node->v : 0;  // 节点存在就返回结尾计数 v，否则说明没有这个单词，返回 0
    }

    int countWordsStartingWith(string prefix) {  // 返回以 prefix 为前缀的单词个数
        Trie* node = search(prefix);  // 先定位到 prefix 末尾对应的节点
        return node ? node->pv : 0;  // 节点存在就返回前缀计数 pv，否则返回 0
    }

    void erase(string word) {  // 删除一个单词（题目保证该单词一定存在）
        Trie* node = this;  // 从根节点开始向下走
        for (char c : word) {  // 逐字符沿路径向下
            c -= 'a';  // 把字母映射成 0~25 的下标
            node = node->children[c];  // 走到该字母对应的子节点
            --node->pv;  // 沿途前缀计数减一
        }
        --node->v;  // 末尾节点结尾计数减一，表示这个单词少了一个
    }

private:  // 内部实现细节
    vector<Trie*> children;  // 26 个子节点指针
    int v, pv;  // v 为结尾计数，pv 为前缀计数

    Trie* search(string& word) {  // 沿字符路径查找，返回 word 末尾对应的节点；路径断了返回 nullptr
        Trie* node = this;  // 从根节点开始查找
        for (char c : word) {  // 逐字符向下
            c -= 'a';  // 把字母映射成 0~25 的下标
            if (!node->children[c]) {  // 路径断了说明没有这个单词/前缀
                return nullptr;  // 返回空指针表示不存在
            }
            node = node->children[c];  // 走到该字母对应的子节点
        }
        return node;  // 返回 word 末尾对应的节点
    }
};

// 下面是 LeetCode 模板给出的调用示例，原本就是块注释，原样保留
/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */