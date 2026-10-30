// 题目：1157. 子数组中占绝大多数的元素（Online Majority Element In Subarray）
// 思路：线段树维护区间的 Boyer-Moore 候选值与票数，再用「值 → 下标列表」二分确认出现次数。
// 时间复杂度：建树 O(n)，每次查询 O(log n)；空间复杂度：O(n)。
class Node {  // 线段树节点
public:  // 节点字段对外可见
    int l = 0, r = 0;  // 该节点负责的区间 [l, r]
    int x = 0, cnt = 0;  // x 是 Boyer-Moore 候选值，cnt 是抵消后剩余的票数
};  // 节点定义结束

using pii = pair<int, int>;  // 简写：{候选值, 票数}

class SegmentTree {  // 维护区间「候选值 + 票数」的线段树
public:  // 对外接口
    SegmentTree(vector<int>& nums) {  // 构造函数，nums 为原始数组
        this->nums = nums;  // 存下数组，供建树时取值
        int n = nums.size();  // 数组长度
        tr.resize(n << 2);  // 预分配 4n 个槽位，线段树足够用
        for (int i = 0; i < tr.size(); ++i) {  // 逐个分配节点对象
            tr[i] = new Node();  // 新建一个节点
        }  // 结束节点分配
        build(1, 1, n);  // 从根节点建树，区间用 1..n 表示
    }  // 构造函数结束

    pii query(int u, int l, int r) {  // 查询区间 [l, r] 的候选值与票数
        if (tr[u]->l >= l && tr[u]->r <= r) {  // 节点区间被查询区间完全覆盖
            return {tr[u]->x, tr[u]->cnt};  // 直接返回该节点保存的结果
        }  // 结束完全覆盖分支
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 当前节点区间的中点
        if (r <= mid) {  // 查询完全落在左子树
            return query(u << 1, l, r);  // 递归查询左子树
        }  // 结束左子树分支
        if (l > mid) {  // 查询完全落在右子树
            return query(u << 1 | 1, l, r);  // 递归查询右子树
        }  // 结束右子树分支
        auto left = query(u << 1, l, r);  // 查询左半部分的结果
        auto right = query(u << 1 | 1, l, r);  // 查询右半部分的结果
        if (left.first == right.first) {  // 两侧候选值相同
            left.second += right.second;  // 候选值不变，票数相加
        } else if (left.second >= right.second) {  // 左侧票数不少于右侧
            left.second -= right.second;  // 票数相减，候选值仍取左侧
        } else {  // 右侧票数更多
            right.second -= left.second;  // 右侧票数减去左侧票数
            left = right;  // 候选值换成右侧
        }  // 结束合并分支
        return left;  // 返回合并后的 {候选值, 票数}
    }  // query 方法结束

private:  // 内部实现
    vector<Node*> tr;  // 线段树节点数组（下标从 1 开始使用）
    vector<int> nums;  // 原始数组

    void build(int u, int l, int r) {  // 递归建树：节点 u 对应区间 [l, r]
        tr[u]->l = l;  // 记录区间左端点
        tr[u]->r = r;  // 记录区间右端点
        if (l == r) {  // 到达叶子节点
            tr[u]->x = nums[l - 1];  // 叶子值（数组下标 0 基，所以减 1）
            tr[u]->cnt = 1;  // 单个元素的票数为 1
            return;  // 叶子建完直接返回
        }  // 结束叶子分支
        int mid = (l + r) >> 1;  // 区间中点
        build(u << 1, l, mid);  // 递归建左子树
        build(u << 1 | 1, mid + 1, r);  // 递归建右子树
        pushup(u);  // 用两个孩子合并出当前节点
    }  // build 方法结束

    void pushup(int u) {  // 用左右孩子合并出节点 u
        if (tr[u << 1]->x == tr[u << 1 | 1]->x) {  // 两侧候选值相同
            tr[u]->x = tr[u << 1]->x;  // 候选值保持不变
            tr[u]->cnt = tr[u << 1]->cnt + tr[u << 1 | 1]->cnt;  // 票数相加
        } else if (tr[u << 1]->cnt >= tr[u << 1 | 1]->cnt) {  // 左侧票数不少于右侧
            tr[u]->x = tr[u << 1]->x;  // 候选值取左侧
            tr[u]->cnt = tr[u << 1]->cnt - tr[u << 1 | 1]->cnt;  // 票数相减
        } else {  // 右侧票数更多
            tr[u]->x = tr[u << 1 | 1]->x;  // 候选值取右侧
            tr[u]->cnt = tr[u << 1 | 1]->cnt - tr[u << 1]->cnt;  // 票数相减
        }  // 结束合并分支
    }  // pushup 方法结束
};  // 线段树类结束

class MajorityChecker {  // 题目要求的查询类
public:  // 对外接口
    MajorityChecker(vector<int>& arr) {  // 构造：建线段树并记录每个值的所有下标
        tree = new SegmentTree(arr);  // 建线段树，用于取区间候选值
        for (int i = 0; i < arr.size(); ++i) {  // 遍历数组
            d[arr[i]].push_back(i);  // 记录该值出现的下标（天然升序）
        }  // 结束下标记录
    }  // 构造函数结束

    int query(int left, int right, int threshold) {  // 查询 [left, right] 中出现次数不少于 threshold 的值
        int x = tree->query(1, left + 1, right + 1).first;  // 线段树取候选值（内部区间 1 基，故加 1）
        auto l = lower_bound(d[x].begin(), d[x].end(), left);  // 候选值在查询区间内的首个下标
        auto r = lower_bound(d[x].begin(), d[x].end(), right + 1);  // 查询区间右端之后的首个下标
        return r - l >= threshold ? x : -1;  // 出现次数达标返回候选值，否则返回 -1
    }  // query 方法结束

private:  // 内部数据
    unordered_map<int, vector<int>> d;  // 值 → 升序下标列表，用于二分数出现次数
    SegmentTree* tree;  // 线段树指针
};  // 类定义结束

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */