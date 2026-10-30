// 题目：3165. 不包含相邻元素的子序列的最大和（Maximum Sum of Subsequence With Non-adjacent Elements）
// 思路：线段树每个节点维护四个状态（左端点选/不选 × 右端点选/不选）的最大和，按相邻元素不能同时选的规则合并；每次单点修改后 O(log n) 得到全区间最优。
// 时间复杂度：O(n + q log n)，建树 O(n)、每次询问 O(log n)；空间复杂度：O(n)，节点池开 4n。
class Node {  // 线段树节点：维护区间 [l, r] 以及「端点选或不选」的四种状态答案
public:  // 成员对外可见
    int l, r;  // 区间的左右端点（闭区间，树中位置从 1 开始编号）
    long long s00, s01, s10, s11;  // 四个状态值：第一位表示左端点是否被选、第二位表示右端点是否被选，0 不选 / 1 选

    Node(int l, int r)  // 构造函数：记录区间端点，并把四个状态都初始化为 0（空选）
        : l(l)  // 初始化左端点
        , r(r)  // 初始化右端点
        , s00(0)  // 左不选、右不选
        , s01(0)  // 左不选、右选
        , s10(0)  // 左选、右不选
        , s11(0) {}  // 左选、右选；叶子节点的取值稍后由 modify 写入
};  // 节点定义结束

class SegmentTree {  // 线段树：支持单点修改与区间查询
public:  // 成员对外可见
    vector<Node*> tr;  // 节点池：编号 u 的左右子节点分别是 2u 与 2u+1

    SegmentTree(int n)  // 构造 n 个位置的线段树
        : tr(n << 2) {  // n << 2 即 4n，线段树数组的经典安全容量
        build(1, 1, n);  // 从根节点（编号 1，负责区间 [1, n]）开始建树
    }  // 构造函数结束

    void build(int u, int l, int r) {  // 建树：让节点 u 负责区间 [l, r]
        tr[u] = new Node(l, r);  // 创建节点并挂到节点池上
        if (l == r) {  // 递归到叶子，说明区间只剩一个位置
            return;  // 无需再分裂，直接返回
        }  // if 结束
        int mid = (l + r) >> 1;  // 取中点，(l + r) / 2 的位运算写法
        build(u << 1, l, mid);  // 递归建左子树 [l, mid]
        build(u << 1 | 1, mid + 1, r);  // 递归建右子树 [mid + 1, r]
    }  // 建树函数结束

    long long query(int u, int l, int r) {  // 查询区间 [l, r] 的最优值；本题只查整个区间 [1, n]
        if (tr[u]->l >= l && tr[u]->r <= r) {  // 节点区间被查询区间完全覆盖，可以直接使用它的答案
            return tr[u]->s11;  // s11 是「两端都处理完」的最优值，正对应全区间答案
        }  // if 结束
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 当前节点的中点，用来判断查询区间落到哪一边
        long long ans = 0;  // 累加器；空子序列的和为 0
        if (r <= mid) {  // 查询区间完全落在左半边
            ans = query(u << 1, l, r);  // 递归左子树
        }  // if 结束
        if (l > mid) {  // 查询区间完全落在右半边
            ans = max(ans, query(u << 1 | 1, l, r));  // 与已有结果取较优（实际两个分支只会命中一个）
        }  // if 结束
        return ans;  // 返回区间最优值
    }  // 查询函数结束

    void pushup(int u) {  // 用左右子节点合并出父节点的四个状态
        Node* left = tr[u << 1];  // 左子节点
        Node* right = tr[u << 1 | 1];  // 右子节点
        tr[u]->s00 = max(left->s00 + right->s10, left->s01 + right->s00);  // 两端都不选：相邻处要么左子右端不选、要么右子左端不选，两种拼法取较优
        tr[u]->s01 = max(left->s00 + right->s11, left->s01 + right->s01);  // 左不选、右选：左子右端与右子左端不能同时被选
        tr[u]->s10 = max(left->s10 + right->s10, left->s11 + right->s00);  // 左选、右不选：同样要求相邻处不同时被选
        tr[u]->s11 = max(left->s10 + right->s11, left->s11 + right->s01);  // 两端都选：内部相邻处仍需满足不能同时被选
    }  // pushup 结束

    void modify(int u, int x, int v) {  // 单点修改：把位置 x 的值改成 v
        if (tr[u]->l == tr[u]->r) {  // 递归到叶子，即位置 x 本身
            tr[u]->s11 = max(0LL, (long long) v);  // 叶子只有「选它」和「不选它」两种选择，取较优；0LL 保证按长整型参与运算
            return;  // 修改完成，返回上层去重新合并
        }  // if 结束
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 判断 x 落在当前区间的哪半边
        if (x <= mid) {  // 落在左半边
            modify(u << 1, x, v);  // 递归修改左子树
        } else {  // 否则落在右半边
            modify(u << 1 | 1, x, v);  // 递归修改右子树
        }  // if/else 结束
        pushup(u);  // 子节点变了，自底向上重新合并
    }  // 修改函数结束

    ~SegmentTree() {  // 析构函数：释放 new 出来的节点，避免内存泄漏
        for (auto node : tr) {  // 遍历节点池
            delete node;  // 逐个释放；delete 空指针也是安全的
        }  // 循环结束
    }  // 析构函数结束
};  // 线段树类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {  // nums 为初始数组，queries 中每个元素是 [下标, 新值]，表示一次「改值后求全区间最大和」
        int n = nums.size();  // 数组长度，也是线段树区间的右端点
        SegmentTree tree(n);  // 建树，位置编号采用 1..n
        for (int i = 0; i < n; ++i) {  // 把初始数组灌进线段树
            tree.modify(1, i + 1, nums[i]);  // 数组下标 i 对应树中的位置 i + 1
        }  // for 结束
        long long ans = 0;  // 所有询问的答案之和
        const int mod = 1e9 + 7;  // 题目要求的取模常量
        for (const auto& q : queries) {  // 依次处理每个询问
            tree.modify(1, q[0] + 1, q[1]);  // 先把 nums[q[0]] 改成 q[1]（树中位置是 q[0] + 1）
            ans = (ans + tree.query(1, 1, n)) % mod;  // 再求当前全区间最大和，累加并取模
        }  // for 结束
        return (int) ans;  // 累加结果取模后转回 int 返回
    }  // 方法结束
};  // 类定义结束
