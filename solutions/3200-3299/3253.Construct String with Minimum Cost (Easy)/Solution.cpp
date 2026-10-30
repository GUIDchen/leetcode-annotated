// 题目：3253. 最小代价构造字符串（简单）（Construct String with Minimum Cost (Easy)）
// 思路：先把所有单词及其代价插入字典树（同一单词保留最小代价），再对 target 做带记忆化的 DFS：枚举从 i 开始能匹配的单词，取「单词代价 + 剩余部分代价」的最小值。
// 时间复杂度：O(n² + Σ|word|)，n 为 target 长度，每个起点最多沿树走 n 步；空间复杂度：O(n + Σ|word|)。
const int inf = 1 << 29;  // 用一个足够大的数表示「不可达」

class Trie {  // 字典树：把所有单词挂到树上，便于沿 target 逐字符匹配
public:  // 成员对外可见，方便 Solution 调用
    Trie* children[26]{};  // 26 个小写字母子节点，{} 保证初始化为空指针
    int cost = inf;  // 以本节点结尾的单词的最小代价，默认视为不可用

    void insert(string& word, int cost) {  // 把单词插入字典树，并更新结尾节点的最小代价
        Trie* node = this;  // 从根节点开始向下插入
        for (char c : word) {  // 逐个字符沿树下行
            int idx = c - 'a';  // 把字母映射到 0..25 的分支下标
            if (!node->children[idx]) {  // 该分支还不存在时才需要新建节点
                node->children[idx] = new Trie();  // 新建一个字典树节点挂在当前位置
            }
            node = node->children[idx];  // 走到对应的子节点，继续处理下一个字符
        }
        node->cost = min(node->cost, cost);  // 同一单词出现多次时只保留最小代价
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {  // target：目标串；words/costs：可用单词及其代价；返回最小拼接代价
        Trie* trie = new Trie();  // 建字典树的根节点
        for (int i = 0; i < words.size(); ++i) {  // 把所有单词按顺序插入字典树
            trie->insert(words[i], costs[i]);  // 插入第 i 个单词及其代价
        }
        int n = target.length();  // n：目标串长度
        int f[n];  // f[i]：拼出 target[i..] 的最小代价（同时充当记忆化标记）
        memset(f, 0, sizeof(f));  // 全部清 0，0 同时表示「尚未计算」
        auto dfs = [&](this auto&& dfs, int i) -> int {  // 递归 + 记忆化：求从下标 i 开始匹配的最小代价
            if (i >= n) {  // 已经匹配到末尾
                return 0;  // 不需要再花费，代价为 0
            }
            if (f[i]) {  // 该状态已经算过（非 0 即已记忆）
                return f[i];  // 直接返回记忆中的结果
            }
            f[i] = inf;  // 先假设从 i 开始无法拼完
            Trie* node = trie;  // 从字典树根开始，沿 target[j] 逐字符向下走
            for (int j = i; j < n; ++j) {  // 枚举当前单词的结束位置 j
                int idx = target[j] - 'a';  // 当前字符对应的分支下标
                if (!node->children[idx]) {  // 字典树中没有这条路径，说明以 i 开头的更长的串也不存在
                    return f[i];  // 直接返回当前最优值
                }
                node = node->children[idx];  // 沿字符继续下走
                f[i] = min(f[i], node->cost + dfs(j + 1));  // 用「结束于 j 的单词代价 + 剩余部分的最小代价」更新答案
            }
            return f[i];  // 返回从 i 开始的最小代价
        };
        int ans = dfs(0);  // 从下标 0 开始拼出整个 target
        return ans < inf ? ans : -1;  // 仍为 inf 说明无法拼出，按题目要求返回 -1
    }
};
