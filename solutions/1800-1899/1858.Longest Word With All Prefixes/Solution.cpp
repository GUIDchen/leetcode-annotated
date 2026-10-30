// 题目：1858. 包含所有前缀的最长单词（Longest Word With All Prefixes）
// 思路：先把所有单词插入字典树，再对每个单词沿树逐字符下落，要求途经的每个结点都是某个单词的结尾（isEnd），从而保证它的所有前缀都在集合中；在满足条件的候选里取最长、长度相同取字典序最小。
// 时间复杂度：O(L)，L 为所有单词的字符总数；空间复杂度：O(L)，字典树结点总数。
class Trie {  // 字典树结点：用固定 26 个孩子表示小写字母
private:  // 内部实现细节，不对外暴露
    Trie* children[26];  // children[idx] 指向字母 idx 的子结点，空表示没有该前缀
    bool isEnd = false;  // isEnd：是否有单词以当前结点结尾

public:  // 对外接口
    Trie() {  // 构造：把 26 个孩子指针全部置空
        fill(begin(children), end(children), nullptr);  // 用 fill + begin/end 一次性初始化整个数组
    }  // 构造函数结束

    void insert(const string& w) {  // 插入单词 w
        Trie* node = this;  // 从根结点开始向下走
        for (char c : w) {  // 逐字符插入
            int idx = c - 'a';  // 字符映射到 0..25
            if (!node->children[idx]) {  // 该前缀对应的子结点还不存在
                node->children[idx] = new Trie();  // 新建结点挂上去
            }  // 子结点建立结束
            node = node->children[idx];  // 移动到子结点，继续插下一个字符
        }  // 字符遍历结束
        node->isEnd = true;  // 最后一个字符所在结点标记为单词结尾
    }  // insert 结束

    bool search(const string& w) {  // 检查 w 的每个前缀是否都是树中某个单词
        Trie* node = this;  // 从根结点开始
        for (char c : w) {  // 逐字符向下走
            int idx = c - 'a';  // 字符映射到 0..25
            node = node->children[idx];  // 沿当前字符下降到子结点（插入时已保证存在）
            if (!node->isEnd) {  // 某个前缀不是完整单词，就不满足题意
                return false;  // 立即返回 false
            }  // 该前缀检查结束
        }  // 字符遍历结束
        return true;  // 所有前缀都是单词，返回 true
    }  // search 结束
};  // 字典树类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string longestWord(vector<string>& words) {  // words：候选单词列表，返回满足条件的最长单词
        Trie trie;  // 建立字典树
        for (const string& w : words) {  // 先把所有单词插入树中，供 O(L) 前缀判定
            trie.insert(w);  // 逐个插入
        }  // 插入结束
        string ans = "";  // 答案初值：空串（长度 0）
        for (const string& w : words) {  // 遍历所有单词挑最优答案
            if ((w.size() > ans.size() || (w.size() == ans.size() && w < ans)) && trie.search(w)) {  // 长度更长，或长度相同而字典序更小，并且所有前缀都在集合中
                ans = w;  // 更新答案
            }  // 候选判断结束
        }  // 循环结束
        return ans;  // 返回答案，没有合法单词时就是空串
    }  // 方法结束
};  // 类定义结束