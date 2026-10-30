// 3901. 好子序列查询 / Good Subsequence Queries
// 核心思路：线段树维护「p 的倍数」的区间 gcd。整体 gcd 不等于 p 时必无解；否则若存在非 p 的倍数（可直接剔除）或元素足够多则有解，全部为 p 的倍数时枚举删除哪个元素并检查剩余部分的 gcd。
// 复杂度：时间 O((n + q log n) + q·n log n)（仅 n <= 6 时枚举），空间 O(n)。
class Node {  // 线段树节点：管辖区间 [l, r] 及其中「p 的倍数」的 gcd
public:  // 公有成员
    int l, r;  // 区间的左右端点
    int g;  // 区间 gcd；非 p 的倍数在树中记为 0

    Node(int l, int r)  // 构造函数
        : l(l)  // 初始化左端点
        , r(r)  // 初始化右端点
        , g(0) {}  // gcd 的幺元取 0
};  // 节点定义结束

class SegmentTree {  // 维护区间 gcd 的线段树
public:  // 公有成员
    vector<Node*> tr;  // 节点池，下标从 1 开始，容量 4n

    SegmentTree(int n)  // 以 [1, n] 建树
        : tr(n << 2) {  // 节点池开 4n 个位置
        build(1, 1, n);  // 从根节点递归建树
    }  // 构造函数结束

    void build(int u, int l, int r) {  // 为节点 u 建立管辖区间 [l, r]
        tr[u] = new Node(l, r);  // 新建节点并挂到位置 u
        if (l == r) {  // 到达叶子节点
            return;  // 叶子直接返回
        }  // 叶子判断结束
        int mid = (l + r) >> 1;  // 区间中点
        build(u << 1, l, mid);  // 递归建立左子树
        build(u << 1 | 1, mid + 1, r);  // 递归建立右子树
    }  // build 结束

    void pushup(int u) {  // 用左右儿子的 gcd 更新当前节点
        tr[u]->g = gcd(tr[u << 1]->g, tr[u << 1 | 1]->g);  // 父区间 gcd 等于两子区间 gcd 的 gcd
    }  // pushup 结束

    void modify(int u, int x, int v) {  // 把位置 x 上的值改为 v
        if (tr[u]->l == tr[u]->r) {  // 找到叶子节点
            tr[u]->g = v;  // 直接覆盖为 v
            return;  // 回溯
        }  // 叶子判断结束
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 当前区间的中点
        if (x <= mid) {  // 位置落在左子树
            modify(u << 1, x, v);  // 递归修改左子树
        } else {  // 位置落在右子树
            modify(u << 1 | 1, x, v);  // 递归修改右子树
        }  // 分支结束
        pushup(u);  // 回溯时更新当前节点的 gcd
    }  // modify 结束

    int query(int u, int l, int r) {  // 查询区间 [l, r] 的 gcd
        if (l > r) {  // 空区间
            return 0;  // 空区间的 gcd 取幺元 0
        }  // 空区间判断结束
        if (tr[u]->l >= l && tr[u]->r <= r) {  // 当前节点区间被完全覆盖
            return tr[u]->g;  // 直接返回该节点的 gcd
        }  // 覆盖判断结束
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 当前区间的中点
        if (r <= mid) {  // 查询区间只在左子树
            return query(u << 1, l, r);  // 递归查询左子树
        }  // 左分支结束
        if (l > mid) {  // 查询区间只在右子树
            return query(u << 1 | 1, l, r);  // 递归查询右子树
        }  // 右分支结束
        return gcd(query(u << 1, l, mid), query(u << 1 | 1, mid + 1, r));  // 跨越中点，合并左右两段的 gcd
    }  // query 结束

    ~SegmentTree() {  // 析构函数：释放所有节点
        for (auto node : tr) {  // 遍历节点池
            delete node;  // 释放该节点
        }  // 遍历结束
    }  // 析构结束
};  // 线段树定义结束

class Solution {  // 题解类
public:  // 公有接口
    int countGoodSubseq(vector<int>& nums, int p, vector<vector<int>>& queries) {  // nums 为数组，p 为目标 gcd，queries 为单点修改；返回存在好子序列的查询个数
        int n = nums.size();  // 数组长度
        SegmentTree tree(n);  // 建立维护区间 gcd 的线段树
        int cnt = 0;  // 记录 p 的倍数在数组中的个数
        for (int i = 0; i < n; ++i) {  // 按初值建树
            if (nums[i] % p == 0) {  // 只有 p 的倍数才可能进入好子序列
                tree.modify(1, i + 1, nums[i]);  // 位置从 1 开始，写入该值
                ++cnt;  // 倍数计数加一
            }  // 倍数判断结束
        }  // 建树结束

        int ans = 0;  // 统计存在好子序列的查询个数
        for (auto& q : queries) {  // 依次处理每个查询
            int idx = q[0], val = q[1];  // 把下标 idx 处的元素改成 val
            if (nums[idx] % p == 0) {  // 旧值原本是 p 的倍数
                tree.modify(1, idx + 1, 0);  // 从线段树中清除旧值
                --cnt;  // 倍数计数减一
            }  // 旧值判断结束
            if (val % p == 0) {  // 新值是 p 的倍数
                tree.modify(1, idx + 1, val);  // 把新值写入线段树
                ++cnt;  // 倍数计数加一
            }  // 新值判断结束
            nums[idx] = val;  // 同步更新原数组

            if (tree.tr[1]->g != p) {  // 整体 gcd 不等于 p，任何子序列的 gcd 都不会等于 p
                continue;  // 本次查询无好子序列，直接跳过
            }  // 整体 gcd 判断结束
            if (cnt < n || n > 6) {  // 存在非 p 的倍数（可整体删去）或元素足够多时，好子序列必定存在
                ++ans;  // 本次查询计入答案
                continue;  // 处理下一个查询
            }  // 快速判断结束
            for (int i = 1; i <= n; ++i) {  // 全部都是 p 的倍数时，枚举被删掉的那个元素
                int leftG = tree.query(1, 1, i - 1);  // 删掉 i 后左半段的 gcd
                int rightG = tree.query(1, i + 1, n);  // 删掉 i 后右半段的 gcd
                if (gcd(leftG, rightG) == p) {  // 剩余元素的 gcd 仍等于 p
                    ++ans;  // 本次查询计入答案
                    break;  // 每个查询最多计一次，跳出枚举
                }  // 命中判断结束
            }  // 枚举结束
        }  // 查询处理结束
        return ans;  // 返回答案
    }  // countGoodSubseq 结束
};  // 类定义结束