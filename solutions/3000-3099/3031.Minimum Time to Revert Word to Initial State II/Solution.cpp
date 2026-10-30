// 题目：3031. 将单词恢复初始状态所需的最短时间 II（Minimum Time to Revert Word to Initial State II）
// 思路：把「剩余后缀等于原串等长前缀」的比较换成字符串哈希比较，预处理前缀哈希后每次判断 O(1)，从 i = k 起枚举删除的字符数。
// 时间复杂度：O(n)，预处理 O(n) 加至多 n/k 次 O(1) 查询；空间复杂度：O(n)，存幂次数组与前缀哈希数组。
class Hashing {  // 字符串哈希工具类：预处理幂次与前缀哈希，支持 O(1) 求子串哈希
private:  // 以下数据只在内部使用
    vector<long long> p;  // p[i]：base 的 i 次方对 mod 取模的结果
    vector<long long> h;  // h[i]：前缀 word[0..i-1] 的哈希值
    long long mod;  // 取模用的模数，供 query 里做差分时使用

public:  // 对外提供构造与查询接口
    Hashing(string word, long long base, int mod) {  // word：待预处理字符串；base：进制；mod：模数
        int n = word.size();  // 字符串长度
        p.resize(n + 1);  // 幂次数组开到 n+1，下标从 1 开始对齐前缀长度
        h.resize(n + 1);  // 前缀哈希数组同样开到 n+1
        p[0] = 1;  // base 的 0 次方等于 1，作为递推初值
        this->mod = mod;  // 形参与成员同名，用 this-> 区分并保存模数
        for (int i = 1; i <= n; i++) {  // 递推预处理幂次与前缀哈希
            p[i] = (p[i - 1] * base) % mod;  // 幂次递推：base^i = base^(i-1) * base
            h[i] = (h[i - 1] * base + word[i - 1] - 'a') % mod;  // 前缀哈希递推，字符先映射成 0..25 的整数
        }
    }

    long long query(int l, int r) {  // 求 1 基下标区间 [l, r] 的子串哈希
        return (h[r] - h[l - 1] * p[r - l + 1] % mod + mod) % mod;  // 差分后加 mod 再取模，避免出现负数
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumTimeToInitialState(string word, int k) {  // word：初始单词；k：每秒删除的字符数
        Hashing hashing(word, 13331, 998244353);  // 用固定进制与模数预处理整串哈希
        int n = word.size();  // 单词长度
        for (int i = k; i < n; i += k) {  // i 是已删除的字符数，只能是 k 的整数倍
            if (hashing.query(1, n - i) == hashing.query(i + 1, n)) {  // 原串前缀 [1, n-i] 与剩余后缀 [i+1, n] 哈希相同
                return i / k;  // 说明删掉 i 个字符后补字符即可复原，耗时 i/k 秒
            }
        }
        return (n + k - 1) / k;  // 单词删空后仍要补满一段字符，向上取整得到总秒数
    }
};