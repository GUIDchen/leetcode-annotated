// 题目：2940. 找到 Alice 和 Bob 可以相遇的建筑（Find Building Where Alice and Bob Can Meet）
// 思路：把询问按右端点 r 从大到小离线处理，用树状数组维护右侧建筑里「离散化高度 → 最左下标」的前缀最小值。
// 时间复杂度：O((n+m)log n)，排序与树状数组操作各 O(log n)；空间复杂度：O(n+m)，树状数组与下标数组。
class BinaryIndexedTree {  // 树状数组（维护前缀最小值）：记录每个高度桶里出现的最小下标
private:  // 以下为内部数据成员
    int inf = 1 << 30;  // 哨兵值：比任何合法下标都大，表示该位置还没有元素
    int n;  // 树状数组的容量，合法下标范围是 1..n
    vector<int> c;  // 树状数组本体，c[x] 保存该节点覆盖区间内的最小下标

public:  // 以下为对外接口
    BinaryIndexedTree(int n) {  // 按规模 n 构造树状数组
        this->n = n;  // 保存容量，供 update / query 使用
        c.resize(n + 1, inf);  // 下标从 1 开始，全部初始化为「无元素」
    }  // 构造函数结束

    void update(int x, int v) {  // 单点更新：在位置 x 放入值 v，节点上取较小值
        while (x <= n) {  // 沿 x += lowbit(x) 向上更新所有覆盖该位置的节点
            c[x] = min(c[x], v);  // 节点保存其覆盖区间内的最小值
            x += x & -x;  // lowbit 跳跃到父节点
        }  // 向上更新循环结束
    }  // update 结束

    int query(int x) {  // 查询前缀 [1, x] 上的最小值
        int mi = inf;  // 先用哨兵初始化，保证 min 从「无元素」开始
        while (x > 0) {  // 沿 x -= lowbit(x) 不断向前缀方向跳跃
            mi = min(mi, c[x]);  // 合并当前节点覆盖的区间
            x -= x & -x;  // 跳到左前方节点
        }  // 查询循环结束
        return mi == inf ? -1 : mi;  // 没查到就返回 -1（表示没有可行建筑），否则返回最左下标
    }  // query 结束
};  // 树状数组类结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {  // heights：每栋建筑的高度；queries：每条询问形如 [alice, bob] 两个下标
        int n = heights.size(), m = queries.size();  // n：建筑数量；m：询问数量
        for (auto& q : queries) {  // 遍历每个询问，把两个下标统一成「左端点 <= 右端点」
            if (q[0] > q[1]) {  // 出现顺序颠倒
                swap(q[0], q[1]);  // 交换两个下标，让 q[0] 是较靠左的那栋建筑
            }  // 归一化结束
        }  // 遍历询问结束
        vector<int> idx(m);  // idx：询问的下标数组，用于离线排序
        iota(idx.begin(), idx.end(), 0);  // 填入 0,1,...,m-1
        sort(idx.begin(), idx.end(), [&](int i, int j) {  // 按右端点 r 从大到小对询问下标排序，便于从右往左加入建筑
            return queries[j][1] < queries[i][1];  // 比较两个询问的右端点，实现降序
        });  // 排序结束
        vector<int> s = heights;  // 拷贝一份高度用于离散化
        sort(s.begin(), s.end());  // 升序排序
        s.erase(unique(s.begin(), s.end()), s.end());  // 去重，得到所有出现过的不同高度值
        vector<int> ans(m);  // ans：保存每个询问的答案
        int j = n - 1;  // j：从右往左的扫描指针，指向还没加入树状数组的建筑
        BinaryIndexedTree tree(n);  // 树状数组容量取 n，足以容纳离散化后的所有编号
        for (int i : idx) {  // 按右端点从大到小依次回答询问
            int l = queries[i][0], r = queries[i][1];  // l、r：当前询问的两个建筑下标，满足 l <= r
            while (j > r) {  // 把所有下标大于 r 的建筑加入树状数组，供当前询问查询
                int k = s.end() - lower_bound(s.begin(), s.end(), heights[j]) + 1;  // 高度离散化：比它大的不同高度越多编号越小；+1 让编号从 1 开始（树状数组下标从 1 起）
                tree.update(k, j);  // 把建筑 j 的下标记到对应高度桶里（同桶取最小下标）
                --j;  // 指针左移，保证每栋建筑只加入一次
            }  // 右侧建筑加入完毕
            if (l == r || heights[l] < heights[r]) {  // 两人同楼，或 Bob 所在楼已经更高，直接就是 r
                ans[i] = r;  // 答案为 r
            } else {  // 否则要在 r 右侧找严格高于 heights[l] 的建筑
                int k = s.end() - lower_bound(s.begin(), s.end(), heights[l]);  // 把 heights[l] 映射成查询上界；上面 +1 的偏移恰好把等高建筑排除在外
                ans[i] = tree.query(k);  // 前缀最小值就是最靠左的可行建筑下标（没有则返回 -1）
            }  // 分支结束
        }  // 所有询问处理完毕
        return ans;  // 返回每个询问的答案
    }  // 方法结束
};  // 类结束