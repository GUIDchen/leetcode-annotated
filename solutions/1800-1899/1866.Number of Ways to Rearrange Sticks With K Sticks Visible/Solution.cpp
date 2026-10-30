// 题目：1866. 恰有 K 根木棍可以看到的排列数目（Number of Ways to Rearrange Sticks With K Sticks Visible）
// 思路：按「最长木棍放在哪里」做递推：放最后则前面要看到 k-1 根，放其余 n-1 个位置则会被挡住、前面需看到 k 根，于是 f[i][j] = f[i-1][j-1] + (i-1)·f[i-1][j]（第一类斯特林数）。
// 时间复杂度：O(nk)，二维状态逐个转移；空间复杂度：O(nk)，存放 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int rearrangeSticks(int n, int k) {  // n：木棍总数；k：需要恰好能被看到的根数
        const int mod = 1e9 + 7;  // 结果要对 1e9+7 取模
        int f[n + 1][k + 1];  // f[i][j]：用 i 根木棍得到恰好 j 根可见的排列数（变长数组，尺寸由入参决定）
        memset(f, 0, sizeof(f));  // 整体清零，作为 DP 的初始状态
        f[0][0] = 1;  // 边界：0 根木棍看到 0 根，只有 1 种（空）排列
        for (int i = 1; i <= n; ++i) {  // 按木棍根数从小到大递推
            for (int j = 1; j <= k; ++j) {  // 按可见根数从小到大递推
                f[i][j] = (f[i - 1][j - 1] + (i - 1LL) * f[i - 1][j]) % mod;  // 递推：最长木棍放最后贡献 f[i-1][j-1]，插在其它 i-1 个位置贡献 (i-1)·f[i-1][j]，再取模
            }  // 可见根数这一维结束
        }  // 木棍根数这一维结束
        return f[n][k];  // 返回 n 根木棍恰好看到 k 根的方案数
    }  // 方法结束
};  // 类定义结束