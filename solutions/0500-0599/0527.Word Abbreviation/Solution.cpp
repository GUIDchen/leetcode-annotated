// 题目：527. 单词缩写（Word Abbreviation）
// 思路：按「(长度, 末字母)」分组建 Trie，节点存经过的单词数；走到 cnt==1 的前缀即为最短唯一缩写，其余长度不足时保留原词。
// 时间复杂度：O(L²)，每个单词最多试 L 个前缀长度；空间复杂度：O(m·L)，Trie 存储所有字符。
class Trie {  // 字典树节点：记录公共前缀上经过的单词数量
public:  // 公有成员区
    Trie()  // 默认构造函数
        : cnt(0) {  // 初始化成员 cnt = 0，表示经过本节点的单词数量
        fill(children.begin(), children.end(), nullptr);  // 把 26 个子节点指针全部置空
    }  // 构造函数结束

    void insert(const string& w) {  // 把一个单词插入 Trie
        Trie* node = this;  // 从根节点开始向下走
        for (char c : w) {  // 逐字符沿 Trie 下行
            int idx = c - 'a';  // 把字母映射成 0..25 的下标
            if (node->children[idx] == nullptr) {  // 该字母对应的子节点还不存在
                node->children[idx] = new Trie();  // 新建一个节点接上去
            }  // if 结束
            node = node->children[idx];  // 走到子节点
            ++node->cnt;  // 经过该节点的单词数加一（根节点不计数）
        }  // for 结束
    }  // insert 结束

    int search(const string& w) {  // 求单词 w 的最短唯一前缀长度
        Trie* node = this;  // 从根节点出发
        int ans = 0;  // 已走过的字符数，也就是前缀长度
        for (char c : w) {  // 逐字符沿 Trie 下行
            ++ans;  // 前缀长度加一
            int idx = c - 'a';  // 字母映射成 0..25 的下标
            node = node->children[idx];  // 走到对应的子节点
            if (node->cnt == 1) {  // 只有 w 自己经过这个前缀，说明前缀已能唯一确定它
                return ans;  // 返回这个最短唯一前缀的长度
            }  // if 结束
        }  // for 结束
        return w.size();  // 走到词尾仍不唯一，只能在整个单词范围内缩写
    }  // search 结束

private:  // 私有成员区
    array<Trie*, 26> children;  // 26 个小写字母对应的子节点指针
    int cnt;  // 经过本节点的单词数量
};  // Trie 类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 公有方法区
    vector<string> wordsAbbreviation(vector<string>& words) {  // words：待缩写的单词列表；返回每个单词对应的缩写
        map<pair<int, int>, Trie*> tries;  // 键是「单词长度, 末字母下标」，值是该分组共用的一棵 Trie
        for (const auto& w : words) {  // 第一遍：把所有单词按分组插入各自的 Trie
            pair<int, int> key = {static_cast<int>(w.size()), w.back() - 'a'};  // 分组键：长度 + 末字母（末字母要保留在缩写里，所以参与分组）
            if (tries.find(key) == tries.end()) {  // 该分组还没有 Trie
                tries[key] = new Trie();  // 为这个分组新建一棵空 Trie
            }  // if 结束
            tries[key]->insert(w);  // 把单词插入对应分组的 Trie
        }  // 第一遍 for 结束

        vector<string> ans;  // 保存每个单词的缩写结果
        for (const auto& w : words) {  // 第二遍：按原始顺序逐个生成缩写
            int m = w.size();  // 单词长度
            pair<int, int> key = {m, w.back() - 'a'};  // 与插入时完全相同的分组键
            int cnt = tries[key]->search(w);  // 求该单词的最短唯一前缀长度
            ans.push_back((cnt + 2 >= m) ? w : w.substr(0, cnt) + to_string(m - cnt - 1) + w.back());  // 缩写不如原词短（cnt+2>=m）时保留原词，否则拼成「前缀 + 省略字母数 + 末字母」
        }  // 第二遍 for 结束

        return ans;  // 返回所有单词的缩写，顺序与原输入一致
    }  // 方法结束
};  // Solution 类定义结束