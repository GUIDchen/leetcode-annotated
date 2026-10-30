// 题目：1937. 扣分后的最大得分（Maximum Number of Points with Cost）
// 思路：逐行 DP，把转移代价 |j-k| 拆成 f[k]+k 与 f[k]-k 两种形式，用左右两遍扫描取前缀最大值。
// 时间复杂度：O(mn)；空间复杂度：O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxPoints(vector<vector<int>>& points) {  // 返回按行取格子能获得的最大得分
        using ll = long long;  // 得分累加可能超过 int 范围，统一用 64 位整数
        int n = points[0].size();  // 列数，每一行长度都相同
        vector<ll> f(n);  // f[j] 表示上一行选择列 j 时能取得的最高得分
        const ll inf = 1e18;  // 足够小的「负无穷」占位值，保证第一次比较一定被更新
        for (auto& p : points) {  // 逐行处理
            vector<ll> g(n);  // 当前行的 DP 数组
            ll lmx = -inf, rmx = -inf;  // 从左 / 从右扫描时维护的最优前缀值
            for (int j = 0; j < n; ++j) {  // 从左往右扫描
                lmx = max(lmx, f[j] + j);  // 把 f[k] - (j - k) 改写成 (f[k] + k) - j，就能用前缀最大值一次取到最优来源
                g[j] = max(g[j], p[j] + lmx - j);  // 用左侧最优来源更新当前格
            }  // for 结束
            for (int j = n - 1; ~j; --j) {  // 从右往左扫描，~j 等价于 j >= 0
                rmx = max(rmx, f[j] - j);  // 对称地维护 (f[k] - k) 的前缀最大值
                g[j] = max(g[j], p[j] + rmx + j);  // 用右侧最优来源更新当前格
            }  // for 结束
            f = move(g);  // 滚动：把当前行结果当作上一行
        }  // for 结束
        return *max_element(f.begin(), f.end());  // 最后一行的最大得分就是答案
    }  // 方法结束
};  // 类结束