// 题目：2580. 统计将重叠区间合并成组的方案数（Count Ways to Group Overlapping Ranges）
// 思路：按左端点排序后顺序合并相交区间，得到 cnt 个互不相交的组；每组可并入左侧或右侧集合，方案数为 2^cnt，用快速幂取模。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，除输入外只用常数个变量（排序需要 O(log n) 栈空间）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countWays(vector<vector<int>>& ranges) {  // ranges 是若干闭区间，返回把它们合并分组后的方案数
        sort(ranges.begin(), ranges.end());  // 按左端点（相同时按右端点）排序，方便顺序判断区间是否相交
        int cnt = 0, mx = -1;  // cnt 统计合并后的组数；mx 记录当前组覆盖到的最右端点
        for (auto& e : ranges) {  // 依次扫描每个区间
            cnt += e[0] > mx;  // 左端点超过 mx 说明与当前组不相交，必须新开一组；比较结果为 bool，隐式转成 0/1 累加
            mx = max(mx, e[1]);  // 用当前区间右端点更新这一组的覆盖范围
        }
        using ll = long long;  // 起别名，让模乘用 64 位整数，避免两个 1e9 级别的数相乘溢出
        auto qpow = [&](ll a, int n, int mod) {  // 手写快速幂 lambda：计算 a^n % mod
            ll ans = 1;  // 结果初值为 1，即乘法单位元
            for (; n; n >>= 1) {  // 指数逐位右移，直到 n 变成 0
                if (n & 1) {  // 当前最低位为 1，说明这一份的 a 要乘进答案
                    ans = ans * a % mod;  // 累乘并取模
                }
                a = a * a % mod;  // 底数自平方，为处理下一位做准备
            }
            return ans;  // 返回 a^n % mod，返回类型由 lambda 自动推导为 ll
        };
        return qpow(2, cnt, 1e9 + 7);  // 每个组都可以自由选择归入左侧还是右侧集合，共 2^cnt 种方案
    }
};