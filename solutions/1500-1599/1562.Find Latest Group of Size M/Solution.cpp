// 题目：1562. 查找大小为 M 的最新分组（Find Latest Group of Size M）
// 思路：用并查集维护连续 1 的分组，按 arr 顺序把 0 翻成 1 并与左右已翻转的位置合并；每次合并前检查被合并分组的大小是否恰为 m，就能记下长度 m 分组存在的最后时刻。
// 时间复杂度：O(n α(n))，并查集近似常数；空间复杂度：O(n)，父指针、分组大小与访问数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解成员对外可见
    vector<int> p;  // 并查集父指针：p[x] 是 x 的父节点
    vector<int> size;  // 每个根所在连续 1 分组的长度

    int findLatestStep(vector<int>& arr, int m) {  // arr：位置翻转顺序；m：目标分组长度；返回最后一次出现的步数
        int n = arr.size();  // 数组长度，也是位置总数
        if (m == n) return n;  // 整个数组都是 1 时分组长度就是 n，第 n 步自然满足
        p.resize(n);  // 给父指针数组分配空间
        size.assign(n, 1);  // 初始每个位置都是独立分组，长度都为 1
        for (int i = 0; i < n; ++i) p[i] = i;  // 并查集初始化：每个位置自成一个根
        int ans = -1;  // 记录最后一次出现长度 m 分组的步数，-1 表示从未出现
        vector<int> vis(n);  // vis[v] 表示位置 v 是否已经由 0 翻成 1
        for (int i = 0; i < n; ++i) {  // 按顺序执行每一次翻转
            int v = arr[i] - 1;  // 题目位置从 1 开始计数，转成 0 基下标
            if (v && vis[v - 1]) {  // 左边相邻位置已经翻成 1，需要与它合并
                if (size[find(v - 1)] == m) ans = i;  // 合并前左边分组的长度恰为 m，说明该分组此刻仍存在，记下步数
                unite(v, v - 1);  // 把左右两个分组合并成一个
            }  // if 结束
            if (v < n - 1 && vis[v + 1]) {  // 右边相邻位置已经翻成 1，同样需要合并
                if (size[find(v + 1)] == m) ans = i;  // 合并前右边分组的长度恰为 m，同样记下步数
                unite(v, v + 1);  // 合并成一个更大的分组
            }  // if 结束
            vis[v] = true;  // 当前位置正式变成 1
        }  // 循环体结束
        return ans;  // 返回最后一次步数；从未出现则仍为 -1
    }  // 方法结束

    int find(int x) {  // 带路径压缩的查根操作
        if (p[x] != x) p[x] = find(p[x]);  // 父节点不是自己就继续向上查找，并顺手压缩路径
        return p[x];  // 返回根节点
    }  // find 结束

    void unite(int a, int b) {  // 合并 a、b 所在的两个分组
        int pa = find(a), pb = find(b);  // 先找到两个分组的根
        if (pa == pb) return;  // 根相同说明本来就在同一分组，无需合并
        p[pa] = pb;  // 把 a 的根挂到 b 的根下面
        size[pb] += size[pa];  // 合并后新分组长度为两者之和
    }  // unite 结束
};  // 类定义结束