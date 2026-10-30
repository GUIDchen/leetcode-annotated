// 题目：3525. 求出数组的 X 值 II（Find X Value of Array II）
// 思路：线段树维护每段的「整段乘积 mod k」与「各前缀积余数的个数」。合并时左段前缀原样保留，右段前缀整体乘上左段乘积；答案即后缀 [start, n-1] 前缀分布中 x 的计数。
// 时间复杂度：O((n + q·log n)·k)，建树 O(n·k)、每次查询/修改 O(k·log n)；空间复杂度：O(n·k)。
class Node {  // 线段树节点：区间边界 + 整段乘积 + 前缀余数分布
public:  // 节点字段全部公开，方便线段树直接访问
    int l = 0, r = 0;  // 该节点负责的闭区间 [l, r]（1-based）
    int prod = 1;  // 整段所有元素的乘积模 k 后的余数
    int cnt[5]{};  // cnt[r] 表示前缀积模 k 余 r 的前缀个数（题目保证 k ≤ 5）
};  // 节点定义结束

class SegmentTree {  // 支持单点修改 + 区间查询的线段树
public:  // 构造、修改、查询对外可见
    SegmentTree(vector<int>& nums, int k) {  // 用原数组与模数 k 建树
        this->k = k;  // 保存模数，供 merge/modify/build 使用
        int n = nums.size();  // 数组长度，线段树下标为 1..n
        tr.resize(n << 2);  // 4n 个节点足够覆盖整棵树
        build(1, 1, n, nums);  // 从根节点递归建树
    }  // 构造函数结束

    void modify(int u, int x, int v) {  // 把下标 x 处的元素改成 v，从节点 u 往下找
        if (tr[u].l == tr[u].r) {  // 走到叶子，区间里只剩被修改的那一个位置
            v %= k;  // 只需保留余数，后续运算都在模 k 下进行
            tr[u].prod = v;  // 单元素区间的乘积就是它自己
            memset(tr[u].cnt, 0, sizeof(tr[u].cnt));  // 先清空旧的前缀余数分布
            tr[u].cnt[v] = 1;  // 该元素本身是唯一的前缀，余数为 v
            return;  // 叶子处理完直接返回
        }  // if 结束
        int mid = (tr[u].l + tr[u].r) >> 1;  // 取区间中点，决定往左还是往右递归
        if (x <= mid) {  // 目标位置在左子树
            modify(u << 1, x, v);  // 递归修改左儿子
        } else {  // 目标位置在右子树
            modify(u << 1 | 1, x, v);  // 递归修改右儿子
        }  // 分支结束
        pushup(u);  // 儿子都更新完了，重新合并出父节点的信息
    }  // modify 结束

    Node query(int u, int l, int r) {  // 查询闭区间 [l, r] 合并后的节点信息
        if (tr[u].l >= l && tr[u].r <= r) {  // 当前节点被查询区间完全覆盖
            return tr[u];  // 整段信息可以直接返回
        }  // if 结束
        int mid = (tr[u].l + tr[u].r) >> 1;  // 取中点，判断查询区间落在哪一侧
        if (r <= mid) {  // 查询区间只落在左子树
            return query(u << 1, l, r);  // 全部交给左儿子
        }  // if 结束
        if (l > mid) {  // 查询区间只落在右子树
            return query(u << 1 | 1, l, r);  // 全部交给右儿子
        }  // if 结束
        return merge(query(u << 1, l, r), query(u << 1 | 1, l, r));  // 区间跨过中点：左右两段按顺序拼接成一个整体
    }  // query 结束

private:  // 以下为内部实现细节
    int k;  // 模数 k
    vector<Node> tr;  // 线段树的节点数组

    Node merge(const Node& a, const Node& b) {  // 把左段 a 与右段 b 合并成一个等价节点
        Node c;  // 存放合并结果
        c.prod = a.prod * b.prod % k;  // 整段乘积 = 左段乘积 × 右段乘积（取模）
        memcpy(c.cnt, a.cnt, sizeof(c.cnt));  // a 自身的前缀仍然是合并区间的前缀，先拷贝过来
        for (int r = 0; r < k; ++r) {  // 枚举右段每种前缀积余数
            c.cnt[a.prod * r % k] += b.cnt[r];  // 「整个 a + b 的前缀」也是合并区间的前缀，余数整体乘上 a.prod
        }  // 循环结束
        return c;  // 返回合并后的节点
    }  // merge 结束

    void pushup(int u) {  // 用左右儿子的信息刷新节点 u
        Node p = merge(tr[u << 1], tr[u << 1 | 1]);  // 先合并左右两个儿子
        tr[u].prod = p.prod;  // 更新父节点的整段乘积
        memcpy(tr[u].cnt, p.cnt, sizeof(tr[u].cnt));  // 更新父节点的前缀余数分布
    }  // pushup 结束

    void build(int u, int l, int r, vector<int>& nums) {  // 以 u 为根，递归建出区间 [l, r]
        tr[u].l = l;  // 记录区间左端点
        tr[u].r = r;  // 记录区间右端点
        if (l == r) {  // 走到叶子，区间只含一个元素
            int v = nums[l - 1] % k;  // 取出该元素并取模（数组下标为 0-based，故减一）
            tr[u].prod = v;  // 单元素区间的乘积就是它本身
            tr[u].cnt[v] = 1;  // 只有一个前缀，余数为 v
            return;  // 叶子建完直接返回
        }  // if 结束
        int mid = (l + r) >> 1;  // 取中点划分左右子区间
        build(u << 1, l, mid, nums);  // 递归建立左子树
        build(u << 1 | 1, mid + 1, r, nums);  // 递归建立右子树
        pushup(u);  // 由两个儿子合并出当前节点
    }  // build 结束
};  // SegmentTree 定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 判题器只调用 public 区的方法
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {  // 按 queries 依次修改并查询，返回每次查询的答案
        int n = nums.size();  // 数组长度
        SegmentTree tree(nums, k);  // 用初始 nums 建线段树
        vector<int> ans;  // 保存每个查询的答案
        ans.reserve(queries.size());  // 预留空间，避免反复扩容
        for (auto& q : queries) {  // 依次处理每个查询 [下标, 新值, 起点, 目标余数]
            tree.modify(1, q[0] + 1, q[1]);  // 先把 nums[q[0]] 改成 q[1]（下标转成 1-based）
            ans.push_back(tree.query(1, q[2] + 1, n).cnt[q[3]]);  // 查询后缀 [q[2], n-1] 中前缀积余数为 q[3] 的个数
        }  // 查询循环结束
        return ans;  // 返回所有查询的答案
    }  // 方法结束
};  // 类定义结束
