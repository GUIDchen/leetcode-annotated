// 题目：1316. 不同的循环子字符串（Distinct Echo Substrings）
// 思路：用字符串哈希判等，枚举每个偶数长度子串并比较前后两半的哈希值，哈希值放进集合去重。
// 时间复杂度：O(n^2)，枚举区间 O(n^2) 而比较是 O(1)；空间复杂度：O(n)，前缀哈希与幂次数组。
typedef unsigned long long ull;  // 无符号长整型别名，用作可自然溢出的滚动哈希值类型

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int distinctEchoSubstrings(string text) {  // text 为输入字符串
        int n = text.size();  // 字符串长度 n
        int base = 131;  // 哈希基数 131，大于小写字母表大小
        vector<ull> p(n + 10);  // p[i] = base^i，用于拼接哈希时对齐幂次
        vector<ull> h(n + 10);  // h[i] 为 text 前 i 个字符的前缀哈希
        p[0] = 1;  // base^0 = 1，作为递推起点
        for (int i = 0; i < n; ++i) {  // 逐字符递推前缀哈希与幂次
            int t = text[i] - 'a' + 1;  // 字符映射到 1..26，避免 0 造成前导零歧义
            p[i + 1] = p[i] * base;  // 预计算幂次 base^(i+1)
            h[i + 1] = h[i] * base + t;  // 滚动哈希：h[i+1] = h[i] * base + 当前字符值
        }  // 前缀哈希构造结束
        unordered_set<ull> vis;  // 集合去重，记录出现过的「左半段」哈希值
        for (int i = 0; i < n - 1; ++i) {  // 枚举回声子串的起点 i
            for (int j = i + 1; j < n; j += 2) {  // 枚举终点 j，步长 2 保证子串长度为偶数，才能均分成两半
                int k = (i + j) >> 1;  // 中点 k：左半段为 [i, k]，右半段为 [k+1, j]
                ull a = get(i + 1, k + 1, p, h);  // 左半段哈希（哈希下标从 1 开始，故区间为 [i+1, k+1]）
                ull b = get(k + 2, j + 1, p, h);  // 右半段哈希（区间为 [k+2, j+1]）
                if (a == b) vis.insert(a);  // 两半哈希相同即为一回声子串，把哈希值放入集合去重
            }  // 内层循环结束：换下一个终点
        }  // 外层循环结束：换下一个起点
        return vis.size();  // 集合大小即不同回声子串的个数
    }  // 方法结束

    ull get(int l, int r, vector<ull>& p, vector<ull>& h) {  // 取字符串下标区间 [l, r]（1 起）的哈希值
        return h[r] - h[l - 1] * p[r - l + 1];  // 前缀哈希相减：左端整体右移后乘上缺失的幂次对齐
    }  // 辅助函数结束
};  // 类定义结束