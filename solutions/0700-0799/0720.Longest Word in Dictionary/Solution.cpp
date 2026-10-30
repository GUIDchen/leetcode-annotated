// 题目：720. 词典中最长的单词（Longest Word in Dictionary）
// 思路：把所有单词插入字典树；候选单词合法 <=> 它的每个前缀（含自身）都是树中某个单词的结尾；再按「更长、同长取字典序更小」挑最优。
// 时间复杂度：O(sum|w| log|w|)（排序与逐字符建树）；空间复杂度：O(sum|w| * 26)（字典树节点）。
class Trie {  // 字典树节点（同时作为整棵树的根）
public:  // 对外暴露的数据与接口
    Trie* children[26] = {nullptr};  // 26 个子指针，对应字母 a~z，初始全部为空
    bool isEnd = false;  // 标记从根到当前节点的路径是否恰好是一个完整单词

    void insert(const string& w) {  // 把单词 w 插入字典树
        Trie* node = this;  // 从根节点开始向下走
        for (char c : w) {  // 逐个字符向下扩展路径
            int idx = c - 'a';  // 字母映射为 0~25 的下标
            if (node->children[idx] == nullptr) {  // 该字符对应的分支还不存在
                node->children[idx] = new Trie();  // 新建子节点补上这条分支
            }  // if 分支结束
            node = node->children[idx];  // 走到子节点，继续处理下一个字符
        }  // for 循环结束
        node->isEnd = true;  // 词尾打标记，表示 w 是完整单词
    }  // insert 方法结束

    bool search(const string& w) {  // 判断 w 的每个前缀（含自身）是否都作为单词出现过
        Trie* node = this;  // 从根开始
        for (char c : w) {  // 逐字符沿树下降
            int idx = c - 'a';  // 字母映射成下标
            if (node->children[idx] == nullptr || !node->children[idx]->isEnd) {  // 分支不存在，或该前缀本身不是完整单词，则 w 不能由短单词逐字构造
                return false;  // 直接判定不合法
            }  // if 分支结束
            node = node->children[idx];  // 继续向下一层
        }  // for 循环结束
        return true;  // 所有前缀都合法，w 合法
    }  // search 方法结束
};  // Trie 类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string longestWord(vector<string>& words) {  // words：候选单词集合
        Trie trie;  // 建立一棵字典树保存所有单词
        for (const string& w : words) {  // 遍历每个单词
            trie.insert(w);  // 插入字典树，供后续前缀判定使用
        }  // for 循环结束

        string ans = "";  // 记录当前最优答案
        for (const string& w : words) {  // 逐个检查单词是否合法
            if (trie.search(w) && (ans.length() < w.length() || (ans.length() == w.length() && w < ans))) {  // 合法，且「比当前答案更长」或「等长时字典序更小」
                ans = w;  // 更新答案
            }  // if 分支结束
        }  // for 循环结束
        return ans;  // 返回最长的合法单词（不存在则返回空串）
    }  // 方法结束
};  // 类定义结束
