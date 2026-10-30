// 题目：699. 掉落的方块（Falling Squares）
// 思路：坐标范围可达 1e9，用动态开点的线段树维护每个坐标区间的最高高度；每块方块查询其覆盖区间的最大高度并叠加上自身边长，再区间赋值，答案取历史最大。
// 时间复杂度：O(n log C)，每次查询与修改都是 log 级，C 为坐标上界 1e9；空间复杂度：O(n log C)，动态开点只创建被访问到的节点。
class Node {  // 线段树结点：表示坐标区间 [l, r] 上的高度信息
public:  // 结点字段对外可见，供线段树访问
    Node* left;  // 左儿子指针，用到时才动态创建
    Node* right;  // 右儿子指针，用到时才动态创建
    int l;  // 当前结点负责区间的左端点
    int r;  // 当前结点负责区间的右端点
    int mid;  // 区间中点，用于划分左右儿子
    int v;  // 该区间内的最大高度
    int add;  // 懒标记：非 0 表示整段区间已被统一赋值为 add

    Node(int l, int r) {  // 构造函数：给定区间端点创建一个结点
        this->l = l;  // 记录左端点（this-> 用于区分同名形参）
        this->r = r;  // 记录右端点
        this->mid = (l + r) >> 1;  // 用右移一位实现除以 2，得到中点
        this->left = this->right = nullptr;  // 子结点先置空，等 pushdown 时再按需创建
        v = add = 0;  // 初始高度为 0，且没有待下传的赋值标记
    }
};

class SegmentTree {  // 动态开点线段树，维护区间最大值并支持区间赋值
private:  // 根结点是内部实现细节
    Node* root;  // 线段树根结点，覆盖 1 到 1e9 的全部坐标

public:  // 对外提供构造、区间赋值与区间查询
    SegmentTree() {  // 构造函数：建立表示整个坐标范围的根结点
        root = new Node(1, 1e9);  // 方块横坐标与边长之和不超 1e9，因此根区间取 [1, 1e9]
    }

    void modify(int l, int r, int v) {  // 对外接口：把区间 [l, r] 的高度统一改成 v
        modify(l, r, v, root);  // 转交给递归版本，从根结点开始
    }

    void modify(int l, int r, int v, Node* node) {  // 递归实现：在 node 子树内把 [l, r] 赋值为 v
        if (l > r) return;  // 空区间直接返回，作为递归的兜底
        if (node->l >= l && node->r <= r) {  // 当前结点区间被目标区间完全覆盖
            node->v = v;  // 整段高度统一赋值，最大值自然就是 v
            node->add = v;  // 打上懒标记，等待子结点被访问时再下传
            return;  // 覆盖完毕，无需继续向下递归
        }
        pushdown(node);  // 未完全覆盖，先把懒标记下传给子结点
        if (l <= node->mid) modify(l, r, v, node->left);  // 目标区间与左半段有交集才去修改左子树
        if (r > node->mid) modify(l, r, v, node->right);  // 目标区间与右半段有交集才去修改右子树
        pushup(node);  // 子结点更新后，用它们的值重新计算当前结点的最大值
    }

    int query(int l, int r) {  // 对外接口：查询区间 [l, r] 内的最大高度
        return query(l, r, root);  // 转交给递归版本，从根结点开始
    }

    int query(int l, int r, Node* node) {  // 递归实现：在 node 子树内查询 [l, r] 的最大值
        if (l > r) return 0;  // 空区间没有高度，返回 0
        if (node->l >= l && node->r <= r) return node->v;  // 当前结点区间被完全覆盖，直接返回其最大值
        pushdown(node);  // 需要进入子结点前，先把懒标记下传保证子结点数据正确
        int v = 0;  // 记录本次查询的答案，初始为 0（高度非负）
        if (l <= node->mid) v = max(v, query(l, r, node->left));  // 与左半段有交集则递归查询左子树
        if (r > node->mid) v = max(v, query(l, r, node->right));  // 与右半段有交集则递归查询右子树
        return v;  // 返回两个子区间中的较大高度
    }

    void pushup(Node* node) {  // 用子结点的值更新父结点的最大值
        node->v = max(node->left->v, node->right->v);  // 父区间最大值等于左右儿子最大值的较大者
    }

    void pushdown(Node* node) {  // 访问子结点之前，把当前结点的懒标记下传
        if (!node->left) node->left = new Node(node->l, node->mid);  // 左儿子不存在则按左半区间动态创建
        if (!node->right) node->right = new Node(node->mid + 1, node->r);  // 右儿子不存在则按右半区间动态创建
        if (node->add) {  // 当前结点带有「整段赋值」的懒标记
            Node* left = node->left;  // 取左儿子指针，便于连续赋值
            Node* right = node->right;  // 取右儿子指针，便于连续赋值
            left->v = node->add;  // 把赋值结果传给左儿子的最大值
            right->v = node->add;  // 把赋值结果传给右儿子的最大值
            left->add = node->add;  // 左儿子也打上同样的懒标记，供更下层使用
            right->add = node->add;  // 右儿子也打上同样的懒标记，供更下层使用
            node->add = 0;  // 标记已下传，清空当前结点的懒标记
        }
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> fallingSquares(vector<vector<int>>& positions) {  // positions[i] = [left, size] 表示第 i 块方块的左边界与边长
        vector<int> ans;  // 依次记录每块方块落下后的全局最高高度
        SegmentTree* tree = new SegmentTree();  // 建立线段树来维护坐标轴上的高度
        int mx = 0;  // 当前全局最大高度
        for (auto& p : positions) {  // 按顺序处理每一块掉落的方块
            int l = p[0], w = p[1], r = l + w - 1;  // 左边界 l、边长 w，以及它占据的右边界 r
            int h = tree->query(l, r) + w;  // 落在 [l, r] 最高处之上，再加自身边长，得到本块顶部高度
            mx = max(mx, h);  // 用本块顶部高度更新全局最高高度
            ans.push_back(mx);  // 本题要求输出的是当前全局最大值，而非本块自身高度
            tree->modify(l, r, h);  // 把 [l, r] 这一整段的高度更新为本块顶部高度
        }
        return ans;  // 返回每块方块落下后的全局最高高度序列
    }
};
