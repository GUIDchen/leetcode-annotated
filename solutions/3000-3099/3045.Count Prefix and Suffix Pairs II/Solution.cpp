// 题目：3045. 统计前后缀下标对 II（Count Prefix and Suffix Pairs II）
// 核心思路：把每个单词按「首字符 + 尾字符」成对插入字典树，节点记录以该前后缀路径结尾的单词数，处理到某单词时逐层累加即可在线统计答案。
// 时间复杂度：O(总字符数)，每个单词只需一次字典树插入；空间复杂度：O(总字符数)，字典树节点总数与字符总数同阶。
class Node {  // 字典树节点：把「前缀字符 + 后缀字符」成对作为边的编号
public:
    unordered_map<int, Node*> children;  // children：键是首尾字符对的编码，值是对应的子节点
    int cnt;  // cnt：以当前前后缀路径结尾的单词个数（即有多少个单词恰好在这里结束）

    Node()  // 构造函数，初始化节点
        : cnt(0) {}  // cnt 初始为 0，表示还没有单词在这里结束
};  // 节点定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外公开
    long long countPrefixSuffixPairs(vector<string>& words) {  // words：单词数组，返回满足 words[i] 同时是 words[j] 前后缀的下标对数量
        long long ans = 0;  // ans：累计的合法下标对数量；答案可能超过 int 范围所以用 long long
        Node* trie = new Node();  // trie：字典树根节点，保存此前插入过的所有前后缀路径
        for (const string& s : words) {  // 按输入顺序逐个处理单词，保证只统计 i < j 的对
            Node* node = trie;  // 从根节点开始，沿当前单词的首尾字符对向下走
            int m = s.length();  // m：当前单词长度，用于取对称位置的字符
            for (int i = 0; i < m; ++i) {  // 第 i 步同时看第 i 个字符与倒数第 i 个字符
                int p = s[i] * 32 + s[m - i - 1];  // 把两个字符编码成一个整数作为边的键，便于快速定位子节点
                if (node->children.find(p) == node->children.end()) {  // 子节点不存在说明这条前后缀路径首次出现
                    node->children[p] = new Node();  // 新建节点并挂到当前节点的 children 上
                }
                node = node->children[p];  // 指针下移到该子节点
                ans += node->cnt;  // 此前以这条路径结尾的单词数，正好是当前单词能新增的合法对数
            }  // 内层循环结束：当前单词的所有前后缀路径都已插入
            ++node->cnt;  // 在终点节点计数加一，表示又有一个单词以这条路径结尾
        }
        return ans;  // 返回累计的合法下标对数量
    }  // 方法结束
};  // 题解类结束