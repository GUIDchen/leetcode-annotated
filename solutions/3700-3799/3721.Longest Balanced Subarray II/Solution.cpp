// 3721. Longest Balanced Subarray II（最长平衡子数组 II）
// 核心思路：把每个不同数值按奇偶性折算成 +1/-1，用支持区间加与区间最值的线段树维护“按不同数值计数”的前缀和，对每个右端点找出最早出现相同前缀和的位置，即得最长平衡子数组。
// 复杂度：时间 O(n log n)（每次区间加/查询 O(log n)），空间 O(n)（线段树 4n 个结点）。

/*
 * Segment tree node.
 * It maintains:
 *  - [l, r] : the covered index range
 *  - mn     : minimum prefix sum in this range
 *  - mx     : maximum prefix sum in this range
 *  - lazy   : lazy propagation value (range add)
 */
class Node {  // 线段树结点定义
public:
    int l = 0, r = 0;  // 结点管辖的区间左、右端点
    int mn = 0, mx = 0;  // 区间内前缀和的最小值与最大值，用于判断目标值是否落在本区间
    int lazy = 0;  // 区间加的懒标记
};  // 结点定义结束

/*
 * Segment Tree that supports:
 *  1. Range add
 *  2. Query the smallest index whose prefix sum equals a given value
 */
class SegmentTree {  // 线段树类：支持区间加与“找最小下标使前缀和等于目标值”
public:
    SegmentTree(int n) {  // 构造函数，下标范围是 [0, n]（共 n+1 个前缀位置）
        tr.resize(n << 2);  // 开 4 倍空间（n<<2 已足够覆盖 [0, n]）
        for (int i = 0; i < (int) tr.size(); ++i) {  // 逐个分配结点，避免指针数组未初始化
            tr[i] = new Node();  // 新建一个结点
        }  // 分配循环结束
        // Build the tree on range [0, n]
        build(1, 0, n);  // 在 [0, n] 上建树，初始前缀和全为 0
    }  // 构造函数结束

    /*
     * Add value v to all prefix sums in range [l, r]
     */
    void modify(int u, int l, int r, int v) {  // 把区间 [l, r] 内的所有前缀和都加上 v
        if (tr[u]->l >= l && tr[u]->r <= r) {  // 当前结点区间被完全覆盖（是目标区间的子区间）
            apply(u, v);  // 整段打上懒标记并更新最值
            return;  // 完全覆盖时无需继续递归，直接返回
        }  // 否则先把懒标记下传，保证子结点数据正确
        pushdown(u);  // 下传懒标记
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 取区间中点
        if (l <= mid) modify(u << 1, l, r, v);  // 左子区间 [l, mid] 与目标区间有交集时递归左侧
        if (r > mid) modify(u << 1 | 1, l, r, v);  // 右子区间 [mid+1, r] 与目标区间有交集时递归右侧
        pushup(u);  // 左右子结点更新后回溯合并最值
    }  // modify 结束

    /*
     * Binary search on the segment tree.
     * Find the smallest index pos such that prefix_sum[pos] == target.
     *
     * The key observation:
     * If target is within [mn, mx] of a segment, then such a position
     * must exist inside this segment.
     */
    int query(int u, int target) {  // 在线段树上二分，找最小下标 pos 使 prefix_sum[pos] == target
        if (tr[u]->l == tr[u]->r) {  // 递归到叶子结点，该下标即答案
            return tr[u]->l;  // 返回叶子对应的下标
        }  // 叶子分支结束
        pushdown(u);  // 向下递归前先下传懒标记
        int lc = u << 1, rc = u << 1 | 1;  // 左、右子结点编号（u<<1 与 u<<1|1）
        if (tr[lc]->mn <= target && target <= tr[lc]->mx) {  // 目标值落在左子区间的 [mn, mx] 内，说明左区间中一定存在该值
            return query(lc, target);  // 优先往左子树找，保证取到最小下标
        }  // 左子树判断分支结束
        return query(rc, target);  // 左子树不含目标值时只能去右子树
    }  // query 结束

private:  // 私有成员：线段树数组与内部工具函数
    vector<Node*> tr;  // 线段树结点指针数组

    /*
     * Build an empty segment tree.
     * Initial prefix sums are all zero.
     */
    void build(int u, int l, int r) {  // 递归建树：结点 u 管辖区间 [l, r]
        tr[u]->l = l;  // 记录结点管辖的左端点
        tr[u]->r = r;  // 记录结点管辖的右端点
        tr[u]->mn = tr[u]->mx = 0;  // 初始前缀和全为 0，最小值与最大值都置 0
        tr[u]->lazy = 0;  // 懒标记清零
        if (l == r) return;  // 到达叶子结点，停止递归
        int mid = (l + r) >> 1;  // 取区间中点
        build(u << 1, l, mid);  // 递归建左子树 [l, mid]
        build(u << 1 | 1, mid + 1, r);  // 递归建右子树 [mid+1, r]
    }  // build 结束

    /*
     * Apply a range add to node u.
     */
    void apply(int u, int v) {  // 对结点 u 整段加上 v，并同步懒标记
        tr[u]->mn += v;  // 区间最小值整体加 v
        tr[u]->mx += v;  // 区间最大值整体加 v
        tr[u]->lazy += v;  // 懒标记累加 v，等待下传给子结点
    }  // apply 结束

    /*
     * Push information from children to parent.
     */
    void pushup(int u) {  // 用左右子结点的最值更新父结点
        tr[u]->mn = min(tr[u << 1]->mn, tr[u << 1 | 1]->mn);  // 父结点最小值取两子结点最小值
        tr[u]->mx = max(tr[u << 1]->mx, tr[u << 1 | 1]->mx);  // 父结点最大值取两子结点最大值
    }  // pushup 结束

    /*
     * Push lazy tag down to children.
     */
    void pushdown(int u) {  // 把结点 u 的懒标记下传给左右子结点
        if (tr[u]->lazy != 0) {  // 只有存在待下传的懒标记时才需要处理
            apply(u << 1, tr[u]->lazy);  // 左子结点继承懒标记
            apply(u << 1 | 1, tr[u]->lazy);  // 右子结点继承懒标记
            tr[u]->lazy = 0;  // 父结点懒标记清零，避免重复下传
        }  // if 分支结束
    }  // pushdown 结束
};  // 线段树类定义结束

class Solution {  // 题解类
public:
    int longestBalanced(vector<int>& nums) {  // 求最长平衡子数组的长度
        int n = nums.size();  // 取数组长度 n
        SegmentTree st(n);  // 建一棵下标范围为 [0, n] 的线段树

        /*
         * last[x] = the most recent position where value x appeared
         */
        unordered_map<int, int> last;  // 记录每个数值最近一次出现的位置（1 基下标）

        int now = 0; // current prefix sum  // 当前前缀和（按不同数值计数后的结果）
        int ans = 0; // answer  // 最长平衡子数组长度

        /*
         * Enumerate the right endpoint of the subarray
         */
        for (int i = 1; i <= n; ++i) {  // 枚举子数组右端点（1 基下标，与线段树下标对齐）
            int x = nums[i - 1];  // 取当前右端点对应的数值

            /*
             * Contribution of x:
             *  +1 if x is odd
             *  -1 if x is even
             */
            int det = (x & 1) ? 1 : -1;  // 该数值的贡献：奇数 +1，偶数 -1

            /*
             * If x appeared before, remove its previous contribution
             */
            if (last.count(x)) {  // 该数值之前出现过，需要先撤销它在旧位置之后的贡献
                st.modify(1, last[x], n, -det);  // 区间 [last[x], n] 减去旧贡献，使旧位置之后不再统计该数值
                now -= det;  // 当前前缀和同步减去该贡献
            }  // 撤销分支结束

            /*
             * Add current contribution of x
             */
            last[x] = i;  // 更新该数值最近一次出现的位置
            st.modify(1, i, n, det);  // 从当前位置 i 开始加上新贡献
            now += det;  // 当前前缀和同步加上该贡献

            /*
             * Find the smallest position pos such that
             * prefix_sum[pos] == now
             */
            int pos = st.query(1, now);  // 找到前缀和等于 now 的最早下标 pos

            /*
             * Update the maximum balanced subarray length
             */
            ans = max(ans, i - pos);  // 用 i-pos 更新答案（子数组 nums[pos..i-1] 平衡）
        }  // 右端点枚举结束

        return ans;  // 返回最长平衡子数组长度
    }  // 函数结束
};  // 题解类结束
