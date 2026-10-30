// 题目：2916. 子数组不同元素数目的平方和 II（Subarrays Distinct Element Sum of Squares II）
// 思路：对每个右端点 i，线段树下标 j 存 nums[j..i] 的不同元素个数；新元素只让上次出现位置之后的左端点 +1，用懒标记维护区间和与区间平方和。
// 时间复杂度：O(n log n)，每次区间加一次；空间复杂度：O(n)，线段树四倍空间。
class Node {  // 线段树节点：区间左右端点、区间和、区间平方和、加法懒标记
public:  // 节点对外可见
    int l = 0, r = 0;  // 节点管辖的区间 [l, r]
    long long sum = 0, sumSq = 0;  // sum 是区间内所有值之和，sumSq 是区间内所有值的平方和
    int lazy = 0;  // lazy 表示还没下推给孩子的加法增量（这里只会是 +1）
};

class SegmentTree {  // 线段树：维护数组的区间和与区间平方和，支持区间加
public:  // 构造与接口对外可见
    SegmentTree(int n) {  // 用元素个数 n 建树
        tr.resize(n << 2);  // 开到四倍空间，足够装下整棵线段树
        build(1, 0, n - 1);  // 从根节点 1 开始递归建树，管辖下标 [0, n-1]
    }

    void modify(int u, int l, int r, int v) {  // 把区间 [l, r] 内的值全部加 v
        if (tr[u].l >= l && tr[u].r <= r) {  // 当前节点区间被 [l, r] 完全覆盖，可以直接打标记
            apply(u, v);  // 把增量 v 作用到该节点上
            return;  // 不用再往下递归，直接返回
        }
        pushdown(u);  // 区间没有被完全覆盖，先把父节点挂着的懒标记下推给孩子
        int mid = (tr[u].l + tr[u].r) >> 1;  // 当前区间中点，用来判断该往哪边递归
        if (l <= mid) {  // 左孩子区间与 [l, r] 有交集时才需要递归
            modify(u << 1, l, r, v);  // 递归处理左孩子
        }
        if (r > mid) {  // 右孩子区间与 [l, r] 有交集时才需要递归
            modify(u << 1 | 1, l, r, v);  // 递归处理右孩子
        }
        pushup(u);  // 两个孩子都更新完后，用它们的信息重算当前节点
    }

    long long sumSq() const {  // 返回整棵树的区间平方和（根节点 1 的 sumSq）
        return tr[1].sumSq;  // 根节点管理所有下标，它的平方和就是要累加的量
    }

private:  // 以下是内部实现，不对外暴露
    vector<Node> tr;  // 树节点数组：1 为根，孩子为 u<<1 与 u<<1|1

    void build(int u, int l, int r) {  // 建树：让节点 u 管辖区间 [l, r]
        tr[u].l = l;  // 记录该节点的左端点
        tr[u].r = r;  // 记录该节点的右端点
        if (l == r) {  // 左右端点相同说明到了叶子
            return;  // 叶子没有孩子，直接返回
        }
        int mid = (l + r) >> 1;  // 中点，把区间对半分给两个孩子
        build(u << 1, l, mid);  // 递归建左孩子，区间 [l, mid]
        build(u << 1 | 1, mid + 1, r);  // 递归建右孩子，区间 [mid+1, r]
    }

    void apply(int u, int v) {  // 把加法增量 v 作用到节点 u：同步更新 sum、sumSq、lazy
        long long len = tr[u].r - tr[u].l + 1LL;  // 区间长度，用来把单点增量摊到整个区间
        long long add = v;  // 要加的增量，写成 long long 防止乘法溢出
        tr[u].sumSq += 2 * add * tr[u].sum + add * add * len;  // 平方和变化和公式：Σ(x+v)^2 = 原平方和 + 2v*原和 + v^2*长度
        tr[u].sum += add * len;  // 区间和变化：每个元素都加 v，总和增加 v*长度
        tr[u].lazy += v;  // 懒标记累加，表示孩子还欠 v 没加
    }

    void pushdown(int u) {  // 把节点 u 的懒标记下推给两个孩子
        if (tr[u].lazy) {  // 只有存在未下推的标记时才需要处理
            apply(u << 1, tr[u].lazy);  // 把同样的增量传给左孩子
            apply(u << 1 | 1, tr[u].lazy);  // 把同样的增量传给右孩子
            tr[u].lazy = 0;  // 标记已经下推完，清空当前节点的懒标记
        }
    }

    void pushup(int u) {  // 用两个孩子的结果重算节点 u
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;  // 区间和 = 左孩子和 + 右孩子和
        tr[u].sumSq = tr[u << 1].sumSq + tr[u << 1 | 1].sumSq;  // 区间平方和 = 左孩子平方和 + 右孩子平方和
    }
};

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int sumCounts(vector<int>& nums) {  // nums 是输入数组；返回所有子数组『不同元素个数的平方』之和（模 1e9+7）
        int n = nums.size();  // 数组长度
        SegmentTree st(n);  // 对下标 0..n-1 建一棵线段树
        unordered_map<int, int> last;  // last 记录每个数值上一次出现的位置
        long long ans = 0;  // 答案用 long long 累加，最后再转成 int
        for (int i = 0; i < n; ++i) {  // 枚举子数组的右端点 i
            int p = last.count(nums[i]) ? last[nums[i]] : -1;  // 当前值上一次出现的位置，没出现过就记为 -1
            st.modify(1, p + 1, i, 1);  // 把上次位置之后到 i 的区间整体加 1：这些左端点对应的子数组不同元素个数都 +1
            last[nums[i]] = i;  // 更新当前值最近一次出现的位置
            ans = (ans + st.sumSq()) % 1000000007;  // 根节点平方和就是以 i 结尾的所有子数组的不同元素个数平方和，累加到答案
        }
        return (int) ans;  // 把 long long 结果转成 int 返回
    }
};
