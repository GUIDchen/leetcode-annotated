// 题目：2524. 子数组的最大频率分数（Maximum Frequency Score of a Subarray）
// 思路：固定长度 k 的滑动窗口 + 哈希计数，用快速幂增量维护窗口分数（移入加、移出减）。
// 时间复杂度：O(n log k)，每次移动做常数次快速幂；空间复杂度：O(n)，哈希表最多存 n 种值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxFrequencyScore(vector<int>& nums, int k) {  // nums：原数组；k：子数组长度；返回所有长度 k 子数组的「频率分数」最大值
        using ll = long long;  // 定义长整型别名，分数会超过 int 范围，中间结果必须用 64 位
        const int mod = 1e9 + 7;  // 模数 1e9+7，题目要求分数对 10^9+7 取模
        auto qpow = [&](ll a, ll n) {  // 快速幂 Lambda：计算 a^n mod mod，供下面反复复用
            ll ans = 1;  // 幂的累乘结果
            for (; n; n >>= 1) {  // n 不断右移，直到指数变成 0
                if (n & 1) {  // 指数当前最低位为 1，需要把 a 乘进结果
                    ans = ans * a % mod;  // 把 a 乘进答案并取模
                }  // 指数最低位为 0，跳过这一位
                a = a * a % mod;  // a 自乘，为下一位准备（a^(2^b)）
            }  // 指数位移循环结束
            return ans;  // 返回 a^n mod mod
        };  // 快速幂 Lambda 定义结束
        unordered_map<int, int> cnt;  // 统计当前长度为 k 的滑动窗口内每个值出现的次数
        for (int i = 0; i < k; ++i) {  // 先暴力统计第一个窗口的 k 个元素
            cnt[nums[i]]++;  // 对应元素计数加一
        }  // 第一个窗口统计完成
        ll cur = 0;  // 当前窗口的频率分数，即各不同值的「值^出现次数」之和
        for (auto& [k, v] : cnt) {  // 结构化解包遍历哈希表：k 是元素值，v 是它出现的次数
            cur = (cur + qpow(k, v)) % mod;  // 累加 value^count 并随时取模，防止溢出
        }  // 第一个窗口的分数算完
        ll ans = cur;  // 答案初值取第一个窗口的分数
        for (int i = k; i < nums.size(); ++i) {  // 窗口右移：i 是新进入窗口的位置，同时 nums[i-k] 会离开窗口
            int a = nums[i - k], b = nums[i];  // a 是要移出的旧元素，b 是要移入的新元素
            if (a != b) {  // 新旧元素相同时窗口多重集不变，分数不变，无需重算
                cur += cnt[b] ? (b - 1) * qpow(b, cnt[b]) % mod : b;  // 新增一个 b：若原本已有 cnt[b] 个，b^cnt[b] 变成 b^(cnt[b]+1)，增量是 (b-1)*b^cnt[b]，否则从 0 变 b
                cur -= cnt[a] > 1 ? (a - 1) * qpow(a, cnt[a] - 1) % mod : a;  // 删掉一个 a：若原本有 cnt[a] 个且 cnt[a]>1，a^cnt[a] 变成 a^(cnt[a]-1)，减少 (a-1)*a^(cnt[a]-1)，否则直接减 a
                cur = (cur + mod) % mod;  // 加上 mod 再取模，把上一步可能得到的负数修正为非负
                ans = max(ans, cur);  // 用当前窗口分数更新最大值
                cnt[b]++;  // b 的计数加一，表示它已进入窗口
                cnt[a]--;  // a 的计数减一，表示它已离开窗口
            }  // if 分支结束
        }  // 滑动窗口遍历结束
        return ans;  // 返回所有窗口中的最大频率分数
    }  // 方法结束
};  // 类定义结束