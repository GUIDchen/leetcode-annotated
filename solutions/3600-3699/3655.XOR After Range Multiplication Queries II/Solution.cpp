// 3655. 区间乘法查询后的异或 II（XOR After Range Multiplication Queries II）
// 核心思路：按步长 sqrt(n) 分治——大步长查询次数少，直接逐个下标相乘；小步长查询按 (k, l mod k) 落到一条等差数列上，用「乘 v」与「乘 v 的逆元」两个事件做差分，再排序合并同一序号的因子，最后沿等差数列扫描施加前缀乘积。
// 复杂度：时间 O((n + q)·sqrt(n) + q·log q)，空间 O(n + q)，其中 q 为查询数。
class Solution {  // 定义题解类
    static constexpr int MOD = 1000000007;  // 取模常量 10^9 + 7

    long long modpow(long long a, long long e) {  // 快速幂：计算 a^e mod MOD
        long long r = 1 % MOD;  // 结果先置为 1（显式保留 long long 类型）
        a %= MOD;  // 底数先取模
        while (e > 0) {  // 按指数的二进制位循环
            if (e & 1) { r = (r * a) % MOD; }  // 当前二进制位为 1 时把 a 累乘进结果
            a = (a * a) % MOD;  // 底数平方，准备处理下一位
            e >>= 1;  // 指数右移一位
        }  // 快速幂循环结束
        return r;  // 返回 a^e mod MOD
    }  // modpow 结束

public:  // 公有接口
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {  // 依次执行所有查询，返回最终数组所有元素的异或值；大步长直接模拟，小步长用差分批量处理
        int n = nums.size();  // 数组长度
        int B = sqrt(n) + 1;  // 分块阈值：步长 <= B 的查询走差分批量，步长 > B 的查询直接模拟

        vector<vector<vector<pair<int, int>>>> events(B + 1);  // events[k][res] 记录等差数列（下标 ≡ res (mod k)，序号 t = (idx - res) / k）上的乘子事件
        for (int k = 1; k <= B; ++k) {  // 为每个小步长预备 k 个同余分支
            events[k].resize(k);  // 步长 k 对应 k 个余数分支
        }  // 初始化结束

        for (auto& qq : queries) {  // 依次处理每个查询
            int l = qq[0], r = qq[1], k = qq[2], v = qq[3];  // 拆出左端点、右端点、步长、乘数
            if (k > B) {  // 大步长：这类查询次数少，直接逐个下标相乘
                for (int idx = l; idx <= r; idx += k) {  // 按步长枚举区间内的下标
                    nums[idx] = (long long) nums[idx] * v % MOD;  // 该位置乘上 v 并取模
                }  // 大步长枚举结束
            } else {  // 小步长：转成等差数列上的差分事件
                int res = l % k;  // 该等差数列的余数（首项下标对 k 取模）
                int t1 = (l - res) / k;  // l 在这条等差数列中的序号
                int t2 = (r - res) / k;  // r 在这条等差数列中的序号
                events[k][res].push_back({t1, v});  // 从序号 t1 起乘上 v

                if (t2 + 1 <= (n - 1 - res) / k) {  // 若 t2 之后在这条等差数列里还有下标
                    int invv = modpow(v, MOD - 2);  // 用费马小定理求 v 的模逆元
                    events[k][res].push_back({t2 + 1, invv});  // 在序号 t2 + 1 处乘逆元，抵消这次乘法
                }  // 差分右端点判断结束
            }  // 大步长 / 小步长分支结束
        }  // 查询遍历结束

        for (int k = 1; k <= B; ++k) {  // 逐个小步长处理
            for (int res = 0; res < k; ++res) {  // 逐个余数（逐条等差数列）处理
                auto& ev = events[k][res];  // 取出该等差数列上的全部事件
                if (ev.empty()) {  // 没有事件则无需处理
                    continue;  // 跳过这条等差数列
                }  // 空判断结束

                sort(ev.begin(), ev.end());  // 按序号 t 排序，便于合并同一位置的事件并顺序扫描
                vector<pair<int, int>> comp;  // comp 存放合并后的事件（同一 t 的因子相乘）

                for (auto& p : ev) {  // 遍历排序后的事件
                    if (!comp.empty() && comp.back().first == p.first) {  // 与上一条事件的序号相同
                        comp.back().second = (long long) comp.back().second * p.second % MOD;  // 把因子合并到同一事件上
                    } else {  // 序号不同
                        comp.push_back(p);  // 作为新事件追加
                    }  // 合并分支结束
                }  // 事件合并结束

                long long cur = 1;  // cur 维护扫描到当前序号时的累积乘子
                int ptr = 0;  // ptr 指向 comp 中下一个待生效的事件
                int t = 0;  // t 为当前在等差数列中的序号
                for (int idx = res; idx < n; idx += k, ++t) {  // 沿这条等差数列从小到大扫描
                    while (ptr < comp.size() && comp[ptr].first == t) {  // 把序号等于 t 的事件全部生效
                        cur = (cur * comp[ptr].second) % MOD;  // 累积乘子乘上该事件的因子
                        ++ptr;  // 移动到下一个事件
                    }  // 事件生效结束
                    nums[idx] = nums[idx] * cur % MOD;  // 把累积乘子施加到该位置
                }  // 等差数列扫描结束
            }  // 余数循环结束
        }  // 步长循环结束

        int xr = 0;  // 异或结果从 0 开始
        for (int x : nums) {  // 遍历最终数组
            xr ^= x;  // 逐个异或累加
        }  // 遍历结束

        return xr;  // 返回所有元素的异或值
    }  // xorAfterQueries 结束
};  // 类定义结束
