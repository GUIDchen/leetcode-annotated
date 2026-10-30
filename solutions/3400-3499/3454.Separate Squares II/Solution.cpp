// 3454. 分割正方形 II / Separate Squares II
// 核心思路：扫描线求正方形并集面积，用线段树维护当前 x 方向被覆盖的总长度，再在第二遍扫描中定位面积刚好达到一半的高度。
// 复杂度：时间复杂度 O(n log n)，空间复杂度 O(n)。
struct Node {  // 线段树结点
    int l = 0, r = 0, cnt = 0;  // 区间左右端点下标与整段被覆盖的次数
    int length = 0;  // 该区间被覆盖的总长度
};

class SegmentTree {  // 维护“被覆盖总长度”的线段树
private:
    vector<Node> tr;  // 线段树结点数组
    vector<int> nums;  // 离散化后的坐标数组

    void build(int u, int l, int r) {  // 建树：结点 u 管理区间 [l, r]
        tr[u].l = l;  // 记录区间左端点下标
        tr[u].r = r;  // 记录区间右端点下标
        if (l != r) {  // 非叶结点继续递归建子树
            int mid = (l + r) >> 1;  // 区间中点
            build(u << 1, l, mid);  // 建左子树
            build(u << 1 | 1, mid + 1, r);  // 建右子树
        }  // 结束递归条件
    }  // 结束 build

    void pushup(int u) {  // 由子结点信息更新结点 u 的覆盖长度
        if (tr[u].cnt > 0) {  // 该区间被整体覆盖
            tr[u].length = nums[tr[u].r + 1] - nums[tr[u].l];  // 覆盖长度即为整段坐标跨度
        } else if (tr[u].l == tr[u].r) {  // 叶子结点且未被整体覆盖
            tr[u].length = 0;  // 没有覆盖，长度为 0
        } else {  // 内部结点且未被整体覆盖
            tr[u].length = tr[u << 1].length + tr[u << 1 | 1].length;  // 由左右子结点长度合并
        }  // 结束分支
    }  // 结束 pushup

public:
    SegmentTree(const vector<int>& nums)  // 构造函数：用离散坐标建树
        : nums(nums) {  // 保存坐标数组
        int n = (int) nums.size() - 1;  // 相邻坐标构成的小区间个数
        tr.assign(n << 2, Node());  // 按 4n 预分配结点
        build(1, 0, n - 1);  // 从根结点开始建树
    }  // 结束构造函数

    void modify(int u, int l, int r, int k) {  // 把区间 [l, r] 的覆盖次数增加 k（k 为 +1 或 -1）
        if (tr[u].l >= l && tr[u].r <= r) {  // 当前区间被修改区间完全包含
            tr[u].cnt += k;  // 直接累加覆盖标记
        } else {  // 只有部分相交，需要往子结点递归
            int mid = (tr[u].l + tr[u].r) >> 1;  // 区间中点
            if (l <= mid) modify(u << 1, l, r, k);  // 左子树有交集则递归左子树
            if (r > mid) modify(u << 1 | 1, l, r, k);  // 右子树有交集则递归右子树
        }  // 结束分支
        pushup(u);  // 回溯时更新当前结点的覆盖长度
    }  // 结束 modify

    int query() const {  // 查询整条扫描线被覆盖的总长度
        return tr[1].length;  // 根结点的长度即为答案
    }  // 结束 query
};  // 结束 SegmentTree

class Solution {  // 题解类
public:
    double separateSquares(vector<vector<int>>& squares) {  // 求使上下两部分面积相等的最小高度
        set<int> xs;  // 收集所有 x 坐标，用于离散化
        vector<array<int, 4>> segs;  // 扫描线事件：{y, x1, x2, 增量}

        for (auto& sq : squares) {  // 把每个正方形拆成底边与顶边两条事件
            int x1 = sq[0], y1 = sq[1], l = sq[2];  // 左下角坐标与边长
            int x2 = x1 + l, y2 = y1 + l;  // 右上角坐标
            xs.insert(x1);  // 记录左边界
            xs.insert(x2);  // 记录右边界
            segs.push_back({y1, x1, x2, 1});  // 底边事件：进入时覆盖次数 +1
            segs.push_back({y2, x1, x2, -1});  // 顶边事件：离开时覆盖次数 -1
        }  // 结束事件构造

        sort(segs.begin(), segs.end(), [](const auto& a, const auto& b) {  // 事件按高度排序
            return a[0] < b[0];  // 高度小的排在前面
        });  // 结束排序

        vector<int> st;  // 离散化后的 x 坐标数组
        st.reserve(xs.size());  // 预留空间避免扩容
        for (int x : xs) st.push_back(x);  // 按升序拷贝坐标

        SegmentTree tree(st);  // 用离散坐标建线段树

        unordered_map<int, int> d;  // x 坐标到离散下标的映射
        d.reserve(st.size() * 2);  // 预留空间减少哈希冲突
        for (int i = 0; i < (int) st.size(); i++) d[st[i]] = i;  // 逐项建立映射

        double area = 0.0;  // 第一遍扫描累计并集总面积
        int y0 = 0;  // 上一条扫描线的高度
        for (auto& s : segs) {  // 第一遍扫描：求正方形并集的总面积
            int y = s[0], x1 = s[1], x2 = s[2], k = s[3];  // 取出一个事件
            area += (double) (y - y0) * tree.query();  // 累加两条扫描线之间矩形条的面积
            tree.modify(1, d[x1], d[x2] - 1, k);  // 更新当前扫描线的覆盖情况
            y0 = y;  // 记录本次扫描线高度
        }  // 结束第一遍扫描

        double target = area / 2.0;  // 上下各一半，因此目标面积为总面积的一半
        area = 0.0;  // 复用 area 记录第二遍扫描的下方面积
        y0 = 0;  // 重置扫描线高度
        for (auto& s : segs) {  // 第二遍扫描：定位面积刚好达到一半的高度
            int y = s[0], x1 = s[1], x2 = s[2], k = s[3];  // 取出一个事件
            double t = (double) (y - y0) * tree.query();  // 当前矩形条的面积
            if (area + t >= target) {  // 目标面积落在这一条内
                return y0 + (target - area) / tree.query();  // 按比例线性插值出精确高度
            }  // 结束命中判断
            area += t;  // 累加已经扫过的面积
            tree.modify(1, d[x1], d[x2] - 1, k);  // 更新覆盖情况
            y0 = y;  // 记录本次扫描线高度
        }  // 结束第二遍扫描

        return 0.0;  // 理论上不会走到这里，保底返回
    }  // 结束 separateSquares
};  // 结束题解类
