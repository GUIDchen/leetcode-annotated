// 题目：3753. 范围内总波动值 II（Total Waviness of Numbers in Range II）
// 核心思路：区间和化为 calc(num2) - calc(num1 - 1)；用数位 DP 从高位逐位填数，状态记录位置、前两位数字、是否已开始填数、是否贴上界，同时返回「能形成的数字个数」与「这些数字的波动值总和」，新出现的峰谷贡献要乘以后缀方案数。
// 复杂度：时间 O(位数 × 11 × 11 × 2 × 10)，即 O(log x)；空间 O(位数 × 11 × 11 × 2 × 2)，记忆化表规模与上界位数成正比。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long totalWaviness(long long num1, long long num2) {  // 返回闭区间 [num1, num2] 内所有数字的波动值之和
        return calc(num2) - calc(num1 - 1);  // 用前缀和之差把区间查询化为两个前缀查询
    }  // 方法结束

private:  // 以下是内部实现，只供本类成员使用
    string s;  // s 存放当前上界的十进制字符串
    long long fCnt[20][11][11][2];  // fCnt 记忆化：该状态下能形成的数字个数
    long long fWav[20][11][11][2];  // fWav 记忆化：该状态下所有数字的波动值之和
    bool vis[20][11][11][2];  // vis 标记该状态是否已经算过

    long long calc(long long x) {  // 返回 [0, x] 内所有数字的波动值之和（x < 0 时为空区间）
        if (x < 0) {  // x 为负数说明区间为空
            return 0;  // 直接返回 0
        }  // if 分支结束
        s = to_string(x);  // 把上界转成字符串，便于逐位取数
        memset(vis, 0, sizeof(vis));  // 清空记忆化标记，本次上界下的缓存从头开始
        return dfs(0, 10, 10, 0, true).second;  // 从最高位开始：前两位未填、未开始填数、贴着上界；取返回值的 second 即波动值之和
    }  // 方法结束

    pair<long long, long long> dfs(int pos, int prev2, int prev1, int started, bool limit) {  // 数位 DP：pos 为当前位，prev2/prev1 为前两位数字（10 表示尚未填），started 表示是否已开始填数，limit 表示是否贴上界；返回 {数字个数, 波动值之和}
        if (pos == s.size()) {  // 已经填完全部数位
            return {started, 0};  // 已开始填数就是一个合法正整数，个数记 started；末位不再产生新的峰谷
        }  // 递归出口结束
        if (!limit && vis[pos][prev2][prev1][started]) {  // 不受上界限制时状态可复用，命中缓存就直接返回
            return {fCnt[pos][prev2][prev1][started], fWav[pos][prev2][prev1][started]};  // 取出缓存的数字个数与波动值之和
        }  // 缓存分支结束
        int up = limit ? s[pos] - '0' : 9;  // 贴着上界时当前位最多取到 s[pos]，否则可以取到 9
        long long c = 0, w = 0;  // c 统计数字个数，w 统计波动值之和
        for (int d = 0; d <= up; ++d) {  // 枚举当前位填入的数字 d
            bool nlimit = limit && d == up;  // 只有前缀一直紧贴上界，限制才会继续传递
            int ns, np2, np1, add = 0;  // ns 为新的 started，np2/np1 为新的前两位，add 表示这一位是否形成峰谷
            if (started == 0) {  // 还没开始填数时，要区分继续前导零和填入首位非零数字
                if (d == 0) {  // 仍然填 0，继续保持前导零状态
                    ns = 0;  // 仍未开始填数
                    np2 = 10;  // 前两位仍视为未填
                    np1 = 10;  // 前一位也视为未填
                } else {  // 否则填入了首位非零数字，数字正式开始
                    ns = 1;  // 标记已开始填数
                    np2 = 10;  // 更早的一位还没有，记为未填
                    np1 = d;  // 前一位就是刚填入的 d
                }  // if 分支结束
            } else {  // 已经在填数，直接向后推进状态
                ns = 1;  // 已开始填数
                np2 = prev1;  // 原来的一位变成前两位
                np1 = d;  // 当前位成为新的前一位
                if (prev2 != 10 && ((prev1 > prev2 && prev1 > d) || (prev1 < prev2 && prev1 < d))) {  // 前两位都存在且 prev1 严格大于或严格小于两侧，说明 prev1 是峰或谷
                    add = 1;  // 这一位贡献 1 个波动值
                }  // if 分支结束
            }  // else 分支结束
            auto [tc, tw] = dfs(pos + 1, np2, np1, ns, nlimit);  // 递归处理下一位，拿到后缀的数字个数与波动值之和
            c += tc;  // 累加子问题的数字个数
            w += tw + tc * add;  // 累加子问题的波动值，并加上本层新增的峰谷贡献（要乘以方案数）
        }  // 当前位枚举结束
        if (!limit) {  // 只有不受上界限制的状态才通用，可以写入缓存
            vis[pos][prev2][prev1][started] = true;  // 标记该状态已计算
            fCnt[pos][prev2][prev1][started] = c;  // 缓存数字个数
            fWav[pos][prev2][prev1][started] = w;  // 缓存波动值之和
        }  // if 分支结束
        return {c, w};  // 返回本状态的数字个数与波动值之和
    }  // 方法结束
};  // 类定义结束
