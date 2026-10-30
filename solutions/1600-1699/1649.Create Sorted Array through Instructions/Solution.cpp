// 题目：1649. 通过指令创建有序数组（Create Sorted Array through Instructions）
// 思路：树状数组统计已插入值的出现次数；处理 x 时，左侧严格小的个数 = query(x-1)，右侧严格大的个数 = i - query(x)，取较小者累加。
// 时间复杂度：O(n log m)，m 为最大值；空间复杂度：O(m)，树状数组需要 m+1 个桶。
class BinaryIndexedTree {  // 树状数组（BIT）：用 O(log m) 完成单点修改与前缀和查询
public:  // 公有接口：构造、更新、前缀和查询
    BinaryIndexedTree(int _n)  // 构造函数：_n 为值域上界
        : n(_n)  // 初始化列表：保存上界供 update 判越界
        , c(_n + 1) {}  // 开 _n+1 个桶，下标从 1 开始，方便 lowbit 运算

    void update(int x, int delta) {  // 单点更新：在下标 x 处加上 delta
        while (x <= n) {  // 沿 lowbit 逐级向上，更新所有覆盖 x 的节点
            c[x] += delta;  // 当前节点累加增量
            x += x & -x;  // x += lowbit(x) 跳到下一个覆盖 x 的位置
        }  // 更新循环结束
    }  // update 方法结束

    int query(int x) {  // 前缀和查询：返回下标 1..x 的元素总和
        int s = 0;  // 累加器初始化为 0
        while (x) {  // x 还没减到 0 就继续累加
            s += c[x];  // 累加当前节点维护的那一段区间和
            x -= x & -x;  // x -= lowbit(x) 跳到前一个不重叠区间
        }  // 查询循环结束
        return s;  // 返回前缀和
    }  // query 方法结束

private:  // 私有成员：只在类内部使用
    int n;  // 值域上界
    vector<int> c;  // 树状数组本体，c[i] 维护一段区间的计数和
};  // 树状数组类定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int createSortedArray(vector<int>& instructions) {  // instructions 是依次插入的数值，返回每次插入代价之和取模
        int m = *max_element(instructions.begin(), instructions.end());  // 值域上界取最大元素，树状数组只需覆盖 1..m
        BinaryIndexedTree tree(m);  // 按最大值建树状数组
        const int mod = 1e9 + 7;  // 题目要求的取模常量 1e9+7
        int ans = 0;  // 累计的最小代价
        for (int i = 0; i < instructions.size(); ++i) {  // 按指令顺序逐个插入
            int x = instructions[i];  // 本次要插入的值
            int cost = min(tree.query(x - 1), i - tree.query(x));  // 代价 = min(左侧严格小于 x 的个数, 已插入元素中严格大于 x 的个数)，i - query(x) 正是后者
            ans = (ans + cost) % mod;  // 累加代价并及时取模，防止溢出
            tree.update(x, 1);  // 把 x 的计数加一，供后续指令统计
        }  // 遍历结束
        return ans;  // 返回总代价
    }  // 方法结束
};  // Solution 类定义结束