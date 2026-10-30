// 题目：97. 交错字符串（Interleaving String）
// 思路：记忆化搜索，dfs(i, j) 表示 s1 的前 i 个与 s2 的前 j 个字符能否交错拼出 s3 的前 i+j 个；
//       当前应匹配 s3[i+j]，可以取自 s1[i] 或 s2[j]，两条路都走不通才失败。
// 时间复杂度：O(m·n)，每个状态只求解一次；空间复杂度：O(m·n)，记忆化数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isInterleave(string s1, string s2, string s3) {  // 判断 s3 是否由 s1、s2 交错拼接而成
        int m = s1.size(), n = s2.size();  // 两个串的长度，决定状态空间大小
        if (m + n != s3.size()) {  // 长度都对不上，绝无可能交错拼成
            return false;  // 直接否决
        }
        vector<vector<int>> f(m + 1, vector<int>(n + 1, -1));  // 记忆化数组：-1 未计算，0 失败，1 成功
        function<bool(int, int)> dfs = [&](int i, int j) {  // i、j 分别是 s1、s2 已用掉的字符数
            if (i >= m && j >= n) {  // 两个串都用完，说明 s3 也恰好被拼完
                return true;  // 找到一条合法交错路径
            }
            if (f[i][j] != -1) {  // 该状态之前算过，直接复用结果
                return f[i][j] == 1;  // 把 0/1 还原成 bool
            }
            f[i][j] = 0;  // 先按失败处理，后面成功再覆盖，防止重复搜索
            int k = i + j;  // 当前要对齐的是 s3 的第 k 个字符
            if (i < m && s1[i] == s3[k] && dfs(i + 1, j)) {  // 方案一：让 s3[k] 取自 s1[i]，且后续也能拼成
                f[i][j] = 1;  // 这条分支成功，记下结果
            }
            if (!f[i][j] && j < n && s2[j] == s3[k] && dfs(i, j + 1)) {  // 方案二：上一条失败时，改让 s3[k] 取自 s2[j]
                f[i][j] = 1;  // 这条分支成功，记下结果
            }
            return f[i][j] == 1;  // 返回该状态最终能否拼成
        };
        return dfs(0, 0);  // 从两个串都没用任何字符开始搜索
    }
};
