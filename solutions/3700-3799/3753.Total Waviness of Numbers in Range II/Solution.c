// 题目：3753. 范围内总波动值 II（Total Waviness of Numbers in Range II）
// 核心思路：区间和化为 calc(num2) - calc(num1 - 1)；用数位 DP 从高位逐位填数，状态记录位置、前两位数字、是否已开始填数、是否贴上界，同时返回「能形成的数字个数」与「这些数字的波动值总和」，新出现的峰谷贡献要乘以后缀方案数。
// 复杂度：时间 O(位数 × 11 × 11 × 2 × 10)，即 O(log x)；空间 O(位数 × 11 × 11 × 2 × 2)，记忆化表规模与上界位数成正比。
static int len, digits[20];  // len 为当前上界的位数，digits 按高位在前存放上界的各数位
static long long fCnt[20][11][11][2];  // fCnt 记忆化：该状态下能形成的数字个数
static long long fWav[20][11][11][2];  // fWav 记忆化：该状态下所有数字的波动值之和
static char vis[20][11][11][2];  // vis 标记该状态是否已经算过
static long long cnt, wav;  // cnt、wav 作为全局返回值：dfs 通过它们回传个数与波动值之和

static void dfs(int pos, int prev2, int prev1, int started, int limit) {  // 数位 DP：pos 为当前位，prev2/prev1 为前两位数字（10 表示尚未填），started 表示是否已开始填数，limit 表示是否贴上界
    if (pos == len) {  // 已经填完全部数位
        cnt = started;  // 已开始填数就是一个合法正整数，个数记 1；全是前导零（数字 0）则记 0
        wav = 0;  // 末位不再产生新的峰谷
        return;  // 递归出口返回
    }  // 出口分支结束
    if (!limit && vis[pos][prev2][prev1][started]) {  // 不受上界限制时状态可复用，命中缓存就直接回填
        cnt = fCnt[pos][prev2][prev1][started];  // 取出缓存的数字个数
        wav = fWav[pos][prev2][prev1][started];  // 取出缓存的波动值之和
        return;  // 直接返回
    }  // 缓存分支结束
    int up = limit ? digits[pos] : 9;  // 贴着上界时当前位最多取到 digits[pos]，否则可以取到 9
    long long c = 0, w = 0;  // c 统计数字个数，w 统计波动值之和
    for (int d = 0; d <= up; ++d) {  // 枚举当前位填入的数字 d
        int nlimit = limit && d == up;  // 只有前缀一直紧贴上界，限制才会继续传递
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
        dfs(pos + 1, np2, np1, ns, nlimit);  // 递归处理下一位，结果通过全局 cnt、wav 回传
        c += cnt;  // 累加子问题的数字个数
        w += wav + add * cnt;  // 累加子问题的波动值，并加上本层新增的峰谷贡献（要乘以方案数）
    }  // 当前位枚举结束
    if (!limit) {  // 只有不受上界限制的状态才通用，可以写入缓存
        vis[pos][prev2][prev1][started] = 1;  // 标记该状态已计算
        fCnt[pos][prev2][prev1][started] = c;  // 缓存数字个数
        fWav[pos][prev2][prev1][started] = w;  // 缓存波动值之和
    }  // if 分支结束
    cnt = c;  // 把本层统计到的数字个数写回全局，供调用者读取
    wav = w;  // 把本层统计到的波动值之和写回全局
}  // 函数结束

static long long calc(long long x) {  // 返回 [0, x] 内所有数字的波动值之和（x < 0 时为空区间）
    if (x < 0) {  // x 为负数说明区间为空
        return 0;  // 直接返回 0
    }  // if 分支结束
    len = 0;  // 重新设置上界的位数
    if (x == 0) {  // 单独处理 x == 0，此时十进制表示就是一位 0
        digits[len++] = 0;  // digits 中放一个 0
    } else {  // 一般情况：先取低位再反转成高位在前
        int buf[20];  // buf 暂存低位在前的各数位
        int l = 0;  // l 是已取出的位数
        while (x) {  // 反复取最低位
            buf[l++] = x % 10;  // 取最低位存入 buf，位数加一
            x /= 10;  // x 去掉最低位
        }  // 循环结束
        for (int i = l - 1; i >= 0; --i) {  // 从高位到低位倒序写回 digits
            digits[len++] = buf[i];  // 写入数位，len 同步递增
        }  // 反转结束
    }  // else 分支结束
    memset(vis, 0, sizeof(vis));  // 清空记忆化标记，本次上界下的缓存从头开始
    dfs(0, 10, 10, 0, 1);  // 从最高位开始：前两位未填、未开始填数、贴着上界
    return wav;  // dfs 通过全局 wav 回传 [0, x] 的波动值之和
}  // 函数结束

long long totalWaviness(long long num1, long long num2) {  // 返回闭区间 [num1, num2] 内所有数字的波动值之和
    return calc(num2) - calc(num1 - 1);  // 用前缀和之差把区间查询化为两个前缀查询
}  // 函数结束
