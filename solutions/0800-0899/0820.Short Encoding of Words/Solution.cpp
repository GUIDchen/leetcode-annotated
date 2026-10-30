// 题目：820. 单词的压缩编码（Short Encoding of Words）
// 思路：互为后缀的单词可以共用一段编码，于是把所有单词倒序插入字典树；建树后每个叶子到根的路径长度之和就是答案（根计 1，代表结尾的 '#'）。
// 时间复杂度：O(Σ|w|)，Σ|w| 为所有单词总长度；空间复杂度：O(Σ|w|)，字典树节点数不超过总长度。
struct Trie {  // 字典树节点：26 个小写字母的孩子指针
    Trie* children[26] = {nullptr};  // 全部初始化为空指针
};  // 结构体结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumLengthEncoding(vector<string>& words) {  // words：待编码的单词列表
        auto root = new Trie();  // 字典树根节点
        for (auto& w : words) {  // 逐个单词插入
            auto cur = root;  // 每次都从根开始
            for (int i = w.size() - 1; i >= 0; --i) {  // 倒序遍历单词，把「后缀相同」的关系转成「公共前缀」
                if (cur->children[w[i] - 'a'] == nullptr) {  // 该字符对应的孩子还不存在
                    cur->children[w[i] - 'a'] = new Trie();  // 新建一个节点挂上去
                }  // if 结束
                cur = cur->children[w[i] - 'a'];  // 沿着该字符对应的孩子向下走一层
            }  // 单词插入结束
        }  // for 结束
        return dfs(root, 1);  // 从根开始统计：根层长度记为 1（末尾的 '#' 也算一个字符）
    }  // minimumLengthEncoding 方法结束

private:  // 私有辅助函数
    int dfs(Trie* cur, int l) {  // cur：当前节点；l：当前节点对应的长度（含 '#'）
        bool isLeaf = true;  // 先假设当前节点是叶子
        int ans = 0;  // 累计子树贡献的总长度
        for (int i = 0; i < 26; ++i) {  // 遍历 26 个孩子
            if (cur->children[i] != nullptr) {  // 存在孩子
                isLeaf = false;  // 有孩子说明不是叶子
                ans += dfs(cur->children[i], l + 1);  // 递归累加该子树的贡献，深度加 1
            }  // if 结束
        }
        if (isLeaf) {  // 叶子说明有单词在这里结束
            ans += l;  // 该单词的编码长度就是 l
        }  // if 结束
        return ans;  // 返回该子树的总长度
    }  // dfs 方法结束
};  // Solution 类结束