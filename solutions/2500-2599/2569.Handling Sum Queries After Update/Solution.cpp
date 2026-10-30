// 题目：2569. 更新数组后处理求和查询（Handling Sum Queries After Update）
// 思路：type 1 是 nums1 的区间 0/1 翻转，用带懒标记的线段树维护区间内 1 的个数；type 2 使 nums2 总和增加 p ×（nums1 中 1 的个数）；type 3 直接输出当前总和。
// 时间复杂度：O((n + q) log n)，每次翻转/查询都是区间操作；空间复杂度：O(n)，线段树开 4n 个节点。
class Node {  // 线段树节点
public:
    int l = 0, r = 0;  // 该节点负责的闭区间 [l, r]
    int s = 0, lazy = 0;  // s：区间内 1 的个数；lazy：待下传的翻转标记（1 表示整段还要再翻转一次）
};

class SegmentTree {  // 支持「区间 0/1 翻转」与「区间和查询」的懒标记线段树
public:
    SegmentTree(vector<int>& nums) {  // 构造函数：用初始数组建树
        this->nums = nums;  // 保存一份数组副本，build 时需要按下标取值
        int n = nums.size();  // 元素的个数
        tr.resize(n << 2);  // 线段树节点数开到 4n（n << 2 即 4n），保证不会越界
        for (int i = 0; i < tr.size(); ++i) {  // 逐个下标分配节点对象
            tr[i] = new Node();  // 默认构造的节点 l = r = s = lazy = 0
        }
        build(1, 1, n);  // 从 1 号节点开始递归建树，区间下标采用 1 ~ n 的写法
    }

    void modify(int u, int l, int r) {  // 把区间 [l, r] 里的每个数原地翻转（0 变 1、1 变 0）
        if (tr[u]->l >= l && tr[u]->r <= r) {  // 当前节点区间被目标区间完全覆盖
            tr[u]->lazy ^= 1;  // 打上翻转标记，等需要时再下传给子节点
            tr[u]->s = tr[u]->r - tr[u]->l + 1 - tr[u]->s;  // 整段翻转后 1 的个数变成「长度 - 原来的个数」
            return;  // 完全覆盖就不必再往下递归
        }
        pushdown(u);  // 没有完全覆盖，先把本节点积累的标记下传给子节点
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 当前区间的中点，用来判断左右子节点
        if (l <= mid) {  // 目标区间与左子区间有交集
            modify(u << 1, l, r);  // 递归处理左子节点（u << 1 即 2u）
        }
        if (r > mid) {  // 目标区间与右子区间有交集
            modify(u << 1 | 1, l, r);  // 递归处理右子节点（u << 1 | 1 即 2u+1）
        }
        pushup(u);  // 子节点更新完毕，用它们的和修正当前节点
    }

    int query(int u, int l, int r) {  // 查询区间 [l, r] 内 1 的个数
        if (tr[u]->l >= l && tr[u]->r <= r) {  // 当前节点区间被查询区间完全覆盖
            return tr[u]->s;  // 直接返回该节点维护的和
        }
        pushdown(u);  // 需要下钻子节点，先保证子节点的信息是最新的
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 当前区间的中点
        int res = 0;  // 累计答案
        if (l <= mid) {  // 左子区间有重叠部分
            res += query(u << 1, l, r);  // 累加左子区间的结果
        }
        if (r > mid) {  // 右子区间有重叠部分
            res += query(u << 1 | 1, l, r);  // 累加右子区间的结果
        }
        return res;  // 返回区间总和
    }

private:
    vector<Node*> tr;  // 线段树节点数组，下标从 1 开始使用
    vector<int> nums;  // 原始数组副本，build 建叶子时按 nums[l - 1] 取值

    void build(int u, int l, int r) {  // 以 u 为根，建立负责区间 [l, r] 的子树
        tr[u]->l = l;  // 记录区间左端点
        tr[u]->r = r;  // 记录区间右端点
        if (l == r) {  // 递归到叶子节点
            tr[u]->s = nums[l - 1];  // 叶子只代表一个元素，和就是该元素本身（树下标 1 对应数组下标 0）
            return;  // 叶子无需继续分裂
        }
        int mid = (l + r) >> 1;  // 区间中点
        build(u << 1, l, mid);  // 递归建立左子树 [l, mid]
        build(u << 1 | 1, mid + 1, r);  // 递归建立右子树 [mid+1, r]
        pushup(u);  // 左右子树建好后，用它们的和算出当前节点的和
    }

    void pushup(int u) {  // 由子节点信息更新父节点
        tr[u]->s = tr[u << 1]->s + tr[u << 1 | 1]->s;  // 父区间 1 的个数等于左右子区间之和
    }

    void pushdown(int u) {  // 把父节点的翻转标记下传给两个子节点
        if (tr[u]->lazy) {  // 只有存在待下传的翻转标记时才需要处理
            int mid = (tr[u]->l + tr[u]->r) >> 1;  // 中点，用来计算左右子区间的长度
            tr[u << 1]->s = mid - tr[u]->l + 1 - tr[u << 1]->s;  // 左子节点整段翻转：1 的个数变成 长度 - 原个数
            tr[u << 1]->lazy ^= 1;  // 左子节点累积一次翻转标记（两次翻转互相抵消，所以用异或）
            tr[u << 1 | 1]->s = tr[u]->r - mid - tr[u << 1 | 1]->s;  // 右子节点整段翻转：同样用「长度 - 原个数」
            tr[u << 1 | 1]->lazy ^= 1;  // 右子节点累积一次翻转标记
            tr[u]->lazy ^= 1;  // 标记已下传，清空当前节点的懒标记
        }
    }
};

class Solution {  // LeetCode 约定的题解类
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {  // nums1、nums2 是初始数组，queries 是三类操作
        SegmentTree* tree = new SegmentTree(nums1);  // 只对 nums1 建线段树，因为只有它会被区间翻转
        long long s = 0;  // 维护 nums2 当前的元素总和（可能超过 int，所以用 long long）
        for (int& x : nums2) {  // 用引用遍历，避免拷贝
            s += x;  // 累加得到 nums2 的初始总和
        }
        vector<long long> ans;  // 保存所有 type 3 查询的回答
        for (auto& q : queries) {  // 按顺序处理每条查询
            if (q[0] == 1) {  // type 1：翻转 nums1 的下标区间 [q[1], q[2]]
                tree->modify(1, q[1] + 1, q[2] + 1);  // 树中下标从 1 开始，所以左右端点都加 1
            } else if (q[0] == 2) {  // type 2：nums2 的每个元素都加上 p ×（nums1 中 1 的个数）
                s += 1LL * q[1] * tree->query(1, 1, nums1.size());  // 总和增加 p × 1 的个数；1LL 防止 int 相乘溢出
            } else {  // type 3：询问 nums2 的元素总和
                ans.push_back(s);  // 把当前总和记录下来
            }
        }
        return ans;  // 返回全部询问的答案
    }
};