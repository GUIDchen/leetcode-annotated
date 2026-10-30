// 题目：850. 矩形面积 II（Rectangle Area II）
// 思路：扫描线 + y 坐标离散化 + 线段树维护当前被覆盖的 y 总长度，沿 x 方向累加「宽度 × 覆盖长度」得到并集面积。
// 时间复杂度：O(n log n)，排序与 n 次线段树区间更新；空间复杂度：O(n)，离散化坐标表与线段树节点。
class Node {  // 线段树节点：区间端点、覆盖次数、以及当前有效覆盖长度
public:  // 结构体成员默认公开，这里显式写出便于外部直接访问
    int l, r, cnt, length;  // l/r 为离散化下标区间，cnt 为被矩形覆盖次数，length 为该节点真实覆盖的 y 长度
};

class SegmentTree {  // y 方向线段树：支持区间加、并查询整体被覆盖的总长度
public:  // 对外提供构造、更新与查询接口
    vector<Node*> tr;  // 节点数组，按完全二叉树下标从 1 开始使用（根为 1）
    vector<int> nums;  // 离散化后的 y 坐标表，用来把下标还原成真实长度

    SegmentTree(vector<int>& nums) {  // 构造函数：传入离散化坐标并立即建树
        this->nums = nums;  // 保存坐标表，pushup 计算真实长度时要用
        int n = nums.size() - 1;  // s 个坐标点划分出 s-1 个小区间，故区间下标为 0..n-1
        tr.resize(n << 2);  // 线段树容量开 4n（n << 2），防止递归下标越界
        for (int i = 0; i < tr.size(); ++i) tr[i] = new Node();  // 为每个位置分配节点对象，避免后续访问空指针
        build(1, 0, n - 1);  // 从根节点 1 开始，构建覆盖 [0, n-1] 的线段树
    }

    void build(int u, int l, int r) {  // u 为节点编号，[l, r] 为该节点负责的离散化下标区间
        tr[u]->l = l;  // 记录左端点下标
        tr[u]->r = r;  // 记录右端点下标
        if (l != r) {  // 非叶子节点才需要继续分裂
            int mid = (l + r) >> 1;  // 取中点，>> 1 等价于整除 2
            build(u << 1, l, mid);  // 递归构建左子节点 u*2
            build(u << 1 | 1, mid + 1, r);  // 递归构建右子节点 u*2+1（u << 1 | 1）
        }
    }

    void modify(int u, int l, int r, int k) {  // 区间加：把 [l, r] 的覆盖次数整体加上 k（+1 进入矩形，-1 离开矩形）
        if (tr[u]->l >= l && tr[u]->r <= r)  // 当前节点区间被完全包含，可直接打标记
            tr[u]->cnt += k;  // 覆盖次数累加 k，不再向下递归，体现懒标记思想
        else {  // 区间未被完全包含，需要继续向下递归
            int mid = (tr[u]->l + tr[u]->r) >> 1;  // 当前节点区间的中点，用于判断往哪边递归
            if (l <= mid) modify(u << 1, l, r, k);  // 左半区间与操作区间相交才递归左子树
            if (r > mid) modify(u << 1 | 1, l, r, k);  // 右半区间与操作区间相交才递归右子树
        }
        pushup(u);  // 回溯时按子节点状态重新计算本节点的覆盖长度
    }

    int query() {  // 查询当前整棵 y 方向线段树被覆盖的总长度
        return tr[1]->length;  // 根节点的 length 就是所有矩形在 y 上的并集长度
    }

    void pushup(int u) {  // 由子节点信息更新节点 u 的 length
        if (tr[u]->cnt)  // 该区间被完整覆盖，整段 y 都有效
            tr[u]->length = nums[tr[u]->r + 1] - nums[tr[u]->l];  // 用离散化坐标还原真实长度：右端点对应 nums[r+1]
        else if (tr[u]->l == tr[u]->r)  // 叶子节点且未被覆盖，没有任何有效长度
            tr[u]->length = 0;  // 长度置 0
        else  // 非叶子且未被整体覆盖，需要由子节点拼接长度
            tr[u]->length = tr[u << 1]->length + tr[u << 1 | 1]->length;  // 左右子节点有效长度之和即本节点长度
    }
};

class Solution {
public:
    const int mod = 1e9 + 7;  // 题目要求答案对 1e9+7 取模

    int rectangleArea(vector<vector<int>>& rectangles) {  // rectangles 每个元素是 [x1, y1, x2, y2]，返回并集面积
        int n = rectangles.size();  // 矩形个数
        vector<vector<int>> segs(n << 1);  // 每个矩形拆成左右两条竖直扫描线，共 2n 条
        set<int> ts;  // 收集所有出现过的 y 坐标，用于离散化
        int i = 0;  // 扫描线写入下标
        for (auto& e : rectangles) {  // 遍历所有矩形，生成扫描线事件
            int x1 = e[0], y1 = e[1], x2 = e[2], y2 = e[3];  // 取出矩形的左下角与右上角坐标
            segs[i++] = {x1, y1, y2, 1};  // 左边事件：x1 处 y 区间 [y1, y2] 的覆盖数 +1
            segs[i++] = {x2, y1, y2, -1};  // 右边事件：x2 处 y 区间 [y1, y2] 的覆盖数 -1
            ts.insert(y1);  // 记录下边界坐标
            ts.insert(y2);  // 记录上边界坐标
        }
        sort(segs.begin(), segs.end());  // 按 x 升序排序，保证按扫描方向依次处理事件
        unordered_map<int, int> m;  // y 坐标 → 离散化下标 的映射
        i = 0;  // 下标计数器复位
        for (int v : ts) m[v] = i++;  // 升序遍历去重后的 y 坐标，依次编号
        vector<int> nums(ts.begin(), ts.end());  // 离散化数组，供线段树还原真实长度
        SegmentTree* tree = new SegmentTree(nums);  // 建立 y 方向的线段树
        long long ans = 0;  // 累加面积，用 long long 防止溢出
        for (int i = 0; i < segs.size(); ++i) {  // 依次处理每条扫描线事件
            auto e = segs[i];  // 当前扫描线事件
            int x = e[0], y1 = e[1], y2 = e[2], k = e[3];  // 取出当前事件的 x、y 区间与增量 k
            if (i > 0) ans += (long long) tree->query() * (x - segs[i - 1][0]);  // 用上一条扫描线到当前扫描线的宽度 × 当前覆盖长度累加面积
            tree->modify(1, m[y1], m[y2] - 1, k);  // 把当前事件的 y 区间并入或移出线段树；m[y2]-1 因为区间按左闭右开映射到离散下标
        }
        ans %= mod;  // 对 1e9+7 取模
        return (int) ans;  // 转回 int 类型返回
    }  // 方法结束
};  // 题解类结束