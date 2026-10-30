// 题目：732. 我的日程安排表 III（My Calendar III）
// 思路：用动态开点线段树维护时间轴上的「区间加 1 + 查询全局最大值」，每次 book 把 [start, end) 加 1，再查询整段区间的最大重叠次数。
// 时间复杂度：每次 book 为 O(log C)，C 为时间轴范围 1e9；空间复杂度：O(k log C)，k 为预订次数（节点按需创建）。
class Node {  // 线段树节点：维护自己覆盖区间内的最大重叠次数与懒标记
public:  // 成员对外可见
    Node* left;  // 左儿子指针，动态开点，用到时才创建
    Node* right;  // 右儿子指针，动态开点，用到时才创建
    int l;  // 当前节点覆盖区间的左端点
    int r;  // 当前节点覆盖区间的右端点
    int mid;  // 区间中点，用于判断往哪个儿子递归
    int v;  // 本区间内的最大重叠次数
    int add;  // 懒标记：整段区间尚未下发给儿子的增量

    Node(int l, int r) {  // 构造函数：以区间 [l, r] 建立节点
        this->l = l;  // 记录左端点
        this->r = r;  // 记录右端点
        this->mid = (l + r) >> 1;  // 右移一位等价于除以 2，得到中点
        this->left = this->right = nullptr;  // 儿子延迟到 pushdown 时再创建，节省空间
        v = add = 0;  // 初始最大重叠次数与懒标记都为 0
    }  // 构造函数结束
};  // Node 类定义结束

class SegmentTree {  // 动态开点线段树：支持区间加与查询区间最大值
private:  // 私有成员区
    Node* root;  // 线段树根节点

public:  // 对外接口
    SegmentTree() {  // 构造函数：根节点覆盖整条时间轴 [1, 1e9+1]
        root = new Node(1, 1e9 + 1);  // 1e9 是 double 字面量，赋给 int 时隐式转换；整体右移一位以适配 1-based 时间轴
    }  // 构造函数结束

    void modify(int l, int r, int v) {  // 对区间 [l, r] 上的所有时刻整体加上 v
        modify(l, r, v, root);  // 从根节点开始递归修改
    }  // 对外重载的 modify 结束

    void modify(int l, int r, int v, Node* node) {  // 递归版本：在以 node 为根的区间上修改 [l, r]
        if (l > r) {  // 空区间直接返回（防御性判断）
            return;  // 无需处理
        }  // if 结束
        if (node->l >= l && node->r <= r) {  // 当前节点区间被 [l, r] 完全覆盖，可以打懒标记
            node->v += v;  // 本区间最大值整体加 v
            node->add += v;  // 懒标记累积，留给儿子以后再加
            return;  // 完全覆盖后无需继续下探
        }  // if 结束
        pushdown(node);  // 先保证儿子存在，并把父亲的懒标记下发
        if (l <= node->mid) {  // 左半边与修改区间有交集
            modify(l, r, v, node->left);  // 递归修改左儿子
        }  // if 结束
        if (r > node->mid) {  // 右半边与修改区间有交集
            modify(l, r, v, node->right);  // 递归修改右儿子
        }  // if 结束
        pushup(node);  // 两个儿子都更新完，用它们的最大值回填父亲
    }  // 递归 modify 结束

    int query(int l, int r) {  // 查询区间 [l, r] 内的最大重叠次数
        return query(l, r, root);  // 从根节点开始查询
    }  // 对外重载的 query 结束

    int query(int l, int r, Node* node) {  // 递归版本：在以 node 为根的区间内查询 [l, r]
        if (l > r) {  // 空区间返回 0
            return 0;  // 不产生任何贡献
        }  // if 结束
        if (node->l >= l && node->r <= r) return node->v;  // 被完全覆盖时直接返回节点自己维护的最大值
        pushdown(node);  // 保证儿子的值已经包含父亲的懒标记
        int v = 0;  // v 收集两个子区间查询结果的最大值
        if (l <= node->mid) {  // 左半边有交集
            v = max(v, query(l, r, node->left));  // 与左儿子的查询结果取最大
        }  // if 结束
        if (r > node->mid) {  // 右半边有交集
            v = max(v, query(l, r, node->right));  // 与右儿子的查询结果取最大
        }  // if 结束
        return v;  // 返回本区间内查询到的最大值
    }  // 递归 query 结束

    void pushup(Node* node) {  // 用两个儿子的最大值更新父亲
        node->v = max(node->left->v, node->right->v);  // 父亲的最大值取两个儿子最大值的较大者
    }  // pushup 结束

    void pushdown(Node* node) {  // 把本节点的懒标记下发给两个儿子
        if (!node->left) {  // 左儿子还不存在
            node->left = new Node(node->l, node->mid);  // 动态开点，建立覆盖 [l, mid] 的左儿子
        }  // if 结束
        if (!node->right) {  // 右儿子还不存在
            node->right = new Node(node->mid + 1, node->r);  // 动态开点，建立覆盖 [mid+1, r] 的右儿子
        }  // if 结束
        if (node->add) {  // 只有存在懒标记才需要下发
            Node* left = node->left;  // 先取出左儿子指针，避免重复解引用
            Node* right = node->right;  // 先取出右儿子指针
            left->v += node->add;  // 左儿子的最大值加上标记
            right->v += node->add;  // 右儿子的最大值加上标记
            left->add += node->add;  // 标记继续累积到左儿子，供更下层使用
            right->add += node->add;  // 标记继续累积到右儿子
            node->add = 0;  // 清空父亲的懒标记，避免重复下发
        }  // if 结束
    }  // pushdown 结束
};  // SegmentTree 类定义结束

class MyCalendarThree {  // 题目要求的日程安排表 III：每次预订后返回最大重叠次数
public:  // 对外接口
    SegmentTree* tree;  // 内部维护一棵动态开点线段树

    MyCalendarThree() {  // 构造函数：创建线段树
        tree = new SegmentTree();  // 根节点覆盖整条时间轴
    }  // 构造函数结束

    int book(int start, int end) {  // 预订半开区间 [start, end)，返回当前全局最大重叠次数
        tree->modify(start + 1, end, 1);  // 把区间整体加 1；+1 是为了和线段树 1-based 的时间轴对齐
        return tree->query(1, 1e9 + 1);  // 查询整条时间轴上的最大值，即当前最大重叠次数
    }  // book 方法结束
};  // MyCalendarThree 类定义结束

// 下面是 LeetCode 判题器自动生成的调用示例，原样保留，仅作说明
/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(start,end);
 */
