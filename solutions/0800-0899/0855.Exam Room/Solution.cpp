// 题目：855. 考场就座（Exam Room）
// 思路：用有序集合维护所有空区间，按「落座后与最近者的距离」排序，每次取最优区间拆成两段；leave 时合并左右两段。
// 时间复杂度：单次 seat/leave 为 O(log n)；空间复杂度：O(n)，存放空区间与前后驱映射。
int N;  // 全局变量：座位总数，供全局比较函数 dist 使用

int dist(const pair<int, int>& p) {  // 计算空区间可落座位置到最近者的距离
    auto [l, r] = p;  // 结构化绑定取出区间左右端点
    if (l == -1 || r == N) return r - l - 1;  // 贴着边界时只能坐在端点，距离为区间长度
    return (r - l) >> 1;  // 否则坐在中间，距离为区间长度的一半（向下取整）
}  // 函数结束

struct cmp {  // 自定义比较器：距离大的优先，距离相同时左端点小的优先
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {  // 返回 true 表示 a 的优先级高于 b
        int d1 = dist(a), d2 = dist(b);  // 分别计算两个区间的落座距离
        return d1 == d2 ? a.first < b.first : d1 > d2;  // 距离相同则比左端点，否则距离大的排前面
    };  // 比较函数结束
};  // 比较器结构体结束

class ExamRoom {  // 考场类
public:  // 对外提供构造与座位操作
    ExamRoom(int n) {  // 构造函数：n 为座位总数
        N = n;  // 同步全局变量，供 dist 使用
        this->n = n;  // 记录到成员变量
        add({-1, n});  // 初始只有一个「虚拟左边界 → 虚拟右边界」的空区间
    }  // 构造完成

    int seat() {  // 安排一人就座并返回座位号
        auto s = *ts.begin();  // 取出优先级最高（落座距离最大）的空区间
        int p = (s.first + s.second) >> 1;  // 默认坐在区间中点
        if (s.first == -1) {  // 区间贴着左边界
            p = 0;  // 只能坐 0 号座位
        } else if (s.second == n) {  // 区间贴着右边界
            p = n - 1;  // 只能坐最后一个座位
        }  // 边界情况处理完毕
        del(s);  // 该区间已被占用，先删除
        add({s.first, p});  // 把区间拆成左半段
        add({p, s.second});  // 把区间拆成右半段
        return p;  // 返回落座位置
    }  // seat 结束

    void leave(int p) {  // p 位置的人离开
        int l = left[p], r = right[p];  // 找到 p 左右相邻的已坐位置
        del({l, p});  // 删除左半段区间
        del({p, r});  // 删除右半段区间
        add({l, r});  // 合并成一个大区间
    }  // leave 结束

private:  // 私有成员：内部实现细节
    set<pair<int, int>, cmp> ts;  // 所有空区间，按落座优先级排序
    unordered_map<int, int> left;  // 已坐位置 → 左侧最近的已坐位置
    unordered_map<int, int> right;  // 已坐位置 → 右侧最近的已坐位置
    int n;  // 座位总数

    void add(pair<int, int> s) {  // 加入一个空区间并维护前后驱映射
        ts.insert(s);  // 插入有序集合
        left[s.second] = s.first;  // 记录右端点的左邻居
        right[s.first] = s.second;  // 记录左端点的右邻居
    }  // add 结束

    void del(pair<int, int> s) {  // 删除一个空区间并清理前后驱映射
        ts.erase(s);  // 从有序集合移除
        left.erase(s.second);  // 清理右端点的左邻居记录
        right.erase(s.first);  // 清理左端点的右邻居记录
    }  // del 结束
};  // 考场类结束

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */