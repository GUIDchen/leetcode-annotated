// 题目：1312. 让字符串成为回文串的最少插入次数（Minimum Insertion Steps to Make a String Palindrome）
// 核心思路：区间 DP + 记忆化：dfs(i, j) 表示把 s[i..j] 变成回文的最少插入次数；
//           两端字符相同则收缩区间，否则在左右各插入一个字符，取两种方案中更小的并加一。
// 时间复杂度：O(n^2)，状态数为区间个数；空间复杂度：O(n^2)，记忆化表 f 以及递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minInsertions(string s) {  // s 是待变成回文的字符串
        int n = s.size();  // 字符串长度
        int f[n][n];  // 记忆化表：f[i][j] 存放区间 [i, j] 的最少插入次数（变长数组，GCC 扩展）
        memset(f, -1, sizeof(f));  // 初始化为 -1，表示该区间尚未计算过
        function<int(int, int)> dfs = [&](int i, int j) -> int {  // 递归 lambda：求区间 [i, j] 的最少插入次数
            if (i >= j) {  // 区间为空或只剩一个字符，本身已是回文
                return 0;  // 不需要任何插入
            }
            if (f[i][j] != -1) {  // 该区间已经算过
                return f[i][j];  // 直接返回缓存结果，避免重复计算
            }
            int ans = 1 << 30;  // 用一个足够大的数初始化答案（后续一定会被覆盖）
            if (s[i] == s[j]) {  // 两端字符相同，可以同时配对
                ans = dfs(i + 1, j - 1);  // 直接收缩两端，不增加插入次数
            } else {  // 两端不同，必须在某一侧补字符
                ans = min(dfs(i + 1, j), dfs(i, j - 1)) + 1;  // 取「只处理左端」或「只处理右端」中更优的，再加一次插入
            }
            return f[i][j] = ans;  // 写入记忆化表并返回
        };
        return dfs(0, n - 1);  // 从整个字符串区间开始求解
    }
};  // 类定义结束（文件末尾无换行，保持原样）