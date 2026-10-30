// 题目：2819. 购买巧克力后的最小相对损失（Minimum Relative Loss After Buying Chocolates）
// 思路：把价格排序并做前缀和。对询问 [k, m]，最优买法是「最便宜的 l 个按原价买 + 最贵的 m-l 个按惩罚价 2k-price 买」，其中 l 的上界是价格不超过 k 的个数；损失函数关于 l 单调，二分出最优切分点后用前缀和 O(1) 算出损失。
// 时间复杂度：O((n+q)·log n)，排序加每个询问一次二分；空间复杂度：O(n)，前缀和数组。
class Solution {  // 题解类
public:  // 题解方法对外可见
    vector<long long> minimumRelativeLosses(vector<int>& prices, vector<vector<int>>& queries) {  // prices：巧克力价格；queries 每项是 [k, m]；返回每个询问的最小相对损失
        int n = prices.size();  // 巧克力个数
        sort(prices.begin(), prices.end());  // 先排序，之后才能二分与取「最便宜/最贵」的前缀
        long long s[n + 1];  // 前缀和：s[i] 表示最便宜 i 个巧克力的价格之和
        s[0] = 0;  // 前缀和的哨兵：前 0 个价格为 0
        for (int i = 1; i <= n; ++i) {  // 递推填写前缀和
            s[i] = s[i - 1] + prices[i - 1];  // s[i] = 前 i-1 个之和 + 第 i 个（下标 i-1）的价格
        }
        auto f = [&](int k, int m) {  // 二分：求买 m 个时按原价买的数量 l 的最优切分点
            int l = 0, r = upper_bound(prices.begin(), prices.end(), k) - prices.begin();  // r 的上界是价格 <= k 的个数（这些原价买才不会亏）
            r = min(r, m);  // 原价购买的数量不可能超过总数 m
            while (l < r) {  // 在 [0, r] 上二分找最优切分点
                int mid = (l + r) >> 1;  // 二分中点，右移一位等价于除以 2
                int right = m - mid;  // 剩下这些个只能按惩罚价 2k-price 购买，取最贵的几个
                if (prices[mid] < 2LL * k - prices[n - right]) {  // 单调性判断：第 mid 个原价买入是否仍比换成惩罚价购买更划算
                    l = mid + 1;  // 还能多买一个原价的，切分点右移
                } else {  // 否则说明原价买多了
                    r = mid;  // 收缩右边界，保留更小的 mid 作为答案
                }
            }
            return l;  // 返回最优的原价购买数量
        };
        vector<long long> ans;  // 每个询问的答案
        for (auto& q : queries) {  // 逐个处理询问
            int k = q[0], m = q[1];  // 当前询问：k 为阈值参数，m 为要买的个数
            int l = f(k, m);  // 最优的原价购买个数
            int r = m - l;  // 剩下的按惩罚价购买，且取最贵的那些
            ans.push_back(s[l] + 2LL * k * r - (s[n] - s[n - r]));  // 损失 = 原价部分之和 + 惩罚价部分之和（2k·r 减去最贵 r 个的原价和）
        }
        return ans;  // 返回所有询问的答案
    }
};