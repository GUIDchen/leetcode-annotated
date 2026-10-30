// 题目：3292. 形成目标字符串需要的最少字符串数 II（Minimum Number of Valid Strings to Form Target II）
// 思路：字符串哈希 + 二分求出从每个位置出发能匹配的最长候选串前缀长度，再做一次类似「跳跃游戏」的贪心区间覆盖，得到最少串数。
// 时间复杂度：O((n + L) + n·log m)，n 为 target 长度、m 为最长候选串长度、L 为 words 总长；空间复杂度：O(n + L)。
class Hashing {  // 字符串哈希工具类：O(1) 判断任意子串是否出现在候选串前缀集合中
private:  // 以下为内部数据成员
    vector<long long> p;  // p[i] = base^i mod mod，用于对齐不同起点子串的哈希
    vector<long long> h;  // h[i] 是前缀 word[0..i) 的哈希值
    long long mod;  // 取模用的模数

public:  // 以下为对外接口
    Hashing(const string& word, long long base, int mod) {  // 构造函数：预处理 word 的幂数组与前缀哈希
        int n = word.size();  // 串长
        p.resize(n + 1);  // 幂数组长度为 n+1
        h.resize(n + 1);  // 前缀哈希数组长度为 n+1
        p[0] = 1;  // base^0 = 1
        this->mod = mod;  // 保存模数，query() 里要用
        for (int i = 1; i <= n; i++) {  // 递推计算幂与前缀哈希
            p[i] = (p[i - 1] * base) % mod;  // p[i] = p[i-1] * base
            h[i] = (h[i - 1] * base + word[i - 1]) % mod;  // h[i] = h[i-1] * base + word[i-1]（字符用 ASCII 值参与计算）
        }  // for 结束
    }  // 构造函数结束

    long long query(int l, int r) {  // 查询子串 word[l-1..r) 的哈希（下标从 1 开始）
        return (h[r] - h[l - 1] * p[r - l + 1] % mod + mod) % mod;  // 前缀哈希相减并补 mod 防止负数，得到这段区间的哈希
    }  // query 结束
};  // Hashing 类结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minValidStrings(vector<string>& words, string target) {  // words：候选串集合；target：目标串
        int base = 13331, mod = 998244353;  // 哈希的进制与模数
        Hashing hashing(target, base, mod);  // 预先算出 target 的幂数组与前缀哈希
        int m = 0, n = target.size();  // m 记录候选串的最大长度，n 是 target 的长度
        for (const string& word : words) {  // 求候选串的最大长度
            m = max(m, (int) word.size());  // 更新最大长度：匹配长度不可能超过它
        }  // for 结束

        vector<unordered_set<long long>> s(m + 1);  // s[len] 存放所有候选串中长度恰为 len 的前缀哈希
        for (const string& w : words) {  // 遍历每个候选串，把它的所有前缀哈希分类存起来
            long long h = 0;  // 滚动累积当前前缀的哈希
            for (int j = 0; j < w.size(); j++) {  // 枚举候选串的每一个前缀
                h = (h * base + w[j]) % mod;  // 滚动计算前缀哈希
                s[j + 1].insert(h);  // 把长度为 j+1 的前缀哈希放进对应的桶
            }  // for 结束
        }  // for 结束

        auto f = [&](int i) -> int {  // 二分求：从 target[i] 开始最多能匹配多长的候选串前缀
            int l = 0, r = min(n - i, m);  // 长度上界：不能越过 target 末尾，也不超过最长候选串
            while (l < r) {  // 二分查找最大的可行长度
                int mid = (l + r + 1) >> 1;  // 向上取整的中点，保证区间一定会收缩
                long long sub = hashing.query(i + 1, i + mid);  // target[i..i+mid) 这段的哈希
                if (s[mid].count(sub)) {  // 长度 mid 的候选串前缀里存在这个哈希，说明可以匹配
                    l = mid;  // 可行，尝试更长
                } else {  // 否则不可行
                    r = mid - 1;  // 缩短上界
                }  // if 结束
            }  // while 结束
            return l;  // l 就是最大可匹配长度
        };  // lambda 定义结束

        int ans = 0, last = 0, mx = 0;  // ans：最少串数；last：当前这串覆盖到的最右端；mx：所有已覆盖段能达到的最右端
        for (int i = 0; i < n; i++) {  // 逐位置扫描 target
            int dist = f(i);  // 从 i 开始最多能匹配的长度
            mx = max(mx, i + dist);  // 更新可达的最右端（开区间）
            if (i == last) {  // 走到当前覆盖边界，必须新开一个串
                if (i == mx) {  // 连一个字符都匹配不了，说明永远拼不出 target
                    return -1;  // 按题意返回 -1
                }  // if 结束
                last = mx;  // 新的一段能覆盖到 mx
                ans++;  // 串数加一
            }  // if 结束
        }  // for 结束
        return ans;  // 返回最少串数
    }  // minValidStrings 结束
};  // Solution 类结束
