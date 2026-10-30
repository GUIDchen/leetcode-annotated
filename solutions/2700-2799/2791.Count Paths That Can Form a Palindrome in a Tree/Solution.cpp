// 题目：2791. 树中可以形成回文的路径数（Count Paths That Can Form a Palindrome in a Tree）
// 思路：把字母映射成二进制位，用根到节点的路径异或值做前缀；两节点间的路径异或值只有 0 个或 1 个二进制位时为可回文，用哈希表累计配对。
// 时间复杂度：O(n * 26)，每个节点查询 26 个状态（26 为常量，可视为 O(n)）；空间复杂度：O(n)，存邻接表与哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countPalindromePaths(vector<int>& parent, string s) {  // parent：每个节点的父节点；s：节点到父节点这条边上的字母
        int n = parent.size();  // 节点总数
        vector<vector<pair<int, int>>> g(n);  // 邻接表：g[p] 存放 (子节点, 该边字母对应的二进制位)
        unordered_map<int, int> cnt;  // 哈希表：键是「根到某节点的路径异或值」，值是该值出现的次数
        cnt[0] = 1;  // 空前缀的异或值为 0，先记一次，用来表示以根为起点的路径
        for (int i = 1; i < n; ++i) {  // 0 号节点是根，从 1 号节点开始建边
            int p = parent[i];  // 当前节点的父节点
            g[p].emplace_back(i, 1 << (s[i] - 'a'));  // 用 1 << (字母偏移) 作为边权，表示这条边让该字母出现次数加一
        }  // 建边循环结束
        long long ans = 0;  // ans：满足回文条件的路径对数（long long 防止计数溢出）
        function<void(int, int)> dfs = [&](int i, int xo) {  // 深度优先搜索：i 是当前节点，xo 是根到 i 的路径异或值
            for (auto [j, v] : g[i]) {  // 遍历当前节点的全部子节点，v 是这条边的字母掩码
                int x = xo ^ v;  // 根到子节点 j 的路径异或值
                ans += cnt[x];  // 之前出现过相同异或值，说明两段路径异或为 0，所有字母都是偶数次，可构成回文
                for (int k = 0; k < 26; ++k) {  // 再枚举「允许恰好一个字母出现奇数次」的 26 种情形
                    ans += cnt[x ^ (1 << k)];  // 异或值只差一个二进制位时，两段路径之间只有一种字母为奇数个，同样可构成回文
                }  // 内层枚举结束
                ++cnt[x];  // 把当前异或值的出现次数加一，供后续子树查询
                dfs(j, x);  // 继续向子树深入
            }  // 子节点循环结束
        };  // lambda 定义结束
        dfs(0, 0);  // 从根节点开始搜索，根到根的路径异或值为 0
        return ans;  // 返回可构成回文的路径总数
    }  // 方法结束
};  // 类定义结束
