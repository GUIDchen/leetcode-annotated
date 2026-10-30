// 题目：2213. 由单个字符重复的最长子字符串（Longest Substring of One Repeating Character）
// 思路：线段树每个节点维护左端起 lmx、右端起 rmx 与区间内最长 mx，单点修改后逐层 pushup 合并，根节点 mx 即答案。
// 时间复杂度：O((n + k) log n)，建树 O(n)、每次修改 O(log n)；空间复杂度：O(n)，节点池开 4n。
class Node {  // 线段树节点：保存区间 [l, r] 以及该区间内的最长同字符信息
public:  // 字段对外可见，方便 pushup 直接读取
    int l, r;  // 区间左右端点，这里统一用 1-based 下标，避免与 0 混淆
    int lmx, rmx, mx;  // lmx：左端起最长同字符长度；rmx：右端起；mx：区间内最长

    Node(int l, int r)  // 构造函数：给定区间端点，三个长度先按 1 初始化
        : l(l)  // 记录区间左端点
        , r(r)  // 记录区间右端点
        , lmx(1)  // 单个位置自身也算长度为 1 的重复串
        , rmx(1)  // 右端起同理，先给 1
        , mx(1) {}  // 区间内最长同理，先给 1
};

class SegmentTree {  // 线段树：支持单点修改，并能快速回答全局最长同字符子串
private:  // 以下内部实现不对外暴露
    string s;  // 字符数组的副本，pushup 时用它比较交界两侧字符是否相同
    vector<Node*> tr;  // 节点池：下标 u 的左右儿子分别是 u<<1 与 u<<1|1

    void build(int u, int l, int r) {  // 递归建树：为区间 [l, r] 分配并初始化节点编号 u
        tr[u] = new Node(l, r);  // 先创建当前节点，登记它负责的区间
        if (l == r) {  // 递归到叶子：区间里只剩一个字符
            return;  // 叶子没有子节点需要合并，直接回溯
        }
        int mid = (l + r) >> 1;  // 取中点，把区间一分为二
        build(u << 1, l, mid);  // 递归建左子树 [l, mid]
        build(u << 1 | 1, mid + 1, r);  // 递归建右子树 [mid + 1, r]
        pushup(u);  // 左右子树就绪后，自底向上合并信息
    }

    void pushup(int u) {  // 合并：用左右儿子的信息刷新当前节点 u
        Node* root = tr[u];  // 取出当前节点与左右儿子，便于下文书写
        Node* left = tr[u << 1];
        Node* right = tr[u << 1 | 1];
        root->mx = max(left->mx, right->mx);  // 区间最大值至少是左右儿子各自最大值的较大者
        root->lmx = left->lmx;  // 左端起的最长重复串默认继承左儿子的 lmx
        root->rmx = right->rmx;  // 右端起的最长重复串默认继承右儿子的 rmx
        int a = left->r - left->l + 1;  // a、b 是左右儿子的区间长度，用于判断是否整段同字符
        int b = right->r - right->l + 1;
        if (s[left->r - 1] == s[right->l - 1]) {  // 只有交界两侧字符相同，才可能跨区间拼接
            if (left->lmx == a) {  // 左儿子整段同字符，左前缀才能继续向右延伸
                root->lmx += right->lmx;  // 左端起长度 = 左儿子全长 + 右儿子的左前缀
            }
            if (right->rmx == b) {  // 右儿子整段同字符，右后缀才能继续向左延伸
                root->rmx += left->rmx;  // 右端起长度 = 右儿子全长 + 左儿子的右后缀
            }
            root->mx = max(root->mx, left->rmx + right->lmx);  // 跨交界的最长串 = 左儿子后缀 + 右儿子前缀，与已有最大值取较大者
        }
    }

public:  // 以下是对外接口
    SegmentTree(const string& s)  // 构造函数：用给定字符串建立整棵线段树
        : s(s) {  // 保存字符副本，后序 pushup 比较字符时使用
        int n = s.size();  // n 是串长，节点编号取值范围是 [1, n]
        tr.resize(n * 4);  // 4n 是线段树的安全上界，避免越界
        build(1, 1, n);  // 从根节点 1 开始递归建整棵树
    }

    void modify(int u, int x, char v) {  // 单点修改：把 1-based 下标 x 处的字符改成 v
        if (tr[u]->l == x && tr[u]->r == x) {  // 走到长度为 1 的叶子，说明定位到了目标位置
            s[x - 1] = v;  // 真正写入新字符（内部下标从 0 开始，所以减 1）
            return;  // 叶子没有子节点可合并，回溯
        }
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 按中点判断目标位置落在左子树还是右子树
        if (x <= mid) {  // 目标在左半区间
            modify(u << 1, x, v);  // 递归修改左子树
        } else {  // 否则目标在右半区间
            modify(u << 1 | 1, x, v);  // 递归修改右子树
        }
        pushup(u);  // 子树发生变化，重新合并当前节点
    }

    int query(int u, int l, int r) {  // 区间查询：返回 [l, r] 内的最长同字符长度
        if (tr[u]->l >= l && tr[u]->r <= r) {  // 当前节点区间被查询区间完全覆盖，直接返回其 mx
            return tr[u]->mx;  // 命中已维护好的值，直接返回
        }
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 取中点，判断查询区间落在哪一侧
        int ans = 0;  // 答案初值 0，等待子区间结果来更新
        if (r <= mid) {  // 查询区间完全落在左半边
            ans = query(u << 1, l, r);  // 只需查左子树
        } else if (l > mid) {  // 查询区间完全落在右半边（否则说明跨中点）
            ans = max(ans, query(u << 1 | 1, l, r));  // 与已有答案取较大者，再交给右子树结果
        }
        return ans;  // 返回查询区间内的最长重复长度
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {  // s 为初始串；queryCharacters 是每次替换的字符；queryIndices 是替换位置
        SegmentTree tree(s);  // 用初始字符串建树，后续所有修改与查询都在树上完成
        int k = queryIndices.size();  // k 是修改次数，也就是需要返回的答案个数
        vector<int> ans(k);  // 预分配答案数组，避免循环中反复扩容
        int n = s.size();  // n 是串长，查询区间固定为整段 [1, n]
        for (int i = 0; i < k; ++i) {  // 依次处理每一次替换
            int x = queryIndices[i] + 1;  // 题目下标从 0 开始，线段树内部从 1 开始，因此加 1
            char v = queryCharacters[i];  // 取出本次要写入的新字符
            tree.modify(1, x, v);  // 先做单点修改，沿路径合并维护信息
            ans[i] = tree.query(1, 1, n);  // 根节点保存整段的最长重复长度，正是本题要的答案
        }
        return ans;  // 返回每次修改后的答案
    }
};