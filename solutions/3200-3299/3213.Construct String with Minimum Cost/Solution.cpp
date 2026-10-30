// 题目：3213. 最小代价构造字符串（Construct String with Minimum Cost）
// 思路：用字符串哈希把每个单词记成「哈希值 → 最小代价」，再令 f[i] 为拼出 target 前 i 个字符的最小代价，枚举出现过的单词长度并用哈希 O(1) 校验子串后转移。
// 时间复杂度：O(n · L)，n 为目标串长度、L 为不同单词长度个数；空间复杂度：O(n) 存前缀哈希与 DP 数组。
class Hashing {  // 字符串哈希封装：预处理 base 的幂与前缀哈希，支持 O(1) 求任意子串哈希
private:  // 以下为私有成员
    vector<long> p, h;  // p[i] = base^i，h[i] = word 前 i 个字符的前缀哈希
    long mod;  // 模数，用于控制哈希值范围并减少冲突

public:  // 以下成员对外可见
    Hashing(const string& word, long base, long mod)  // word：待哈希的原串；base：进制；mod：模数
        : p(word.size() + 1, 1)  // 初始化 p 为全 1（其中 p[0] = 1）
        , h(word.size() + 1, 0)  // 前缀哈希 h 全部初始化为 0
        , mod(mod) {  // 保存模数供 query 使用
        for (int i = 1; i <= word.size(); ++i) {  // 从前往后递推每一位的幂与前缀哈希
            p[i] = p[i - 1] * base % mod;  // p[i] = base^i mod mod
            h[i] = (h[i - 1] * base + word[i - 1]) % mod;  // h[i] = (h[i-1] * base + word[i-1]) mod mod
        }
    }

    long query(int l, int r) {  // 取子串 word[l-1..r-1] 的哈希值（l、r 为 1 基下标）
        return (h[r] - h[l - 1] * p[r - l + 1] % mod + mod) % mod;  // 用前缀哈希差分还原区间哈希，+mod 防止出现负数
    }
};  // Hashing 类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {  // target：目标串；words：可拼接的单词；costs：对应代价
        const int base = 13331;  // 哈希进制，取一个大于字符集大小的质数
        const int mod = 998244353;  // 大质数模数，降低哈希冲突概率
        const int inf = INT_MAX / 2;  // 用 INT_MAX / 2 表示无穷大，避免加法溢出

        int n = target.size();  // 目标串长度
        Hashing hashing(target, base, mod);  // 预先计算 target 的前缀哈希，供后面 O(1) 取子串哈希

        vector<int> f(n + 1, inf);  // f[i]：拼出 target 前 i 个字符所需的最小代价
        f[0] = 0;  // 空串的代价为 0

        set<int> ss;  // 收集所有单词出现过的长度，set 自动去重并按升序排列
        for (const string& w : words) {  // 逐个单词取长度
            ss.insert(w.size());  // 插入长度，重复长度自动被去重
        }

        unordered_map<long, int> d;  // d：单词哈希值 → 该单词的最小代价
        for (int i = 0; i < words.size(); ++i) {  // 逐个单词计算哈希并更新最小代价
            long x = 0;  // 当前单词的哈希初值为 0
            for (char c : words[i]) {  // 逐字符滚动计算整个单词的哈希
                x = (x * base + c) % mod;  // 多项式哈希递推
            }
            d[x] = d.find(x) == d.end() ? costs[i] : min(d[x], costs[i]);  // 同一哈希可能由多个单词产生，取更小的代价；首次出现则直接记录
        }

        for (int i = 1; i <= n; ++i) {  // 按前缀长度从小到大做 DP
            for (int j : ss) {  // 枚举每一种可能的单词长度
                if (j > i) {  // 长度超过当前位置时，后面更长的长度也不可能放下
                    break;  // 因 ss 升序，直接结束本层枚举
                }
                long x = hashing.query(i - j + 1, i);  // O(1) 取出 target[i-j+1..i] 的哈希值
                if (d.contains(x)) {  // 该哈希确实对应一个单词
                    f[i] = min(f[i], f[i - j] + d[x]);  // 状态转移：用代价 d[x] 拼上这一段
                }
            }
        }

        return f[n] >= inf ? -1 : f[n];  // 整个 target 无法拼出时返回 -1
    }
};