// 题目：2276. 统计区间中的整数数目（Count Integers in Intervals）
// 思路：动态开点线段树维护 [1, 1e9] 的覆盖情况，add 做区间置 1，count 做全域求和，懒标记控制下传。
// 时间复杂度：add 与 count 均为 O(log C)，C = 1e9；空间复杂度：O(k log C)，k 为加入的区间个数。
class Node {  // 线段树节点：表示闭区间 [l, r]
public:  // 节点成员对外可见
    Node(int l, int r)  // 构造函数：区间端点由外部传入
        : l(l)  // 区间左端点
        , r(r)  // 区间右端点
        , mid((l + r) / 2)  // 区间中点，向下取整，用来划分左右子区间
        , v(0)  // 该区间内已被覆盖的整数个数，初始为 0
        , add(0)  // 懒标记：0 表示无标记，1 表示整段被覆盖
        , left(nullptr)  // 左子节点，初始为空，按需创建
        , right(nullptr) {}  // 右子节点，初始为空，按需创建

    int l, r, mid, v, add;  // 区间端点、中点、覆盖计数、懒标记
    Node* left;  // 指向左子节点
    Node* right;  // 指向右子节点
};

class SegmentTree {  // 动态开点线段树：支持区间置 1 与区间求和
public:  // 对外提供 modify 与 query
    SegmentTree()  // 构造函数：建立根节点
        : root(new Node(1, 1000000001)) {}  // 根覆盖 [1, 1e9+1]，右端点多留 1，便于 count 查询 [1, 1e9]

    void modify(int l, int r, int v, Node* node = nullptr) {  // 把区间 [l, r] 全部置为 v（本题只用 v = 1）
        if (node == nullptr) {  // 默认参数：未显式传入节点时从根开始
            node = root;  // 使用根节点作为递归起点
        }
        if (l > r) {  // 空区间无需处理
            return;  // 直接返回
        }
        if (node->l >= l && node->r <= r) {  // 当前节点区间被 [l, r] 完全覆盖
            node->v = node->r - node->l + 1;  // 整段整数都算被覆盖，计数直接等于区间长度
            node->add = v;  // 打上懒标记，暂不向子节点下传，保证复杂度
            return;  // 完全覆盖后无需继续递归
        }
        pushdown(node);  // 部分覆盖：先把懒标记下传，保证子节点数据正确
        if (l <= node->mid) {  // 与左子区间有交集
            modify(l, r, v, node->left);  // 递归处理左子树
        }
        if (r > node->mid) {  // 与右子区间有交集
            modify(l, r, v, node->right);  // 递归处理右子树
        }
        pushup(node);  // 用子节点结果回填当前节点的覆盖计数
    }

    int query(int l, int r, Node* node = nullptr) {  // 查询区间 [l, r] 内被覆盖的整数个数
        if (node == nullptr) {  // 默认参数：未显式传入节点时从根开始
            node = root;  // 使用根节点作为查询起点
        }
        if (l > r) {  // 空区间对答案贡献为 0
            return 0;  // 返回 0
        }
        if (node->l >= l && node->r <= r) {  // 查询区间完全覆盖当前节点
            return node->v;  // 直接返回该节点记录的覆盖计数
        }
        pushdown(node);  // 下传懒标记，之后子节点的值才是正确的
        int v = 0;  // 累计左右子树的查询结果
        if (l <= node->mid) {  // 左子区间与查询区间有交集
            v += query(l, r, node->left);  // 加上左子树的贡献
        }
        if (r > node->mid) {  // 右子区间与查询区间有交集
            v += query(l, r, node->right);  // 加上右子树的贡献
        }
        return v;  // 返回闭区间 [l, r] 的覆盖总数
    }

private:  // 以下为内部实现细节
    Node* root;  // 线段树根节点

    void pushup(Node* node) {  // 由两个子节点汇总当前节点
        node->v = node->left->v + node->right->v;  // 覆盖计数等于左右子树之和
    }

    void pushdown(Node* node) {  // 下传懒标记，并按需动态创建子节点
        if (node->left == nullptr) {  // 左子节点尚未创建
            node->left = new Node(node->l, node->mid);  // 动态开点：建立左子区间 [l, mid]
        }
        if (node->right == nullptr) {  // 右子节点尚未创建
            node->right = new Node(node->mid + 1, node->r);  // 动态开点：建立右子区间 [mid+1, r]
        }
        if (node->add != 0) {  // 有懒标记时才需要下传
            Node* left = node->left;  // 先取出左子节点，避免重复解引用
            Node* right = node->right;  // 先取出右子节点
            left->add = node->add;  // 左子节点继承覆盖标记
            right->add = node->add;  // 右子节点继承覆盖标记
            left->v = left->r - left->l + 1;  // 左子区间整段被覆盖
            right->v = right->r - right->l + 1;  // 右子区间整段被覆盖
            node->add = 0;  // 清除当前节点的标记，防止重复下传
        }
    }
};

class CountIntervals {  // 题目要求的计数类
public:
    CountIntervals() {}  // 构造函数：成员 tree 由默认构造自动初始化

    void add(int left, int right) {  // 把区间 [left, right] 加入集合
        tree.modify(left, right, 1);  // 线段树区间置 1，表示这些整数已被覆盖
    }

    int count() {  // 返回当前集合中不同整数的个数
        return tree.query(1, 1000000000);  // 查询全域 [1, 1e9] 的覆盖计数，即答案
    }

private:
    SegmentTree tree;  // 动态开点线段树实例
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */  // 判题器调用示例结束，以上注释无需修改