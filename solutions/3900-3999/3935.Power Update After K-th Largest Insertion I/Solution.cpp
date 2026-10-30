// 3935. 插入后第 K 大更新的幂 I / Power Update After K-th Largest Insertion I
// 核心思路：用两个有序计数 map 分别维护「最大的 k 个」与「其余元素」，每次插入后调整规模，取第 k 大做快速幂更新 p。
// 复杂度：时间 O((n + q) log n + q log mod)，空间 O(n)。
class Solution {  // 题解类定义
public:  // 公开接口
    using ll = long long;  // 长整型别名，防止乘法溢出

    void add(map<int, int>& mp, int x) {  // 向有序计数表中加入一个 x
        ++mp[x];  // 该值出现次数加 1
    }  // add 函数结束

    void remove(map<int, int>& mp, int x) {  // 从有序计数表中删除一个 x
        if (--mp[x] == 0) {  // 计数减 1 后变为 0
            mp.erase(x);  // 彻底删除键，保证 begin() 指向最小的有效元素
        }  // if 分支结束
    }  // remove 函数结束

    ll qpow(ll a, int b, int mod) {  // 快速幂：计算 a^b mod mod
        ll ans = 1;  // 累乘结果初始化为 1

        while (b) {  // 按二进制位从低到高处理指数
            if (b & 1) {  // 当前最低位为 1 时累乘
                ans = ans * a % mod;  // 乘入当前底数并取模
            }  // if 分支结束

            a = a * a % mod;  // 底数平方，对应指数右移一位
            b >>= 1;  // 指数右移一位
        }  // while 结束

        return ans;  // 返回快速幂结果
    }  // qpow 函数结束

    vector<int> powerUpdate(vector<int>& nums, int p, vector<vector<int>>& queries) {  // 主函数：逐条处理查询并返回每次更新后的 p
        map<int, int> l, r;  // l 存放较小的元素，r 存放最大的 k 个元素

        int sz1 = 0, sz2 = nums.size();  // 两个有序表的元素个数

        for (int x : nums) {  // 初始时把所有元素放入 r
            add(r, x);  // 插入 r
        }  // 初始装填结束

        const int mod = 1e9 + 7;  // 幂运算的模数

        vector<int> ans;  // 记录每次查询后的 p

        for (auto& q : queries) {  // 逐条处理查询
            int val = q[0];  // 本次要插入的值
            int k = q[1];  // 本次要求的前 k 大

            add(r, val);  // 新值先插入 r
            ++sz2;  // r 的元素个数加 1

            int v = r.begin()->first;  // 取出 r 中最小的元素

            remove(r, v);  // 从 r 中移除它
            --sz2;  // r 的元素个数减 1

            add(l, v);  // 放进 l，保证 r 只留下最大的 k 个
            ++sz1;  // l 的元素个数加 1

            while (sz2 < k) {  // r 中元素不足 k 个时从 l 补充
                v = l.rbegin()->first;  // 取 l 中最大的元素

                remove(l, v);  // 从 l 中删除
                --sz1;  // l 的元素个数减 1

                add(r, v);  // 移入 r
                ++sz2;  // r 的元素个数加 1
            }  // 补充循环结束

            while (sz2 > k) {  // r 中元素多于 k 个时把最小的移出
                v = r.begin()->first;  // 取 r 中最小的元素

                remove(r, v);  // 从 r 中删除
                --sz2;  // r 的元素个数减 1

                add(l, v);  // 移入 l
                ++sz1;  // l 的元素个数加 1
            }  // 移出循环结束

            int x = r.begin()->first;  // r 的最小元素就是第 k 大元素

            p = qpow(p, x, mod);  // 把 p 更新为 p^x mod mod

            ans.push_back(p);  // 记录本次查询的答案
        }  // 查询循环结束

        return ans;  // 返回所有答案
    }  // powerUpdate 函数结束
};  // 类定义结束