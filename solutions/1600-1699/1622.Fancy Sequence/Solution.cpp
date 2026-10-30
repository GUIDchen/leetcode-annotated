// 题目：1622. 奇妙序列（Fancy Sequence）
// 思路：用带「先乘后加」双懒标记的线段树维护序列，append 是单点赋值，addAll/multAll 是整段乘加，getIndex 是单点查询。
// 时间复杂度：append/addAll/multAll/getIndex 均为 O(log V)，V 为下标上限 1e5；空间复杂度：O(V)，动态开点的线段树。
const int MOD = 1e9 + 7;  // 全局取模常量，所有运算结果都对它取模

class Node {  // 线段树节点：维护一段区间的和，以及「先乘后加」两个懒标记
public:  // public:
    Node* left = nullptr;  // 左儿子指针，初始为空，真正用到时才动态创建
    Node* right = nullptr;  // 右儿子指针，同样在用到时才创建
    int l, r, mid;  // 该节点负责的区间是 [l, r]，mid 是区间中点
    long long v = 0, add = 0, mul = 1;  // v：区间和；add：加法懒标记；mul：乘法懒标记（默认 1 表示不乘）

    Node(int l, int r)  // 构造函数：只确定区间范围，标记保持默认值
        : l(l)  // 初始化左端点 l
        , r(r)  // 初始化右端点 r
        , mid((l + r) >> 1) {}  // 右移一位等价于除以 2 求中点，函数体为空
};

class SegmentTree {  // 线段树：支持区间乘、区间加与单点查询
public:  // public:
    SegmentTree()  // 构造函数：根节点覆盖下标 1..1e5+1（多开一位防止越界）
        : root(new Node(1, 1e5 + 1)) {}  // 区间上界取题目元素个数上限 1e5，再多留一位

    void modify(int l, int r, int mul, int add) {  // 对外接口：对区间 [l, r] 先乘 mul 再加 add
        modify(l, r, mul, add, root);  // 委托给带节点参数的递归实现，从根开始
    }

    int query(int l, int r) {  // 对外接口：查询区间 [l, r] 的元素之和
        return query(l, r, root);  // 同样从根节点开始递归查询
    }

private:  // private:
    Node* root;  // 线段树的根节点指针

    void modify(int l, int r, int mul, int add, Node* node) {  // 递归实现：在 node 子树上处理区间修改
        if (l > r) {  // 待修改区间为空，无需处理
            return;  // 直接返回
        }
        if (node->l >= l && node->r <= r) {  // 当前节点区间被待修改区间完全覆盖
            apply(node, mul, add);  // 整段打上懒标记，不再往下递归
            return;
        }
        pushdown(node);  // 部分覆盖：先下推父节点已有的标记，保证子节点数据正确
        if (l <= node->mid) {  // 待修改区间与左儿子有交集
            modify(l, r, mul, add, node->left);  // 递归修改左子树
        }
        if (r > node->mid) {  // 待修改区间与右儿子有交集
            modify(l, r, mul, add, node->right);  // 递归修改右子树
        }
        pushup(node);  // 用两个儿子的和重新计算当前节点的区间和
    }  // modify 递归实现结束

    int query(int l, int r, Node* node) {  // 递归实现：在 node 子树上查询区间 [l, r] 的和
        if (l > r) {  // 查询区间为空，贡献为 0
            return 0;  // 返回 0
        }
        if (node->l >= l && node->r <= r) {  // 当前节点区间被查询区间完全覆盖
            return node->v;  // 直接返回该节点维护好的区间和
        }
        pushdown(node);  // 查询前先下推标记，保证儿子的 v 是最新值
        int v = 0;  // 累加左右子树查询结果的变量
        if (l <= node->mid) {  // 左子树与查询区间有交集
            v = (v + query(l, r, node->left)) % MOD;  // 累加左子树结果并取模
        }
        if (r > node->mid) {  // 右子树与查询区间有交集
            v = (v + query(l, r, node->right)) % MOD;  // 累加右子树结果并取模
        }
        return v;  // 返回累加结果
    }  // query 递归实现结束

    void apply(Node* node, long long mul, long long add) {  // 把「先乘 mul 再加 add」整体作用到 node 所在区间
        node->v = (node->v * mul + (node->r - node->l + 1) * add) % MOD;  // 区间和更新：原和先乘 mul，再给每个元素加 add（共 len 个）
        node->add = (node->add * mul + add) % MOD;  // 新的加法标记要叠在旧标记上：旧标记本身也要被乘一次
        node->mul = node->mul * mul % MOD;  // 乘法标记直接累乘
    }  // apply 结束

    void pushup(Node* node) {  // 用儿子的信息更新当前节点
        node->v = (node->left->v + node->right->v) % MOD;  // 区间和等于左右儿子之和
    }  // pushup 结束

    void pushdown(Node* node) {  // 把当前节点的懒标记下推给两个儿子
        if (!node->left) {  // 左儿子为空则动态创建
            node->left = new Node(node->l, node->mid);  // 左儿子区间为 [l, mid]
        }
        if (!node->right) {  // 右儿子为空则动态创建
            node->right = new Node(node->mid + 1, node->r);  // 右儿子区间为 [mid+1, r]
        }
        if (node->add || node->mul != 1) {  // 只有存在待下推的标记（加非 0 或乘非 1）时才继续
            apply(node->left, node->mul, node->add);  // 把标记作用到左儿子
            apply(node->right, node->mul, node->add);  // 把标记作用到右儿子
            node->add = 0;  // 加法标记清零，表示已经下推
            node->mul = 1;  // 乘法标记复位为 1，表示已经下推
        }
    }  // pushdown 结束
};  // SegmentTree 类定义结束

class Fancy {  // 题目要求的 Fancy 类
public:  // public:
    void append(int val) {  // 在序列尾部追加一个值
        ++n;  // 元素个数加一，新元素的下标就是 n
        tree.modify(n, n, 1, val);  // 单点「赋值」：乘 1 再加 val，等价于把第 n 个位置置为 val
    }

    void addAll(int inc) {  // 给当前所有元素都加上 inc
        tree.modify(1, n, 1, inc);  // 对整个 [1, n] 区间做加法（乘法因子取 1）
    }

    void multAll(int m) {  // 给当前所有元素都乘上 m
        tree.modify(1, n, m, 0);  // 对整个 [1, n] 区间做乘法（加法因子取 0）
    }

    int getIndex(int idx) {  // 查询下标 idx（0 基）处的元素值
        return idx >= n ? -1 : tree.query(idx + 1, idx + 1);  // 越界返回 -1，否则把 0 基下标转成 1 基做单点查询
    }

private:  // private:
    int n = 0;  // 当前序列的元素个数
    SegmentTree tree;  // 用线段树维护所有元素的值
};  // Fancy 类定义结束
