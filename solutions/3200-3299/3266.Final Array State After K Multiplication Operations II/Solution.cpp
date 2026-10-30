// 题目：3266. K 次乘运算后的最终数组 II（Final Array State After K Multiplication Operations II）
// 思路：先用小根堆朴素模拟到堆顶元素不小于原数组最大值，此后每次操作都落在最小值上，故剩余 k 次可均摊倍数，用快速幂一次性乘回并按顺序分配余数。
// 时间复杂度：O(n log n + (n log m)·log n + n log k)，空间复杂度：O(n)，用于堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {  // nums：输入数组；k：操作次数；multiplier：每次乘的倍数；返回操作后的数组
        if (multiplier == 1) {  // 乘数为 1 时数组不会发生任何变化
            return nums;  // 直接返回原数组
        }

        using ll = long long;  // ll：长整型别名，元素反复乘 multiplier 后会超出 int 范围
        using pli = pair<ll, int>;  // pli：(值, 下标)，堆中带上原下标以便最后写回结果
        auto cmp = [](const pli& a, const pli& b) {  // cmp：小根堆比较器，先按值升序、值相同时按下标升序
            if (a.first == b.first) {  // 值相等时需要引入下标作为第二关键字
                return a.second > b.second;  // 下标大的排在后面，使 (值, 下标) 字典序最小者位于堆顶
            }
            return a.first > b.first;  // 值大的排在后面，从而构成小根堆
        };
        priority_queue<pli, vector<pli>, decltype(cmp)> pq(cmp);  // 小根堆，堆顶是当前最小的元素

        int n = nums.size();  // n：数组长度
        int m = *max_element(nums.begin(), nums.end());  // m：原数组最大值，也是朴素模拟阶段的上界

        for (int i = 0; i < n; ++i) {  // 初始时把所有元素连同下标一起入堆
            pq.emplace(nums[i], i);  // 元素入堆
        }

        while (k > 0 && pq.top().first < m) {  // 只要还有操作次数且最小值仍小于 m，就继续朴素模拟
            auto p = pq.top();  // 取出当前最小的元素
            pq.pop();  // 先弹出，改完再压回才能维持堆序
            p.first *= multiplier;  // 执行一次乘 multiplier 的操作
            pq.emplace(p);  // 乘完重新入堆
            --k;  // 消耗一次操作次数
        }

        auto qpow = [&](ll a, ll n, ll mod) {  // qpow：快速幂，返回 a 的 n 次方对 mod 取模的结果
            ll ans = 1 % mod;  // ans：幂的累积结果，初值为 1（写成 1 % mod 以兼容 mod=1）
            a = a % mod;  // 底数先取模，避免后续乘法溢出
            while (n > 0) {  // 按指数的二进制位逐位处理
                if (n & 1) {  // 当前二进制位为 1 时，把当前的 a 乘进答案
                    ans = ans * a % mod;  // 累乘并取模
                }
                a = a * a % mod;  // 底数平方，对应指数右移一位
                n >>= 1;  // 指数右移一位
            }
            return ans;  // 返回 a^n mod mod
        };

        const int mod = 1e9 + 7;  // mod：结果取模常量
        for (int i = 0; i < n; ++i) {  // 按 (值, 下标) 升序依次写回数组
            auto p = pq.top();  // 取出当前最小的元素
            pq.pop();  // 出堆
            long long x = p.first;  // x：模拟结束后该元素的值
            int j = p.second;  // j：该元素在原数组中的下标
            nums[j] = static_cast<int>((x % mod) * qpow(multiplier, k / n + (i < k % n ? 1 : 0), mod) % mod);  // 剩余 k 次操作会均摊到 n 个元素：每个多乘 k/n 次，排名前 k%n 的再多乘一次
        }

        return nums;  // 返回最终数组
    }
};
