// 题目：1032. 字符流（Stream of Characters）
// 思路：把每个字典单词倒序插入前缀树，使「字符流的后缀」对应「树上的根到某节点路径」；查询时从末尾向前走，遇到结束标记即命中。
// 时间复杂度：建树 O(L * m)；每次 query O(L)，L 为单词最大长度（≤200）；空间复杂度：O(L * m)，树节点总数。
class Trie {  // 前缀树（字典树）：以「倒序单词」建树，便于从字符流末尾往前匹配
private:  // 以下成员仅供类内部使用
    Trie* children[26]{};  // 26 个小写字母对应的孩子指针，{} 把整个数组初始化为 nullptr
    bool isEnd = false;  // 标记「从根走到该节点的路径」是否恰好是一个完整单词

public:  // 以下是对外接口
    void insert(string& w) {  // 倒序插入单词 w：这样搜索时从字符流末尾往前读，正好是树上的正常下行顺序
        Trie* node = this;  // 从根节点开始向下建路径
        reverse(w.begin(), w.end());  // 原地反转单词（会改动调用方传入的字符串，但字典之后不再使用）
        for (char& c : w) {  // 逐个字符沿树下行
            int idx = c - 'a';  // 字母 a..z 映射为 0..25 的孩子下标
            if (!node->children[idx]) {  // 这条分支还不存在
                node->children[idx] = new Trie();  // 新建子节点把这条边补上
            }  // 分支判断结束
            node = node->children[idx];  // 移动到子节点，继续插入下一个字符
        }  // 单词的所有字符都建好路径
        node->isEnd = true;  // 在末节点打上「单词结束」标记
    }  // insert 结束

    bool search(string& w) {  // 从 w 的末尾向前匹配：沿途只要遇到 isEnd，就说明有单词是当前字符流的后缀
        Trie* node = this;  // 从根节点开始匹配
        for (int i = w.size() - 1, j = 0; ~i && j < 201; --i, ++j) {  // i 从末尾往左走；j 限制最多回看 201 个字符（题目保证单词长度不超过 200）；~i 表示 i >= 0
            int idx = w[i] - 'a';  // 当前字符对应的孩子下标
            if (!node->children[idx]) {  // 树里没有这条边，后缀不可能再匹配到任何单词
                return false;  // 直接判定不存在
            }  // 提前返回分支结束
            node = node->children[idx];  // 沿边下行到一个字符
            if (node->isEnd) {  // 走到了某个单词的末尾节点
                return true;  // 说明当前后缀恰好等于字典中的某个单词
            }  // 命中判断结束
        }  // 字符用完或回看次数达到上限
        return false;  // 整个回看窗口内都没有命中
    }  // search 结束
};  // Trie 类定义结束

class StreamChecker {  // 字符流查询器：每来一个字符，判断当前流是否存在某个字典单词作为后缀
public:  // 对外方法
    Trie* trie = new Trie();  // 所有单词共用一棵倒序前缀树
    string s;  // 累积到目前为止读到的全部字符

    StreamChecker(vector<string>& words) {  // 构造函数：把字典中的单词全部倒序插入前缀树
        for (auto& w : words) {  // 逐个单词建树
            trie->insert(w);  // 插入时会把 w 原地反转，不影响正确性
        }  // 字典构建完成
    }  // 构造函数结束

    bool query(char letter) {  // 每读入一个字符就查询一次，返回是否存在后缀命中
        s += letter;  // 把新字符追加到字符流末尾
        return trie->search(s);  // 在该流上从末尾向前匹配前缀树
    }  // query 结束
};  // StreamChecker 类定义结束

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */
