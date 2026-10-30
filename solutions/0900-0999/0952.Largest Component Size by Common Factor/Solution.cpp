// 题目：952. 按公因数计算最大组件大小（Largest Component Size by Common Factor）
// 思路：并查集把小因子当作中间节点；对每个数枚举素数因子，把数与因子合并，最后统计每个根下有多少个原数组元素，取最大值。
// 时间复杂度：O(n·√M·α)，M 为最大数值；空间复杂度：O(M)，父指针数组大小与最大数值同阶。
class UnionFind {  // 并查集：维护「数值 / 因子」之间的连通关系
public:  // 以下成员对外可见
    vector<int> p;  // 父指针数组，节点编号就是数值本身
    int n;  // 节点总数（最大数值 + 1）

    UnionFind(int _n)  // 构造函数，_n 为新并查集的节点个数
        : n(_n)  // 初始化成员 n（初始化列表）
        , p(_n) {  // 按节点个数开好父指针数组的空间
        iota(p.begin(), p.end(), 0);  // 初始时每个节点自成一个集合
    }

    void unite(int a, int b) {  // 合并 a、b 所在集合（这里不按大小合并）
        int pa = find(a), pb = find(b);  // 分别求出两个节点所在集合的根
        if (pa != pb) p[pa] = pb;  // 根不同说明还没连通，直接让 pa 指向 pb 完成合并
    }

    int find(int x) {  // 查找 x 的根，并做路径压缩
        if (p[x] != x) p[x] = find(p[x]);  // 若 x 的父指针不是自己，就递归找根并把路径压缩
        return p[x];  // 返回根节点
    }
};

class Solution {  // 题解主类
public:  // 题解方法对外可见
    int largestComponentSize(vector<int>& nums) {  // nums：待分组的一组正整数
        int m = *max_element(nums.begin(), nums.end());  // m 取数组最大值，用它决定并查集的规模
        UnionFind* uf = new UnionFind(m + 1);  // 节点 0..m 覆盖所有可能出现的数值与因子，动态分配避免爆栈
        for (int v : nums) {  // 逐个处理数组中的每个数
            int i = 2;  // 从 2 开始枚举因子，1 不能作为连通依据
            while (i <= v / i) {  // 只需枚举到 sqrt(v)，写成 i <= v / i 可避免乘法溢出
                if (v % i == 0) {  // 找到了一个因子 i
                    uf->unite(v, i);  // 把数 v 与它的因子 i 合并到同一连通块
                    uf->unite(v, v / i);  // 同时把配对的另一个因子 v / i 也合并进来
                }
                ++i;  // 因子试探前进一位
            }
        }
        vector<int> cnt(m + 1);  // cnt[t] 记录以 t 为根的连通块里有多少个原数组元素
        int ans = 0;  // ans 记录最大组件大小
        for (int v : nums) {  // 再遍历一次数组做统计
            int t = uf->find(v);  // 找到当前元素所在连通块的根
            ++cnt[t];  // 该根对应的组件大小加一
            ans = max(ans, cnt[t]);  // 用当前组件大小刷新答案
        }
        return ans;  // 返回最大组件大小
    }
};