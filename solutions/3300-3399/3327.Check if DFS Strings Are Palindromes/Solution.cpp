// 题目：3327. 判断 DFS 字符串是否是回文串（Check if DFS Strings Are Palindromes）
// 思路：先 DFS 建出整棵树的字符串 dfsStr 并记下每个子树占据的区间；再用正序、逆序两套字符串哈希，以 O(1) 判定该区间是否回文。
// 时间复杂度：O(n)，建串与每个子树的判定都是常数次哈希查询；空间复杂度：O(n)，邻接表、dfsStr、区间数组与两张哈希表都是线性。
class Hashing {  // 字符串哈希小工具：预处理前缀哈希与幂次表
private:  // 内部状态不对外暴露
    vector<long long> p;  // p[i] = base^i，用于把两段哈希对齐到同一幂次
    vector<long long> h;  // h[i] 是前 i 个字符的哈希值
    long long mod;  // 取模用的大质数，每个实例各自保存

public:  // 对外接口
    Hashing(string word, long long base, int mod) {  // word 是待哈希的串，base 是进制，mod 是模数
        int n = word.size();  // 串长，哈希与幂次数组都要多开一位给空前缀
        p.resize(n + 1);  // 幂次表长度 n+1
        h.resize(n + 1);  // 前缀哈希表长度 n+1
        p[0] = 1;  // base^0 = 1，递推的起点
        this->mod = mod;  // 参数 mod 遮蔽了同名成员，必须用 this-> 区分
        for (int i = 1; i <= n; i++) {  // 从第 1 位递推到第 n 位
            p[i] = (p[i - 1] * base) % mod;  // 幂次递推：p[i] = p[i-1] * base
            h[i] = (h[i - 1] * base + word[i - 1] - 'a') % mod;  // 前缀哈希递推：整体左移一位再补上新字符（映射成 0..25）
        }  // 预处理结束
    }  // 构造函数结束

    long long query(int l, int r) {  // 查询闭区间 [l, r] 的哈希，下标从 1 开始
        return (h[r] - h[l - 1] * p[r - l + 1] % mod + mod) % mod;  // 先乘幂次对齐再相减，末尾 +mod 防止负数取模
    }  // query 结束
};  // Hashing 类结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<bool> findAnswer(vector<int>& parent, string s) {  // parent 是父节点数组（根为 0），s 是每个节点上的字符
        int n = s.size();  // 节点个数等于字符个数
        vector<int> g[n];  // 邻接表：g[u] 存 u 的所有孩子，树由 parent 数组给出
        for (int i = 1; i < n; ++i) {  // 除根节点外逐个挂到父节点下
            g[parent[i]].push_back(i);  // 记录父子边，孩子的先后顺序与输入一致
        }  // 建图结束
        string dfsStr;  // 整棵树的 DFS 字符串：孩子依次续接，最后补自己的字符
        vector<pair<int, int>> pos(n);  // pos[i] 存子树 i 在 dfsStr 中占据的区间（1 基下标）
        auto dfs = [&](this auto&& dfs, int i) -> void {  // 递归 lambda：this auto&& 让 lambda 能调用自身
            int l = dfsStr.size() + 1;  // 区间左端就是当前串长的下一个位置
            for (int j : g[i]) {  // 先按顺序递归所有孩子
                dfs(j);  // 孩子的字符会先写进 dfsStr
            }  // 孩子遍历完
            dfsStr.push_back(s[i]);  // 最后才写自己，正好是后序遍历的顺序
            int r = dfsStr.size();  // 写完后串长就是区间右端
            pos[i] = {l, r};  // 记下子树对应的连续区间
        };  // lambda 定义结束
        dfs(0);  // 从根节点开始遍历

        const int base = 13331;  // 常用的哈希进制
        const int mod = 998244353;  // 常用的哈希模数
        Hashing h1(dfsStr, base, mod);  // 正序串的哈希，用来取区间的前半段
        reverse(dfsStr.begin(), dfsStr.end());  // 原地反转，得到逆序串
        Hashing h2(dfsStr, base, mod);  // 逆序串的哈希，用来取区间后半段的反向
        vector<bool> ans(n);  // 每个节点一个答案
        for (int i = 0; i < n; ++i) {  // 逐个节点判断它的 DFS 串是否回文
            auto [l, r] = pos[i];  // 结构化绑定取出区间端点
            int k = r - l + 1;  // 区间长度，也就是这棵子树的节点数
            long long v1 = h1.query(l, l + k / 2 - 1);  // 区间前一半的哈希
            long long v2 = h2.query(n - r + 1, n - r + 1 + k / 2 - 1);  // 区间后一半倒序后的哈希，下标换算到逆序串上
            ans[i] = v1 == v2;  // 两半相等即回文；奇数长度时中间字符无需比较
        }  // 判定结束
        return ans;  // 返回每个节点的判定结果
    }  // 方法结束
};  // 类定义结束
