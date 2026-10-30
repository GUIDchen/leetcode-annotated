// 3756. 连接非零数字并乘以其数字和 II（Concatenate Non-Zero Digits and Multiply by Sum II）
// 核心思路：预处理“非零数字拼接前缀值”“数字和前缀”“非零数字个数前缀”，区间拼接值 = 前缀差乘 10 的非零数字个数次幂，再乘区间数字和即可 O(1) 回答每个查询。
// 复杂度：时间 O(n + q)（n 为串长、q 为查询数），空间 O(n + MX)。
class Solution {  // 定义解法类
public:  // 公有接口
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {  // 接口：返回每个查询区间的答案（拼接值乘数字和）
        static const int MX = 100001;  // MX 是预处理的 10 的幂次上界，覆盖最长字符串长度
        static const int MOD = 1000000007;  // MOD 为题目要求的取模值 1e9 + 7
        static vector<long long> pow10 = [] {  // 用静态 lambda 一次性预计算 10 的幂次表
            vector<long long> p(MX);  // 声明长度为 MX 的 long long 数组
            p[0] = 1;  // 10 的 0 次幂为 1
            for (int i = 1; i < MX; i++) {  // 从 1 次幂开始递推
                p[i] = p[i - 1] * 10 % MOD;  // 每次乘 10 后取模，避免溢出
            }  // for 结束
            return p;  // 返回建好的幂次表
        }();  // 立即执行该 lambda，完成静态初始化

        int n = s.size();  // n 为字符串长度，区间下标换算成 1 基前缀
        vector<int> sumD(n + 1), cntN0(n + 1);  // sumD 存非零数字的数字和前缀，cntN0 存非零数字个数前缀
        vector<long long> p(n + 1);  // p 存把非零数字依次拼接后的前缀值（取模）

        for (int i = 1; i <= n; i++) {  // 从 1 开始逐字符建立前缀数组
            int d = s[i - 1] - '0';  // 取当前位置的字符数字值
            sumD[i] = sumD[i - 1] + d;  // 数字和前缀：加上当前位的数字（零不影响和）
            cntN0[i] = cntN0[i - 1] + (d > 0);  // 非零数字个数前缀：当前位大于 0 时加一
            p[i] = d ? (p[i - 1] * 10 + d) % MOD : p[i - 1];  // 零不参与拼接，前缀值保持不变；非零则左移一位加上该数字
        }  // for 结束

        vector<int> ans;  // 准备存放每个查询的答案
        ans.reserve(queries.size());  // 预留空间，避免反复扩容
        for (auto& q : queries) {  // 逐个处理查询区间 [l, r]
            int l = q[0], r = q[1];  // 取出查询的左右端点
            int n0 = cntN0[r + 1] - cntN0[l];  // 区间内非零数字的个数，用来确定拼接位数
            int sd = sumD[r + 1] - sumD[l];  // 区间内的数字和
            long long x = (p[r + 1] - p[l] * pow10[n0] % MOD + MOD) % MOD;  // 前缀差去掉低位残留后再乘 10 的幂次，得到区间拼接值（补 MOD 保证非负）
            ans.push_back(x * sd % MOD);  // 区间拼接值乘区间数字和，取模后加入答案
        }  // for 结束
        return ans;  // 返回所有查询的答案
    }  // 方法结束
};  // 类定义结束