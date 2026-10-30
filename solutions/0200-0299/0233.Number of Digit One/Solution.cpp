// 题目：233. 数字 1 的个数（Number of Digit One）
// 思路：数位 DP，从左往右逐位填数，状态为「当前第几位、已经累计了多少个 1、是否紧贴上界」，用 f[i][cnt] 记忆化不受上界限制的状态。
// 时间复杂度：O(m²·10)，m 为 n 的十进制位数；空间复杂度：O(m²)，即记忆化数组大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countDigitOne(int n) {  // n 是上界，返回 1..n 中数字 1 出现的总次数
        string s = to_string(n);  // 转成字符串，方便按位做数位 DP
        int m = s.size();  // 记录十进制位数
        int f[m][m];  // 记忆化数组：f[i][cnt] 表示处理到第 i 位、前面已累计 cnt 个 1 时的方案总数
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，表示对应状态还没被计算过
        auto dfs = [&](this auto&& dfs, int i, int cnt, bool limit) -> int {  // 递归 lambda（C++23 的 this auto 自引用）：从第 i 位往后还能贡献多少个 1
            if (i >= m) {  // 所有数位都填完了
                return cnt;  // 返回这一条路径上累计的 1 的个数
            }  // 递归终止分支结束
            if (!limit && f[i][cnt] != -1) {  // 只有不紧贴上界的状态才能复用记忆化结果
                return f[i][cnt];  // 命中缓存，直接返回已经算好的答案
            }  // 记忆化判断结束
            int up = limit ? s[i] - '0' : 9;  // 当前位能取的最大值：紧贴上界就是 s[i]，否则可以一路取到 9
            int ans = 0;  // 累计当前状态的方案数，初始为 0
            for (int j = 0; j <= up; ++j) {  // 枚举当前位所有合法取值
                ans += dfs(i + 1, cnt + (j == 1), limit && j == up);  // 往下一位递归：位数加一，若当前位填 1 则计数加一，只有顶上界时 limit 才继续为真
            }  // 枚举结束
            if (!limit) {  // 只有不受上界限制的状态才能写进记忆化表
                f[i][cnt] = ans;  // 记录这个状态的结果
            }  // 记忆化写入分支结束
            return ans;  // 返回当前状态的结果
        };  // 递归 lambda 定义结束
        return dfs(0, 0, true);  // 从最高位开始搜，初始 limit 为 true，表示紧贴 n 的上界
    }  // 方法结束
};  // 题解类结束
