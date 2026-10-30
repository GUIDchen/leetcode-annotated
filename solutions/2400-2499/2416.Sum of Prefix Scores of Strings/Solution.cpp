// 题目：2416. 字符串的前缀分数和（Sum of Prefix Scores of Strings）
// 思路：把所有单词插入同一棵字典树，每个结点记录「有多少个单词经过它」；查询某个单词时，沿途累加各前缀结点的经过次数，就是该单词的前缀分数和。
// 时间复杂度：O(L)，L 为所有单词字符总数，建树与逐个查询各扫描一遍；空间复杂度：O(L)，字典树结点数不超过字符总数。
class Trie {  // 字典树结点：26 个子指针 + 经过该结点的单词数
private:  // 数据成员只允许类内部访问
    Trie* children[26]{};  // 26 个小写字母对应的子结点指针，{} 把它们全部初始化为 nullptr
    int cnt = 0;  // cnt：有多少个单词经过当前结点，即该前缀在所有单词中出现的次数

public:  // 对外提供插入与查询两个接口
    void insert(string& w) {  // 把单词 w 插入字典树，并给沿途每个前缀结点计数加一
        Trie* node = this;  // 从根结点出发向下走
        for (char c : w) {  // 逐个字符沿树下行
            int idx = c - 'a';  // 把字符映射为 0..25 的下标
            if (!node->children[idx]) {  // 该字符对应的子结点还不存在
                node->children[idx] = new Trie();  // 新建结点并挂在当前结点下
            }
            node = node->children[idx];  // 走到子结点上，代表前缀又长了一个字符
            ++node->cnt;  // 当前单词经过了该前缀，计数加一
        }
    }

    int search(string& w) {  // 查询单词 w 的「所有前缀出现次数」之和
        Trie* node = this;  // 从根结点出发
        int ans = 0;  // 累加结果
        for (char c : w) {  // 逐个字符沿树下行
            int idx = c - 'a';  // 字符到子结点下标
            if (!node->children[idx]) {  // 前缀链断开（本题每个单词都插入过，不会发生）
                return ans;  // 只能返回已经累加到的部分
            }
            node = node->children[idx];  // 进入该前缀对应的结点
            ans += node->cnt;  // 该前缀的出现次数计入答案
        }
        return ans;  // 返回完整的前缀分数和
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> sumPrefixScores(vector<string>& words) {  // words：输入单词数组
        Trie* trie = new Trie();  // 建一棵被所有单词共享的字典树
        for (auto& w : words) {  // 第一遍：把所有单词都插入字典树
            trie->insert(w);  // 插入后每个前缀的出现次数就统计完毕
        }
        vector<int> ans;  // 存放每个单词的前缀分数和，顺序与输入一致
        for (auto& w : words) {  // 第二遍：逐个单词查询
            ans.push_back(trie->search(w));  // 查询并追加到答案数组
        }
        return ans;  // 返回答案
    }
};
