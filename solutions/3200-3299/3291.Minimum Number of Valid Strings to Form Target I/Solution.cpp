// 题目：3291. 形成目标字符串需要的最少字符串数 I（Minimum Number of Valid Strings to Form Target I）
// 思路：先把 words 全部插入字典树，再用记忆化搜索 dp[i] = min(1 + dp[j+1])，其中 target[i..j] 必须是字典树里某个串的前缀。
// 时间复杂度：O(n^2 + L)，n 为 target 长度、L 为 words 总字符数；空间复杂度：O(n + L)，用于 dp 与字典树。
class Trie {  // 字典树节点：用来判断 target 的某个前缀是否出现在 words 中
public:  // 节点数据对外可见，方便直接访问 children
    Trie* children[26]{};  // 26 个小写字母子节点；{} 保证默认初始化为 nullptr

    void insert(string& word) {  // 把 word 插入字典树
        Trie* node = this;  // 从根节点开始向下建链
        for (char& c : word) {  // 逐字符向下走
            int i = c - 'a';  // 字母映射成 [0,25] 的子节点下标
            if (!node->children[i]) {  // 这个字母对应的子节点还不存在
                node->children[i] = new Trie();  // 新建一个节点挂上去
            }  // if 结束
            node = node->children[i];  // 走到该子节点，继续处理下一个字符
        }  // for 结束
    }  // insert 结束
};  // Trie 类结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minValidStrings(vector<string>& words, string target) {  // words：可反复使用的候选串；target：需要拼出的目标串
        int n = target.size();  // 目标串长度
        Trie* trie = new Trie();  // 建一棵空字典树
        for (auto& w : words) {  // 把所有候选串都插入字典树
            trie->insert(w);  // 插入单个候选串
        }  // for 结束
        const int inf = 1 << 30;  // 用一个足够大的数表示「拼不出来」
        int f[n];  // f[i]：拼出 target[i..] 所需的最少串数
        memset(f, -1, sizeof(f));  // 用 -1 标记该状态尚未计算
        auto dfs = [&](this auto&& dfs, int i) -> int {  // 记忆化递归 lambda：i 是 target 当前要拼到的下标
            if (i >= n) {  // 已经拼完整个 target
                return 0;  // 不需要更多串，返回 0
            }  // if 结束
            if (f[i] != -1) {  // 该状态计算过，直接复用
                return f[i];  // 返回记忆化结果
            }  // if 结束
            f[i] = inf;  // 先按「拼不出来」置初值，下面再逐步取最小
            Trie* node = trie;  // 从字典树根开始匹配
            for (int j = i; j < n; ++j) {  // 枚举以 i 开头的每一种可匹配长度
                int k = target[j] - 'a';  // 当前字符对应的子节点下标
                if (!node->children[k]) {  // 字典树里走不下去了
                    break;  // 更长的前缀都不可能匹配，直接停止
                }  // if 结束
                node = node->children[k];  // 沿字典树向下走一层，说明 prefix 又长一位
                f[i] = min(f[i], 1 + dfs(j + 1));  // 用 target[i..j] 作为一个串，再拼 j+1 之后的部分
            }  // for 结束
            return f[i];  // 返回从 i 开始拼所需的最少串数
        };  // 递归 lambda 定义结束
        int ans = dfs(0);  // 从 target 开头开始拼
        return ans < inf ? ans : -1;  // 拼不出来（仍为 inf）时按题意返回 -1
    }  // minValidStrings 结束
};  // Solution 类结束
