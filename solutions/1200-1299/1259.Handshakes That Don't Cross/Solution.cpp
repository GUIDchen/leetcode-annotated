// 题目：1259. 不相交的握手（Handshakes That Don't Cross）
// 思路：区间计数 DP——固定第一个人与位置 l+2 的人握手，环被切成两段互不影响的子问题，f[i] = Σ f[l]·f[i-l-2]（l 取偶数）。
// 时间复杂度：O(n²)，外层 n 个状态、内层枚举握手位置；空间复杂度：O(n)，记忆化数组 f 与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfWays(int numPeople) {  // numPeople 是围成一圈的人数（题目保证为偶数），返回不相交的配对方案数
        const int mod = 1e9 + 7;  // 取模常数，防止方案数按 1e9+7 取模后溢出
        int f[numPeople + 1];  // 记忆化数组：f[i] 表示 i 个人时的握手方案数（题目 n ≤ 1000，VLA 随参数确定大小）
        memset(f, 0, sizeof(f));  // 全部清零，0 同时表示「该状态还没算过」
        function<int(int)> dfs = [&](int i) {  // 递归 lambda：dfs(i) 求 i 个人（首尾相邻）时的方案数，[&] 按引用捕获 f 与 mod
            if (i < 2) {  // 不足 2 个人时已无可握手的对象，只有「什么都不做」这一种方案
                return 1;  // 返回唯一的空方案，作为递推的边界
            }  // 结束边界判断
            if (f[i]) {  // 非 0 说明此前算过，直接复用结果（记忆化剪枝）
                return f[i];  // 返回缓存值，避免重复展开子问题
            }  // 结束记忆化判断
            for (int l = 0; l < i; l += 2) {  // 枚举第一个人左边隔着的人数 l；每跨过一对握手者要占 2 个位置，所以步长为 2
                int r = i - l - 2;  // 右边剩下的人数：总数减去左边 l 人和正在握手的这 2 人
                f[i] = (f[i] + 1LL * dfs(l) * dfs(r) % mod) % mod;  // 两段子问题相互独立，方案数相乘；1LL 先升为 long long 再相乘，避免 int 溢出，最后统一取模
            }  // 结束内层枚举
            return f[i];  // 把本轮累加的结果写入 f[i]，供上层与后续查询复用
        };  // 结束递归 lambda 的定义
        return dfs(numPeople);  // 从总人数出发求解，答案即 f[numPeople]
    }  // 结束 numberOfWays
};  // 结束题解类