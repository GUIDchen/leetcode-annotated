// 题目：2158. 每天绘制新区域的数量（Amount of New Area Painted Each Day）
// 核心思路：线段树维护区间被覆盖的长度；每天先查询该区间已覆盖多少，用区间长度减去它得到新增面积，再把整段置为已覆盖。
// 时间复杂度：O(n log V)，V 为坐标值域；空间复杂度：O(V)，线段树节点数随递归下探按需创建。
class Node {  // 线段树节点
public:  // 成员对外可见
    Node* left;  // 左子节点指针
    Node* right;  // 右子节点指针
    int l;  // 区间左端点
    int r;  // 区间右端点
    int mid;  // 区间中点，用来划分左右子节点
    int v;  // 该区间内已被覆盖的长度
    int add;  // 懒标记：标记整段被覆盖的状态，0 表示没有待下传的标记

    Node(int l, int r) {  // 构造一个覆盖 [l, r] 的节点
        this->l = l;  // 记录区间左端点
        this->r = r;  // 记录区间右端点
        this->mid = (l + r) >> 1;  // 用右移一位代替整除 2 计算中点
        this->left = this->right = nullptr;  // 子节点延迟创建，先置空
        v = add = 0;  // 初始未被覆盖，也没有懒标记
    }  // 构造函数结束
};  // 节点类定义结束

class SegmentTree {  // 支持区间置覆盖与区间查询覆盖长度的线段树
private:  // 内部实现细节，不对外暴露
    Node* root;  // 线段树根节点

public:  // 对外接口
    SegmentTree() {  // 构造函数：建立一棵空线段树
        root = new Node(1, 100010);  // 坐标从 1 开始，开到 100010 足以覆盖题目给出的坐标范围
    }  // 构造函数结束

    void modify(int l, int r, int v) {  // 对外接口：把区间 [l, r] 的覆盖状态改成 v
        modify(l, r, v, root);  // 交给递归实现，从根节点开始
    }  // 入口重载结束

    void modify(int l, int r, int v, Node* node) {  // 递归修改：node 为当前节点
        if (l > r) return;  // 空区间，什么都不用做
        if (node->l >= l && node->r <= r) {  // 当前节点区间被目标区间完全包含
            node->v = node->r - node->l + 1;  // 整段都被覆盖，覆盖长度就等于区间长度
            node->add = v;  // 打上懒标记，标记这次整体覆盖的状态
            return;  // 无需继续递归
        }  // 完全覆盖分支结束
        pushdown(node);  // 只是部分覆盖，先把父节点的懒标记下传给子节点
        if (l <= node->mid) modify(l, r, v, node->left);  // 左半区间与目标区间有交集，递归修改左子节点
        if (r > node->mid) modify(l, r, v, node->right);  // 右半区间与目标区间有交集，递归修改右子节点
        pushup(node);  // 由子节点的覆盖长度更新当前节点
    }  // 递归修改结束

    int query(int l, int r) {  // 对外接口：查询区间 [l, r] 已被覆盖的长度
        return query(l, r, root);  // 从根节点开始递归查询
    }  // 入口重载结束

    int query(int l, int r, Node* node) {  // 递归查询：node 为当前节点
        if (l > r) return 0;  // 空区间没有覆盖
        if (node->l >= l && node->r <= r) return node->v;  // 当前节点区间被查询区间完全包含，直接返回其记录值
        pushdown(node);  // 要访问子节点，先把懒标记下传
        int v = 0;  // 覆盖长度累加器
        if (l <= node->mid) v += query(l, r, node->left);  // 左半区间有交集，累加左子树的覆盖长度
        if (r > node->mid) v += query(l, r, node->right);  // 右半区间有交集，累加右子树的覆盖长度
        return v;  // 返回查询区间内的总覆盖长度
    }  // 递归查询结束

    void pushup(Node* node) {  // 由子节点信息向上更新
        node->v = node->left->v + node->right->v;  // 父区间的覆盖长度等于左右子区间覆盖长度之和
    }  // pushup 结束

    void pushdown(Node* node) {  // 把当前节点的懒标记下传给子节点
        if (!node->left) node->left = new Node(node->l, node->mid);  // 左子节点不存在就按左半区间创建出来
        if (!node->right) node->right = new Node(node->mid + 1, node->r);  // 右子节点不存在就按右半区间创建出来
        if (node->add) {  // 只有存在懒标记时才需要下传
            Node* left = node->left;  // 取出左子节点，方便书写
            Node* right = node->right;  // 取出右子节点，方便书写
            left->v = left->r - left->l + 1;  // 左子区间被整段覆盖，覆盖长度等于其区间长度
            right->v = right->r - right->l + 1;  // 右子区间被整段覆盖，覆盖长度等于其区间长度
            left->add = node->add;  // 标记传给左子节点
            right->add = node->add;  // 标记传给右子节点
            node->add = 0;  // 清空当前节点的标记，避免重复下传
        }  // 下传分支结束
    }  // pushdown 结束
};  // 线段树类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> amountPainted(vector<vector<int>>& paint) {  // paint[i] = [start, end) 表示第 i 天刷的区间
        int n = paint.size();  // 刷墙的天数
        vector<int> ans(n);  // 保存每天新增的绘制长度
        SegmentTree* tree = new SegmentTree();  // 新建一棵全未覆盖的线段树
        for (int i = 0; i < n; ++i) {  // 按天依次处理
            int l = paint[i][0] + 1;  // 原区间左闭右开，线段树下标从 1 起，故左端点加一
            int r = paint[i][1];  // 原右端点是开区间，线段树中正好以 r 为闭端点
            int v = tree->query(l, r);  // 先查询这段区间里已经被刷过的长度
            ans[i] = r - l + 1 - v;  // 区间总长减去已覆盖长度，就是今天新增的面积
            tree->modify(l, r, 1);  // 把今天的区间标记为已覆盖，供后面几天查询
        }  // 逐天处理结束
        return ans;  // 返回每天的新增面积
    }  // 方法结束
};  // 题解类定义结束