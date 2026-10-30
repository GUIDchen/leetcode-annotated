// 题目：3145. 大数组元素的乘积（Find Products of Elements of Big Array）
// 思路：大数组把每个正整数 x 的二进制位按 2 的幂拆开依次排列；预处理 cnt[i]/s[i]（1..2^i-1 的元素个数与指数和），用 numIdxAndSum 求前缀指数和，二分出区间端点对应的个数，最后快速幂算 2^(指数和之差) mod mod。
// 时间复杂度：O(log^2C)，每次查询二分 O(log C) 次、每次按位统计 O(log C)；空间复杂度：O(m)，m = 50 的常数表。
using ll = long long;  // ll：64 位整数，指数和可能超出 int 范围
const int m = 50;  // m：最大位宽，2^50 已覆盖查询涉及的范围
ll cnt[m + 1];  // cnt[i]：数字 1..2^i-1 的二进制总位数（即在大数组中的元素个数）
ll s[m + 1];  // s[i]：数字 1..2^i-1 的二进制指数总和
ll p = 1;  // p：滚动保存 2^(i-1)，即当前最高位的位权

auto init = [] {  // 立即执行的 lambda：在 main 之前完成常量表预处理
    cnt[0] = 0;  // cnt[0]：1..0 没有数字，元素个数为 0
    s[0] = 0;  // s[0]：同理指数总和为 0
    for (int i = 1; i <= m; ++i) {  // 递推填充 i = 1..m
        cnt[i] = cnt[i - 1] * 2 + p;  // 两个长度 i-1 的半段拼起来，再加新增最高位的 p 个 1
        s[i] = s[i - 1] * 2 + p * (i - 1);  // 新增的最高位共 p 个，每个贡献指数 i-1
        p *= 2;  // 位权翻倍，供下一轮使用
    }
    return 0;  // 返回 0 只是为了让 lambda 有明确的返回类型
}();  // 立即调用，初始化在静态阶段完成

pair<ll, ll> numIdxAndSum(ll x) {  // 求数字 1..x 在大数组中贡献的（元素个数, 指数总和）
    ll idx = 0;  // idx：累计的元素个数
    ll totalSum = 0;  // totalSum：累计的指数总和
    while (x > 0) {  // 不断剥掉当前最高位，一段一段地处理
        int i = 63 - __builtin_clzll(x);  // i：x 的最高位位置（63 减去前导零个数）
        idx += cnt[i];  // 1..2^i-1 已被完整覆盖，累加其元素个数
        totalSum += s[i];  // 同理累加其指数总和
        x -= 1LL << i;  // 去掉最高位，x 变成剩下的低位部分
        totalSum += (x + 1) * i;  // 剩余 x+1 个数都带最高位 i，每个贡献指数 i
        idx += x + 1;  // 每个这样的数还多出一个元素（最高位本身）
    }
    return make_pair(idx, totalSum);  // 返回（元素个数, 指数总和）
}

ll f(ll i) {  // f(i)：大数组前 i 个元素的指数总和
    ll l = 0;  // 二分左界
    ll r = 1LL << m;  // 二分右界：最多用到 2^m 个数
    while (l < r) {  // 找最大的 l，使前 l 个完整数字贡献的元素数 < i
        ll mid = (l + r + 1) >> 1;  // 取上中位，保证区间单调收敛
        auto idxAndSum = numIdxAndSum(mid);  // 计算 mid 对应的前缀信息
        ll idx = idxAndSum.first;  // idx：前 mid 个完整数字贡献的元素个数
        if (idx < i) {  // 前缀不足 i 个元素，答案在右半区
            l = mid;  // 右移左界
        } else {
            r = mid - 1;  // 否则收缩右界
        }
    }

    auto idxAndSum = numIdxAndSum(l);  // 取出前 l 个完整数字的元素个数与指数和
    ll totalSum = idxAndSum.second;  // totalSum：前 l 个完整数字的指数和
    ll idx = idxAndSum.first;  // idx：前 l 个完整数字的元素个数
    i -= idx;  // i 变成还要从数字 l+1 中取的位数
    ll x = l + 1;  // 接下来处理的是数字 l+1
    for (int j = 0; j < i; ++j) {  // 按从低到高的顺序取出还需要的那 i 个元素
        ll y = x & -x;  // y：x 的最低位 1 所对应的值
        totalSum += __builtin_ctzll(y);  // 该位对应的指数 = y 尾随零的个数
        x -= y;  // 删掉这一位，继续取下一个
    }
    return totalSum;  // 返回大数组前 i 个元素（函数入参）的指数总和
}

ll qpow(ll a, ll n, ll mod) {  // 快速幂：计算 a^n mod mod
    ll ans = 1 % mod;  // 结果为 1，先对 mod 取模以兼容 mod = 1
    a = a % mod;  // 底数取模，避免溢出
    while (n > 0) {  // 把指数按二进制分解
        if (n & 1) {  // 当前二进制位为 1 才需要乘
            ans = ans * a % mod;  // 累乘并取模
        }
        a = a * a % mod;  // 底数平方
        n >>= 1;  // 指数右移一位
    }
    return ans;  // 返回 a^n mod mod
}

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findProductsOfElements(vector<vector<ll>>& queries) {  // queries[i] = [left, right, mod]
        int n = queries.size();  // n：查询个数
        vector<int> ans(n);  // ans：每个查询的答案
        for (int i = 0; i < n; ++i) {  // 逐个查询求解
            ll left = queries[i][0];  // left：区间左端点
            ll right = queries[i][1];  // right：区间右端点
            ll mod = queries[i][2];  // mod：取模数
            ll power = f(right + 1) - f(left);  // 两段前缀指数和之差 = 区间内所有元素的指数和
            ans[i] = static_cast<int>(qpow(2, power, mod));  // 大数组元素都是 2 的幂，乘积即 2^指数和，再取模
        }
        return ans;  // 返回所有查询的答案
    }
};
