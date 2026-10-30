// 题目：715. Range 模块（Range Module）
// 核心思路：动态开点线段树。值域是 [1, 1e9]，每个节点维护「整段是否被完全跟踪」(v) 与懒标记 (add)，addRange/removeRange 做区间赋值，queryRange 做区间与查询；节点用 CachedObj 对象池批量分配降低开销。
// 时间复杂度：每次 addRange/removeRange/queryRange 均为 O(log C)，C = 1e9；空间复杂度：O(k·log C)，k 为操作次数，节点按需创建。
template <class T>  // 模板参数 T 是具体的节点类型，CachedObj 为它提供统一的分配器
class CachedObj {  // 侵入式对象池：重载 new/delete，成批申请节点以减少频繁 malloc 的开销
public:  // 分配器对外的接口
    void* operator new(size_t s) {  // 重载 new：优先从空闲链表 head 取节点，链表空则批量申请一批
        if (!head) {  // 空闲链表已空，需要一次性申请一批节点
            T* a = new T[SIZE];  // 一次申请 SIZE 个 T 的连续内存，把单次分配成本摊薄
            for (size_t i = 0; i < SIZE; ++i)  // 把新申请的这一批节点逐个挂到空闲链表上
                add(a + i);  // 用指针算术定位第 i 个节点并压入空闲链表
        }  // 结束批量申请
        T* p = head;  // 取链表头节点作为本次分配的结果
        head = head->CachedObj<T>::next;  // 头指针后移，把该节点从空闲链表上摘除
        return p;  // 返回这块可用的节点内存
    }  // 结束 operator new
    void operator delete(void* p, size_t) {  // 重载 delete：不真正归还内存，只把节点还回空闲链表复用
        if (p) add(static_cast<T*>(p));  // 空指针无需回收；否则把内存还原成 T* 后压回空闲链表
    }  // 结束 operator delete
    virtual ~CachedObj() {}  // 虚析构函数，保证通过基类指针销毁派生对象时行为正确

protected:  // 派生类可以访问的成员区
    T* next;  // 空闲链表指针，复用对象自身的内存来串起下一个空闲节点

private:  // 只在本类内部使用的成员区
    static T* head;  // 所有 T 类型节点共享的空闲链表头指针
    static const size_t SIZE;  // 每次批量申请的节点个数
    static void add(T* p) {  // 把节点 p 头插到空闲链表上
        p->CachedObj<T>::next = head;  // p 的 next 指向当前链表头
        head = p;  // 更新链表头为 p
    }  // 结束 add 方法
};  // 结束 CachedObj 类定义
template <class T>  // 静态成员 head 的类外定义（模板代码必须写在头文件里）
T* CachedObj<T>::head = 0;  // 初始为空链表
template <class T>  // 静态成员 SIZE 的类外定义
const size_t CachedObj<T>::SIZE = 10000;  // 每批一次申请 10000 个节点
class Node : public CachedObj<Node> {  // 线段树节点，继承对象池以便复用节点内存
public:  // 节点字段对外开放，方便线段树直接读写
    Node* left;  // 左子节点指针
    Node* right;  // 右子节点指针
    int add;  // 懒标记：1 表示整段被跟踪，-1 表示整段被清除，0 表示无标记
    bool v;  // 该区间是否被完全跟踪（线段树维护的答案）
};  // 结束 Node 定义

class SegmentTree {  // 动态开点的线段树，值域固定为 [1, 1e9]
private:  // 内部实现细节区
    Node* root;  // 整棵线段树的根，对应整个值域

public:  // 对外接口区
    SegmentTree() {  // 构造函数：创建根节点
        root = new Node();  // 根节点同样通过对象池分配
    }  // 结束构造函数

    void modify(int left, int right, int v) {  // 对外重载的区间赋值：把 [left, right] 设成 v
        modify(left, right, v, 1, 1e9, root);  // 调用内部递归版本，值域从 1 到 1e9，从根节点开始
    }  // 结束对外 modify

    void modify(int left, int right, int v, int l, int r, Node* node) {  // 内部实现：在区间 [l, r] 上处理目标区间 [left, right]
        if (l >= left && r <= right) {  // 当前区间被目标区间完全包含，可以整段打标记
            node->v = v == 1;  // v 为 1 表示覆盖为真，否则覆盖为假
            node->add = v;  // 把懒标记记在节点上，等子节点被访问时再下推
            return;  // 整段已处理完，无需继续递归
        }  // 结束完全包含判断
        pushdown(node);  // 要继续进入子区间，先把本层的懒标记下推给子节点
        int mid = (l + r) >> 1;  // 取区间中点，把 [l, r] 划分成左右两半
        if (left <= mid) modify(left, right, v, l, mid, node->left);  // 目标区间与左子区间有交集，递归修改左子树
        if (right > mid) modify(left, right, v, mid + 1, r, node->right);  // 目标区间与右子区间有交集，递归修改右子树
        pushup(node);  // 子节点更新完后，用它们的结果重新计算当前节点的 v
    }  // 结束内部 modify

    bool query(int left, int right) {  // 对外重载的区间查询：判断 [left, right] 是否被完全跟踪
        return query(left, right, 1, 1e9, root);  // 调用内部递归版本，从根节点开始查询
    }  // 结束对外 query

    bool query(int left, int right, int l, int r, Node* node) {  // 内部实现：查询 [left, right] 与当前区间 [l, r] 的交集是否全部被跟踪
        if (l >= left && r <= right) return node->v;  // 当前区间被完全包含，直接返回它维护的覆盖标记
        pushdown(node);  // 需要查看子区间，先把懒标记下推
        int mid = (l + r) >> 1;  // 取区间中点划分左右两半
        bool v = true;  // 以「全部覆盖」作为初值，便于用逻辑与累积结果
        if (left <= mid) v = v && query(left, right, l, mid, node->left);  // 与左子树的查询结果求逻辑与
        if (right > mid) v = v && query(left, right, mid + 1, r, node->right);  // 与右子树的查询结果求逻辑与
        return v;  // 只要有一个子区间未被覆盖，整体就不算完全覆盖
    }  // 结束内部 query

    void pushup(Node* node) {  // 由左右子节点的覆盖情况反推父节点的覆盖状态
        node->v = node->left && node->left->v && node->right && node->right->v;  // 左右子节点都存在且都被完全跟踪时，父节点才算完全跟踪
    }  // 结束 pushup 方法

    void pushdown(Node* node) {  // 把父节点的懒标记下推给子节点（动态开点：需要时才创建子节点）
        if (!node->left) node->left = new Node();  // 左子节点不存在就先创建
        if (!node->right) node->right = new Node();  // 右子节点不存在就先创建
        if (node->add) {  // 只有存在有效懒标记时才需要下推
            node->left->add = node->right->add = node->add;  // 把标记原样复制给左右两个子节点
            node->left->v = node->right->v = node->add == 1;  // 子节点的覆盖状态与标记保持一致
            node->add = 0;  // 清空父节点的标记，避免以后重复下推
        }  // 结束懒标记下推
    }  // 结束 pushdown 方法
};  // 结束 SegmentTree 类定义

class RangeModule {  // 题目要求的 RangeModule 类，内部用线段树维护被跟踪的整数区间
public:  // 对外接口区
    SegmentTree* tree;  // 底层线段树，覆盖 [1, 1e9] 的整数点

    RangeModule() {  // 构造函数：创建底层线段树
        tree = new SegmentTree();  // 分配线段树对象
    }  // 结束构造函数

    void addRange(int left, int right) {  // 把左闭右开区间 [left, right) 标记为被跟踪
        tree->modify(left, right - 1, 1);  // 题目右端点是开区间，转成闭区间 [left, right-1] 后整段置为覆盖
    }  // 结束 addRange 方法

    bool queryRange(int left, int right) {  // 查询左闭右开区间 [left, right) 是否被完整跟踪
        return tree->query(left, right - 1);  // 同样转成闭区间 [left, right-1] 后整段查询
    }  // 结束 queryRange 方法

    void removeRange(int left, int right) {  // 把左闭右开区间 [left, right) 取消跟踪
        tree->modify(left, right - 1, -1);  // 转成闭区间 [left, right-1] 后整段置为未覆盖
    }  // 结束 removeRange 方法
};  // 结束 RangeModule 类定义

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */