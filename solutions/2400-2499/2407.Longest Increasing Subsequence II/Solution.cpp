// 题目：2407. 最长递增子序列 II（Longest Increasing Subsequence II）
// 思路：值域线段树维护「以值 x 结尾的最长合法子序列长度」，处理 v 时查询区间 [v-k, v-1] 的最大值再加一，然后把结果单点写回 v。
// 时间复杂度：O(n log M)，n 为元素个数，M 为元素最大值；空间复杂度：O(M)，线段树需要约 4M 个节点。
class Node {  // 线段树节点：保存管辖的区间端点与该区间内的最大值
public:  // 成员对外公开，便于直接读写
    int l;  // 区间左端点
    int r;  // 区间右端点
    int v;  // 该区间内的最大值，即区间内最长合法子序列长度
};  // Node 定义结束

class SegmentTree {  // 值域线段树：下标代表元素值，节点维护对应值域内的最大长度
public:  // 成员对外公开
    vector<Node*> tr;  // 节点数组，用指针存放以便动态分配

    SegmentTree(int n) {  // 构造函数：n 表示值域上界，通常取数组最大值
        tr.resize(4 * n);  // 线段树节点数上界为 4n，先一次性开好
        for (int i = 0; i < tr.size(); ++i) tr[i] = new Node();  // 逐个分配节点，避免后面访问到空指针
        build(1, 1, n);  // 从 1 号节点开始建树，覆盖值域 [1, n]
    }  // 构造函数结束

    void build(int u, int l, int r) {  // 以 u 为根，建立覆盖区间 [l, r] 的子树
        tr[u]->l = l;  // 记录该节点管辖范围的左端
        tr[u]->r = r;  // 记录该节点管辖范围的右端
        if (l == r) return;  // 到达叶子节点，无需再分裂，直接返回
        int mid = (l + r) >> 1;  // 取中点把区间二分
        build(u << 1, l, mid);  // 递归建立左子树，覆盖 [l, mid]
        build(u << 1 | 1, mid + 1, r);  // 递归建立右子树，覆盖 [mid+1, r]
    }  // build 结束

    void modify(int u, int x, int v) {  // 单点更新：把下标 x 处的值改成 v
        if (tr[u]->l == x && tr[u]->r == x) {  // 定位到只包含 x 的叶子节点
            tr[u]->v = v;  // 叶子节点直接覆盖为新的长度
            return;  // 更新完成，回溯返回
        }  // 叶子判断分支结束
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 用当前区间中点决定往哪棵子树递归
        if (x <= mid)  // x 落在左半区间
            modify(u << 1, x, v);  // 递归更新左子树
        else  // 否则 x 落在右半区间
            modify(u << 1 | 1, x, v);  // 递归更新右子树
        pushup(u);  // 孩子更新后，用较大的孩子值刷新当前节点
    }  // modify 结束

    void pushup(int u) {  // 由左右孩子维护的最大值推出父亲的最大值
        tr[u]->v = max(tr[u << 1]->v, tr[u << 1 | 1]->v);  // 区间最大值等于两个孩子的较大者
    }  // pushup 结束

    int query(int u, int l, int r) {  // 查询区间 [l, r] 内的最大值
        if (tr[u]->l >= l && tr[u]->r <= r) return tr[u]->v;  // 当前节点被查询区间完全覆盖，直接返回其值
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 否则按中点拆分查询区间
        int v = 0;  // 累加答案，长度非负，初值取 0
        if (l <= mid) v = query(u << 1, l, r);  // 左半部分与查询区间有交集时递归左子树
        if (r > mid) v = max(v, query(u << 1 | 1, l, r));  // 右半部分有交集时与已有答案取较大值
        return v;  // 返回该区间的最大值
    }  // query 结束
};  // SegmentTree 定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int lengthOfLIS(vector<int>& nums, int k) {  // nums：输入数组；k：子序列中相邻元素差的上限
        SegmentTree* tree = new SegmentTree(*max_element(nums.begin(), nums.end()));  // 值域上界取数组最大值后建树，下标即元素值本身
        int ans = 1;  // 只要数组非空，答案至少为 1
        for (int v : nums) {  // 从左到右依次处理每个元素
            int t = tree->query(1, v - k, v - 1) + 1;  // 只在 [v-k, v-1] 这个前驱区间里转移，长度加一
            ans = max(ans, t);  // 用当前长度更新全局答案
            tree->modify(1, v, t);  // 把「以 v 结尾的最长长度」写回线段树，供后面的元素使用
        }  // 遍历结束
        return ans;  // 返回最长递增子序列的长度
    }  // 方法结束
};  // Solution 定义结束