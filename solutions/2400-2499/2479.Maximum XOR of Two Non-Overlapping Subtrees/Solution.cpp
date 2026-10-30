// 题目：2479. 两个不重叠子树的最大异或值（Maximum XOR of Two Non-Overlapping Subtrees）
// 思路：第一次后序 DFS 求出每棵子树的和 s[i]；第二次后序 DFS 在「离开节点」时才把 s[i] 插入 01-Trie，插入前先查询 Trie 中已有值（即与当前子树不重叠的其它子树）能得到的最大异或，从而保证两棵子树互不重叠。
// 时间复杂度：O(n·logC)，每个节点在 48 位 Trie 上走一趟；空间复杂度：O(n·logC)，Trie 节点总数。
using ll = long long;  // 类型别名：把 long long 写成 ll，子树和可能超出 int 范围

class Trie {  // 01-Trie：按二进制位从高到低保存子树和，用来求最大异或
public:  // 对外提供 insert 与 search
    vector<Trie*> children;  // 两个子节点：children[0] 走 0 位、children[1] 走 1 位
    string v;  // 原题解遗留的成员，本逻辑未使用，保留以免改动代码
    Trie()  // 构造函数
        : children(2) {}  // vector(2) 把两个子指针初始化成空指针

    void insert(ll x) {  // 把数值 x 的 48 个二进制位依次插入 Trie
        Trie* node = this;  // 从根节点开始往下走
        for (int i = 47; ~i; --i) {  // 从第 47 位（最高位）走到第 0 位，~i 在 i 变为 -1 时结束
            int v = (x >> i) & 1;  // 取出 x 的第 i 位，只能是 0 或 1
            if (!node->children[v]) node->children[v] = new Trie();  // 该位的分支不存在就新建一个 Trie 节点
            node = node->children[v];  // 沿着这一位继续向下
        }  // 结束位循环
    }  // 结束 insert

    ll search(ll x) {  // 在 Trie 中找一个数与 x 异或，使结果最大
        Trie* node = this;  // 从根开始匹配
        ll res = 0;  // 累积的最大异或结果
        for (int i = 47; ~i; --i) {  // 同样从最高位到最低位逐位贪心
            if (!node) return res;  // 节点为空说明没有可匹配的数（本题不会发生），直接返回已有结果
            int v = (x >> i) & 1;  // x 的第 i 位
            if (node->children[v ^ 1]) {  // 存在与当前位相反的分支时，这一位异或能得到 1，贪心优先走它
                res = res << 1 | 1;  // 结果左移一位，并把最低位置 1
                node = node->children[v ^ 1];  // 走向相反位分支
            } else {  // 没有相反位分支，只能走相同位，该位异或结果为 0
                res <<= 1;  // 结果左移一位，最低位补 0
                node = node->children[v];  // 走向相同位分支
            }  // 结束分支
        }  // 结束位循环
        return res;  // 返回这一对数的异或值
    }  // 结束 search
};  // 结束 Trie 类

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxXor(int n, vector<vector<int>>& edges, vector<int>& values) {  // n：节点数；edges：无向边；values：点权；返回两棵不重叠子树和的最大异或值
        vector<vector<int>> g(n);  // 邻接表建图，g[i] 存节点 i 的所有邻居
        for (auto& e : edges) {  // 遍历每条无向边
            int a = e[0], b = e[1];  // 取边的两个端点
            g[a].emplace_back(b);  // a 的邻居列表加上 b
            g[b].emplace_back(a);  // b 的邻居列表加上 a（无向边要存两次）
        }  // 结束建图
        vector<ll> s(n);  // s[i]：以 i 为根的子树点权之和
        function<ll(int, int)> dfs1 = [&](int i, int fa) -> ll {  // 第一次 DFS（后序）：自底向上累加子树和；i 是当前节点，fa 是父节点（-1 表示根）
            ll t = values[i];  // 先把自己这一份点权放进累加器
            for (int j : g[i]) {  // 遍历所有邻居
                if (j != fa) t += dfs1(j, i);  // 跳过父节点，避免又走回上层
            }  // 结束邻居循环
            s[i] = t;  // 记下当前节点的子树和
            return t;  // 返回给父节点继续累加
        };  // lambda 定义结束
        dfs1(0, -1);  // 以 0 为根、父节点为 -1，启动第一次 DFS
        Trie tree;  // 建一棵空的 01-Trie，存放已经处理完的子树和
        ll ans = 0;  // 答案初值 0（异或不可能为负）
        function<void(int, int)> dfs2 = [&](int i, int fa) {  // 第二次 DFS（后序）：离开节点时才把它的子树和插入 Trie，保证查询到的另一棵子树不与它重叠
            ans = max(ans, tree.search(s[i]));  // 先查询：当前子树和与 Trie 中已有值的最大异或；此时 Trie 里只有不与 i 重叠的子树
            for (int j : g[i]) {  // 遍历邻居
                if (j != fa) {  // 跳过父节点
                    dfs2(j, i);  // 递归处理孩子（后序：孩子先入 Trie）
                }  // 结束 if
            }  // 结束邻居循环
            tree.insert(s[i]);  // 后序插入自己：此后才代表这棵子树「可被配对」，不会与自己重叠
        };  // lambda 定义结束
        dfs2(0, -1);  // 启动第二次 DFS
        return ans;  // 返回最大异或值
    }  // 结束题解方法
};  // 结束题解类
