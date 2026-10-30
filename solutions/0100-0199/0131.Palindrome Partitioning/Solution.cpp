// 题目：131. 分割回文串（Palindrome Partitioning）
// 思路：先用区间 DP 预处理 f[i][j] 表示 s[i..j] 是否回文，再用回溯枚举所有切分点，只沿着回文区间往下走。
// 时间复杂度：O(n * 2^n)，预处理 O(n^2)、最坏切分数是指数级；空间复杂度：O(n^2)，回文表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<string>> partition(string s) {  // 返回所有把 s 切成若干个回文子串的方案
        int n = s.size();  // n 是字符串长度
        bool f[n][n];  // 回文判定表：f[i][j] 为真表示 s[i..j] 是回文串
        memset(f, true, sizeof(f));  // 用 memset 把每个字节置成 1（非零即 true），先假设所有区间都是回文，单字符区间自然成立
        for (int i = n - 1; i >= 0; --i) {  // 起点 i 从后往前枚举，保证 i+1 这一行已经算好
            for (int j = i + 1; j < n; ++j) {  // 终点 j 从 i+1 开始，长度小于 2 的区间已经在初值里为真
                f[i][j] = s[i] == s[j] && f[i + 1][j - 1];  // 回文递推：首尾字符相等且去掉首尾后仍是回文
            }
        }
        vector<vector<string>> ans;  // 保存所有完整的切分方案
        vector<string> t;  // 回溯过程中当前这一种切分方案
        auto dfs = [&](this auto&& dfs, int i) -> void {  // C++23 的显式对象参数：让 lambda 能递归调用自己，i 是当前待切分的起始位置
            if (i == n) {  // 已经切到字符串末尾，说明当前方案完整
                ans.emplace_back(t);  // 把当前方案的一份拷贝放进答案
                return;  // 这条分支结束，回退
            }
            for (int j = i; j < n; ++j) {  // 枚举从 i 开始的下一个回文段的结束位置 j
                if (f[i][j]) {  // 只有 s[i..j] 是回文才值得继续切
                    t.emplace_back(s.substr(i, j - i + 1));  // 取出子串 s[i..j] 作为当前段，加入方案
                    dfs(j + 1);  // 从 j+1 继续切剩下的后缀
                    t.pop_back();  // 回溯：撤销刚才加入的段，尝试本轮的下一个 j
                }
            }
        };
        dfs(0);  // 从下标 0 开始搜索所有切法
        return ans;  // 返回收集到的全部方案
    }
};
