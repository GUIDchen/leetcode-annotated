// 题目：2445. 值为 1 的节点数（Number of Nodes With Value One，🔒 会员题）
// 思路：同一节点被翻转偶数次等于没翻，故只对查询次数为奇数的节点做 DFS，把该子树的值整体异或 1，最后统计 1 的个数。
// 时间复杂度：O(q + 各奇数查询节点的子树大小之和)，最坏 O(n·q)；空间复杂度：O(n)，tree/cnt 两个数组加上递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfNodes(int n, vector<int>& queries) {  // n 是节点总数（编号 1..n），queries 是每次翻转子树的根节点
        vector<int> tree(n + 1);  // tree[i] 是节点 i 的值，下标 0 弃用，初始全为 0
        vector<int> cnt(n + 1);  // cnt[i] 统计节点 i 作为查询根出现了几次
        for (int v : queries) ++cnt[v];  // 一次遍历把每个查询累加到对应节点的计数上
        function<void(int)> dfs = [&](int i) {  // 递归 lambda：以 i 为根，把整棵子树的值翻转一次
            if (i > n) return;  // 编号超过 n 说明是空子树，递归终止
            tree[i] ^= 1;  // 与 1 异或实现 0/1 翻转
            dfs(i << 1);  // 递归翻转左儿子 2*i
            dfs(i << 1 | 1);  // 递归翻转右儿子 2*i+1；移位优先级高于按位或
        };  // lambda 定义结束
        for (int i = 0; i < n + 1; ++i) {  // 把 0..n 每个节点都检查一遍
            if (cnt[i] & 1) {  // 只有被查询奇数次才真正生效，偶数次互相抵消
                dfs(i);  // 以 i 为根翻转整棵子树
            }
        }
        return accumulate(tree.begin(), tree.end(), 0);  // 求和即值为 1 的节点个数（下标 0 恒为 0，不影响结果）
    }
};  // 类定义结束