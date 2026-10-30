// 题目：3135. 通过添加或删除结尾字符来同化字符串（Equalize Strings by Adding or Removing Characters at Ends）
// 思路：只能在串首/串尾增删字符，所以中间那段必须原样保留；求两串的最长公共子串长度 mx，其余字符全删全补，答案 m+n-2*mx。
// 时间复杂度：O(m*n)，两层 DP 填表；空间复杂度：O(m*n)，二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minOperations(string initial, string target) {  // initial：起始串；target：目标串；返回最少操作次数
        int m = initial.size(), n = target.size();  // 分别记录两个串的长度
        int f[m + 1][n + 1];  // f[i][j]：以 initial[i-1] 与 target[j-1] 结尾的最长公共子串长度
        memset(f, 0, sizeof(f));  // 整体清零：边界（空后缀）的最长公共子串长度为 0
        int mx = 0;  // mx 记录全局最长公共子串长度
        for (int i = 1; i <= m; ++i) {  // 枚举 initial 中以第 i 个字符结尾的位置
            for (int j = 1; j <= n; ++j) {  // 枚举 target 中以第 j 个字符结尾的位置
                if (initial[i - 1] == target[j - 1]) {  // 两个字符相同，公共子串才能继续延长
                    f[i][j] = f[i - 1][j - 1] + 1;  // 接在前一状态的公共子串后面，长度加一
                    mx = max(mx, f[i][j]);  // 用当前长度更新答案下界
                }  // 字符不同则 f[i][j] 保持 0：公共子串必须连续，不能跳过
            }  // 内层循环结束
        }  // 外层循环结束
        return m + n - 2 * mx;  // 保留这段公共子串，其余字符删掉或补齐，操作次数为 m+n-2*mx
    }  // 方法结束
};  // 类定义结束