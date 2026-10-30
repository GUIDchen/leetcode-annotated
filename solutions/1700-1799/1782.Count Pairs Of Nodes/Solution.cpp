// 题目：1782. 统计点对的数目（Count Pairs Of Nodes）
// 思路：先用排序后的度数数组二分统计出所有「度数之和 > 阈值」的点对，再枚举有边的点对做去重修正（减掉重边条数后不再达标的多算了一次）。
// 时间复杂度：O(E + n log n + q * (n log n + E))，q 为查询数；空间复杂度：O(n + E)，存度数、点对表与答案。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {  // n 是点数，edges 是无向边表，queries 是若干阈值
        vector<int> cnt(n);  // cnt[i] 是点 i 的度数（参与的无向边条数，重边按条累加）
        unordered_map<int, int> g;  // 键是编码后的点对，值是这两点之间的重边条数
        for (auto& e : edges) {  // 逐条边建立度数表与重边表
            int a = e[0] - 1, b = e[1] - 1;  // 题目是 1 基下标，转成 0 基
            ++cnt[a];  // a 的度数加一
            ++cnt[b];  // b 的度数加一
            int k = min(a, b) * n + max(a, b);  // 把无序点对编码成唯一整数，保证小的在前
            ++g[k];  // 这对点之间的重边计数加一
        }
        vector<int> s = cnt;  // 复制一份度数数组
        sort(s.begin(), s.end());  // 排序，让「度数之和 > t」可以用二分统计
        vector<int> ans(queries.size());  // 每个查询对应一个答案
        for (int i = 0; i < queries.size(); ++i) {  // 逐个查询处理
            int t = queries[i];  // 当前阈值
            for (int j = 0; j < n; ++j) {  // 枚举点对中较小的那个下标 j
                int x = s[j];  // 排序后第 j 个点的度数
                int k = upper_bound(s.begin() + j + 1, s.end(), t - x) - s.begin();  // 在 j 之后找第一个度数 > t - x 的位置
                ans[i] += n - k;  // 这些点的度数 x + s[k'] 都大于 t，计入答案
            }
            for (auto& [k, v] : g) {  // 修正：前面用的是度数之和，两个相连的点会把公共边算两遍
                int a = k / n, b = k % n;  // 从编码中还原出这对点
                if (cnt[a] + cnt[b] > t && cnt[a] + cnt[b] - v <= t) {  // 度和达标、但扣掉重边条数后不达标
                    --ans[i];  // 说明这对点在二分里被多算了一次，扣掉
                }
            }
        }
        return ans;  // 返回每个查询的答案
    }
};