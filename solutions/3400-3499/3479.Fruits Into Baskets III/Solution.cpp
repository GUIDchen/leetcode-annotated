// 3479. 水果成篮 III（Fruits Into Baskets III）
// 核心思路：用线段树维护篮子容量的区间最大值，对每个水果在线段树上二分查找最左侧容量足够的篮子，占用后把该位置改成 0，找不到则计入放不下的数量。
// 复杂度：时间 O(n log n)，空间 O(n)
class SegmentTree {  // 线段树：维护篮子容量的区间最大值
public:  // 公有成员
    vector<int> nums, tr;  // 原始数组与线段树节点（下标从 1 开始）

    SegmentTree(vector<int>& nums) {  // 构造函数，nums 为 1 起始下标的篮子容量
        this->nums = nums;  // 保存原始数组
        int n = nums.size();  // 篮子数量
        tr.resize(n * 4);  // 线段树节点数开到 4n
        build(1, 1, n);  // 建树，根节点覆盖区间 [1, n]
    }  // 结束构造函数

    void build(int u, int l, int r) {  // 建树：u 为节点编号，[l, r] 为其覆盖区间
        if (l == r) {  // 到达叶子节点
            tr[u] = nums[l - 1];  // 叶子直接取对应的篮子容量（原数组下标从 1 开始）
            return;  // 返回上一层
        }  // 结束叶子判断
        int mid = (l + r) >> 1;  // 取中点
        build(u * 2, l, mid);  // 递归建左子树
        build(u * 2 + 1, mid + 1, r);  // 递归建右子树
        pushup(u);  // 用左右儿子更新当前节点的最大值
    }  // 结束建树

    void modify(int u, int l, int r, int i, int v) {  // 单点修改：把位置 i 的容量改成 v
        if (l == r) {  // 到达叶子节点
            tr[u] = v;  // 直接赋新值（篮子被占用时 v = 0）
            return;  // 返回上一层
        }  // 结束叶子判断
        int mid = (l + r) >> 1;  // 取中点
        if (i <= mid) {  // 目标在左半区间
            modify(u * 2, l, mid, i, v);  // 递归修改左子树
        } else {  // 目标在右半区间
            modify(u * 2 + 1, mid + 1, r, i, v);  // 递归修改右子树
        }  // 结束分支
        pushup(u);  // 回溯时更新当前节点的最大值
    }  // 结束单点修改

    int query(int u, int l, int r, int v) {  // 查询容量大于等于 v 的最左侧篮子的下标，找不到返回 -1
        if (tr[u] < v) {  // 本区间最大值都不够，说明整段没有可用篮子
            return -1;  // 直接返回 -1
        }  // 结束剪枝判断
        if (l == r) {  // 到达叶子节点
            return l;  // 叶子下标即答案
        }  // 结束叶子判断
        int mid = (l + r) >> 1;  // 取中点
        if (tr[u * 2] >= v) {  // 优先往左子树找，保证取到最左侧的合法篮子
            return query(u * 2, l, mid, v);  // 左子树满足条件，递归左子树
        }  // 结束左子树判断
        return query(u * 2 + 1, mid + 1, r, v);  // 否则递归右子树
    }  // 结束查询

    void pushup(int u) {  // 用左右儿子的最大值更新父节点
        tr[u] = max(tr[u * 2], tr[u * 2 + 1]);  // 节点值等于两个儿子中的较大值
    }  // 结束 pushup
};  // 结束线段树类定义

class Solution {  // 解题类
public:  // 公有成员
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {  // 返回无法放入任何篮子的水果数量
        SegmentTree tree(baskets);  // 用篮子容量构建线段树
        int n = baskets.size();  // 篮子数量
        int ans = 0;  // 统计放不下的水果数
        for (int x : fruits) {  // 按顺序处理每个水果
            int i = tree.query(1, 1, n, x);  // 找到容量足够的最左侧篮子
            if (i < 0) {  // 找不到可用的篮子
                ans++;  // 该水果放不下，计数加一
            } else {  // 找到了可用篮子
                tree.modify(1, 1, n, i, 0);  // 占用它：把该位置的容量改成 0
            }  // 结束分支
        }  // 结束水果遍历
        return ans;  // 返回放不下的水果数
    }  // 结束方法
};  // 结束类定义
