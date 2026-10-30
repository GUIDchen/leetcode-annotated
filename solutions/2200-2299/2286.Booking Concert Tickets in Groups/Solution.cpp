// 题目：2286. 以组为单位订音乐会的门票（Booking Concert Tickets in Groups）
// 核心思路：把每一行座位看成叶子结点，线段树维护「区间剩余座位和」与「区间单行剩余座位最大值」；gather 查最左一行满足最大值 >= k，scatter 靠前缀和判断可行性后从第一行有空的行走起贪心填满。
// 时间复杂度：单次 gather/scatter 均摊 O(log n + 被填满的行数)，整体 O((n + q) log n)；空间复杂度：O(n)，线段树开 4n 个结点。
class Node {  // 线段树结点：维护一段连续行区间的统计信息
public:  // 成员对外可见
    int l, r;  // l, r：该结点负责的行区间左右端点（1 基）
    long s, mx;  // s：区间剩余座位总数；mx：区间内单行剩余座位的最大值
};  // 结点定义结束

class SegmentTree {  // 线段树：支持单点修改、区间求和、查最左满足条件的行
public:  // 公开接口
    SegmentTree(int n, int m) {  // 构造函数：n 为行数，m 为每行座位数
        this->m = m;  // 记住每行座位数，建树时叶子初值要用
        tr.resize(n << 2);  // 线段树数组开 4n 个结点，n<<2 即 4n
        for (int i = 0; i < n << 2; ++i) {  // 逐个下标分配结点对象
            tr[i] = new Node();  // 让每个下标都指向一个真实结点，避免空指针
        }  // 分配完毕
        build(1, 1, n);  // 以 1 为根，对区间 [1, n] 递归建树
    }  // 构造函数结束

    void modify(int u, int x, int v) {  // 单点修改：把第 x 行的剩余座位改成 v
        if (tr[u]->l == x && tr[u]->r == x) {  // 已走到叶子，且正是目标行
            tr[u]->s = tr[u]->mx = v;  // 叶子只代表一行，座位和与最大值都设为 v
            return;  // 修改完成，直接返回
        }  // 叶子分支结束
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 取区间中点，>>1 等价于整除 2
        if (x <= mid) {  // 目标行落在左子树
            modify(u << 1, x, v);  // 递归修改左子结点（编号 2u）
        } else {  // 否则目标行落在右子树
            modify(u << 1 | 1, x, v);  // 递归修改右子结点（编号 2u+1）
        }  // 左右分支结束
        pushup(u);  // 子结点信息变了，回溯时重算当前结点的和与最大值
    }  // modify 结束

    long querySum(int u, int l, int r) {  // 查询行区间 [l, r] 的剩余座位总数
        if (tr[u]->l >= l && tr[u]->r <= r) {  // 当前结点区间被查询区间完全覆盖
            return tr[u]->s;  // 直接返回该结点维护的座位和，无需下探
        }  // 否则需要继续递归
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 取区间中点
        long v = 0;  // 答案累加器
        if (l <= mid) {  // 左子树与查询区间有交集
            v += querySum(u << 1, l, r);  // 累加左子树的答案
        }  // 左子树判断结束
        if (r > mid) {  // 右子树与查询区间有交集
            v += querySum(u << 1 | 1, l, r);  // 累加右子树的答案
        }  // 右子树判断结束
        return v;  // 返回区间座位总数
    }  // querySum 结束

    int queryIdx(int u, int l, int r, int k) {  // 在 [l, r] 中找最靠前的一行且该行剩余座位 >= k，找不到返回 0
        if (tr[u]->mx < k) {  // 整段区间的单行最大值都小于 k，一定不存在
            return 0;  // 用 0 表示找不到
        }  // 剪枝判断结束
        if (tr[u]->l == tr[u]->r) {  // 到达叶子，说明这一行满足条件
            return tr[u]->l;  // 返回该行行号
        }  // 叶子判断结束
        int mid = (tr[u]->l + tr[u]->r) >> 1;  // 取区间中点
        if (tr[u << 1]->mx >= k) {  // 先看左子树：它有满足条件的行就优先往左，保证取到最靠前的行
            return queryIdx(u << 1, l, r, k);  // 递归到左子树继续查找
        }  // 左子树判断结束
        if (r > mid) {  // 左子树没有，且查询区间还延伸到右半边
            return queryIdx(u << 1 | 1, l, r, k);  // 递归到右子树查找
        }  // 右子树判断结束
        return 0;  // 两边都没有，返回 0
    }  // queryIdx 结束

private:  // 以下为内部成员
    vector<Node*> tr;  // 线段树结点数组，下标从 1 开始使用
    int m;  // 每行座位数，建树时用作叶子初值

    void build(int u, int l, int r) {  // 递归建树：结点 u 负责区间 [l, r]
        tr[u]->l = l;  // 记录区间左端点
        tr[u]->r = r;  // 记录区间右端点
        if (l == r) {  // 到达叶子，对应单独一行
            tr[u]->s = m;  // 初始时这一行的 m 个座位全空
            tr[u]->mx = m;  // 单行最大值也就是 m
            return;  // 叶子无需继续分裂
        }  // 叶子判断结束
        int mid = (l + r) >> 1;  // 取中点把区间分成两半
        build(u << 1, l, mid);  // 建左子树，负责 [l, mid]
        build(u << 1 | 1, mid + 1, r);  // 建右子树，负责 [mid+1, r]
        pushup(u);  // 用两个子结点算出当前结点的和与最大值
    }  // build 结束

    void pushup(int u) {  // 由两个子结点的信息合并出父结点信息
        tr[u]->s = tr[u << 1]->s + tr[u << 1 | 1]->s;  // 座位和 = 左子树和 + 右子树和
        tr[u]->mx = max(tr[u << 1]->mx, tr[u << 1 | 1]->mx);  // 单行最大值 = 左右子树最大值中的较大者
    }  // pushup 结束
};  // 线段树类定义结束

class BookMyShow {  // 题目要求的订票类
public:  // 公开接口
    BookMyShow(int n, int m) {  // 构造函数：n 行座位，每行 m 个
        this->n = n;  // 保存行数，scatter 里要一直遍历到第 n 行
        this->m = m;  // 保存每行座位数，gather 要用它算列号
        tree = new SegmentTree(n, m);  // 建线段树，初始时每行都有 m 个空位
    }  // 构造函数结束

    vector<int> gather(int k, int maxRow) {  // gather：在 0..maxRow 行里找一整段连续 k 个座位
        ++maxRow;  // 题目行号从 0 开始，线段树从 1 开始，统一转成 1 基
        int i = tree->queryIdx(1, 1, maxRow, k);  // 查最靠前且剩余座位 >= k 的行
        if (i == 0) {  // 返回 0 说明这些行里没有能放下 k 个的
            return {};  // 按题目要求返回空数组
        }  // 找不到的分支结束
        long s = tree->querySum(1, i, i);  // 查第 i 行当前的剩余座位数
        tree->modify(1, i, s - k);  // 这一行扣掉 k 个座位，把新值写回线段树
        return {i - 1, (int) (m - s)};  // 返回 0 基行号，以及这一行已被占用的起始列号 m - s
    }  // gather 结束

    bool scatter(int k, int maxRow) {  // scatter：把 k 个座位分散订在 0..maxRow 行内
        ++maxRow;  // 行号同样转成 1 基
        if (tree->querySum(1, 1, maxRow) < k) {  // 前 maxRow 行的空位总和都不足 k 个
            return false;  // 直接返回失败
        }  // 可行性判断结束
        int i = tree->queryIdx(1, 1, maxRow, 1);  // 找第一行还有空位的行，它前面的行都已经坐满
        for (int j = i; j <= n; ++j) {  // 从这一行开始往后贪心地占用空位
            long s = tree->querySum(1, j, j);  // 查第 j 行剩余座位数
            if (s >= k) {  // 这一行就够放下剩余的 k 个
                tree->modify(1, j, s - k);  // 扣掉 k 个座位写回
                return true;  // 全部安排完毕，返回成功
            }  // 够放的分支结束
            k -= s;  // 这一行坐满，还需要再找 k - s 个座位
            tree->modify(1, j, 0);  // 把这一行剩余座位清成 0
        }  // 循环结束
        return true;  // 总数已经保证够，循环走完即成功
    }  // scatter 结束

private:  // 以下为内部成员
    SegmentTree* tree;  // 线段树对象指针
    int m, n;  // m：每行座位数；n：总行数
};  // BookMyShow 类定义结束

/**
 * Your BookMyShow object will be instantiated and called as such:
 * BookMyShow* obj = new BookMyShow(n, m);
 * vector<int> param_1 = obj->gather(k,maxRow);
 * bool param_2 = obj->scatter(k,maxRow);
 */