// 题目：664. 奇怪的打印机（Strange Printer）
// 思路：区间 DP。f[i][j] 表示打印出 s[i..j] 的最少次数；两端字符相同就能省一次，否则枚举分割点把两个子区间次数相加。
// 时间复杂度：O(n^3)，三层枚举区间端点与分割点；空间复杂度：O(n^2)，二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 公有接口
    int strangePrinter(string s) {  // s 是目标字符串，返回打印出它所需的最少次数
        int n = s.size();  // 字符串长度
        int f[n][n];  // f[i][j]：打印出 s[i..j] 这一段的最少次数
        memset(f, 0x3f, sizeof(f));  // 初值全部填成很大的数（0x3f 逐字节填充即 0x3f3f3f3f），方便后面取 min
        for (int i = n - 1; ~i; --i) {  // 左端点从右往左枚举，保证长度更短的子区间先算完
            f[i][i] = 1;  // 只有一个字符，一次就够
            for (int j = i + 1; j < n; ++j) {  // 右端点从小到大枚举
                if (s[i] == s[j]) {  // 首尾字符相同：打印 s[i..j-1] 时最右字符可以一并带出
                    f[i][j] = f[i][j - 1];  // 所以次数与 s[i..j-1] 相同，不必额外多打一次
                } else {  // 首尾不同，只能拆成两段分别打印
                    for (int k = i; k < j; ++k) {  // 枚举分割点 k，把区间拆成 [i..k] 与 [k+1..j]
                        f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);  // 取所有拆法里的最小值
                    }
                }
            }
        }
        return f[0][n - 1];  // 整个字符串 s[0..n-1] 的答案
    }  // 结束 strangePrinter
};