// 题目：2312. 卖木头块（Selling Pieces of Wood）
// 思路：记忆化搜索。dfs(h, w) 求 h×w 木块能卖出的最大钱数：先取整块直接卖的价格 d[h][w]，再枚举横切与竖切的位置（只枚举到一半，另一半对称），把两块的 dfs 值相加，最后取最大值并缓存。
// 时间复杂度：O(m·n·(m+n))，共 m·n 个状态，每个状态枚举 O(h+w) 种切法；空间复杂度：O(m·n)，记忆化数组与价格表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long sellingWood(int m, int n, vector<vector<int>>& prices) {  // prices[i] = {高, 宽, 价格}，返回能卖出的最大总价
        using ll = long long;  // 起别名，后面不必反复写 long long
        ll f[m + 1][n + 1];  // 记忆化数组：f[h][w] 是 h×w 木块的最大收益，下标从 1 开始便于按尺寸直接取值
        int d[m + 1][n + 1];  // 价格表：d[h][w] 是整块 h×w 直接卖出的价格，0 表示该尺寸没有报价
        memset(f, -1, sizeof(f));  // 全部置 -1 表示「尚未计算」；收益非负，所以 -1 不会与合法答案混淆
        memset(d, 0, sizeof(d));  // 价格表清零，没有出现过的尺寸默认卖不出钱
        for (auto& p : prices) {  // 把每条报价写进价格表
            d[p[0]][p[1]] = p[2];  // p = {高, 宽, 价格}
        }
        function<ll(int, int)> dfs = [&](int h, int w) -> ll {  // 记忆化搜索：h、w 是当前木块的高与宽，按引用捕获上面的数组
            if (f[h][w] != -1) {  // 已经算过，直接返回缓存，避免重复搜索
                return f[h][w];  // 返回缓存中的最优值
            }
            ll ans = d[h][w];  // 方案一：不切，整块直接卖掉
            for (int i = 1; i < h / 2 + 1; ++i) {  // 枚举横向切分，切在高度 i 处；只枚举到一半，另一半与它对称
                ans = max(ans, dfs(i, w) + dfs(h - i, w));  // 上面 i×w 与下面 (h-i)×w 各自取最优后相加
            }
            for (int i = 1; i < w / 2 + 1; ++i) {  // 枚举纵向切分，切在宽度 i 处，同样只枚举一半
                ans = max(ans, dfs(h, i) + dfs(h, w - i));  // 左边 h×i 与右边 h×(w-i) 各自取最优后相加
            }
            return f[h][w] = ans;  // 把答案写回缓存，同时作为返回值
        };  // lambda 定义结束
        return dfs(m, n);  // 从整块 m×n 开始求解
    }
};