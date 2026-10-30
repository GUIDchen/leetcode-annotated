// 题目：3699. 锯齿形数组的总数 I（Number of ZigZag Arrays I）
// 核心思路：动态规划，up[i] / down[i] 分别表示以数值 i 结尾、且最后一步为上升 / 下降的数组个数；每扩展一位时用 down 的前缀和、up 的后缀和把 O(m^2) 的转移整体降到 O(m)。
// 复杂度：时间 O(n * m)，共 n-1 轮、每轮线性扫描三次；空间 O(m)，只有 up / down 两张 DP 表。
int zigZagArrays(int n, int l, int r) {  // 返回长度 n、取值在 [l, r] 内的锯齿形数组总数
    int mod = 1e9 + 7;  // 结果对 1e9+7 取模
    int m = r - l + 1;  // 可选数字的个数，把区间 [l, r] 平移映射到 0..m-1
    long long up[m], down[m];  // up[i]：以 i 结尾且最后一步上升；down[i]：以 i 结尾且最后一步下降
    for (int i = 0; i < m; ++i) {  // 长度为 1 的数组本身都合法
        up[i] = down[i] = 1;  // 单个数字既算「上升态」也算「下降态」，各 1 种
    }  // 结束初始化
    for (int k = 1; k < n; ++k) {  // 每轮把数组长度从 k 扩展到 k+1
        long long pre[m + 1], suf[m + 1];  // pre 存 down 的前缀和，suf 存 up 的后缀和
        memset(pre, 0, sizeof(pre));  // pre[0] 必须为 0，先整体清零
        memset(suf, 0, sizeof(suf));  // suf[m] 必须为 0，先整体清零
        for (int i = 0; i < m; ++i) {  // 正序累计 down 的前缀和
            pre[i + 1] = (pre[i] + down[i]) % mod;  // pre[i+1] = down[0..i] 之和
        }  // 结束前缀和计算
        for (int i = m - 1; i >= 0; --i) {  // 逆序累计 up 的后缀和
            suf[i] = (suf[i + 1] + up[i]) % mod;  // suf[i] = up[i..m-1] 之和
        }  // 结束后缀和计算
        for (int i = 0; i < m; ++i) {  // 用前缀和 / 后缀和一次性刷新整张表
            up[i] = pre[i];  // 新的 up[i]：上一位取比 i 小的任意值且呈下降态结束
            down[i] = suf[i + 1];  // 新的 down[i]：上一位取比 i 大的任意值且呈上升态结束
        }  // 结束本轮转移
    }  // 结束长度扩展
    long long ans = 0;  // ans 汇总所有结尾状态的方案数
    for (int i = 0; i < m; ++i) {  // 枚举最终结尾取值
        ans = (ans + up[i] + down[i]) % mod;  // 累加上升态与下降态两类方案
    }  // 结束汇总
    return ans;  // 返回锯齿形数组总数
}  // 结束 zigZagArrays
