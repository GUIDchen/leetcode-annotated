// 题目：1947. 最大兼容性评分和（Maximum Compatibility Score Sum）
// 思路：先预处理学生 i 与导师 j 的兼容分 g[i][j]，再用回溯枚举所有「学生 → 导师」的一一配对，取最大总分。
// 时间复杂度：O(m!·m + m²n)，回溯最多枚举 m! 种配对；空间复杂度：O(m²)，兼容分矩阵与访问数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {  // students：学生答题向量；mentors：导师答题向量
        int m = students.size();  // 学生人数，题目保证与导师人数相同
        int n = students[0].size();  // 每个人答题的位数
        vector<vector<int>> g(m, vector<int>(m));  // g[i][j]：学生 i 与导师 j 的兼容分
        vector<bool> vis(m);  // vis[j] 表示导师 j 是否已经被分配
        for (int i = 0; i < m; ++i) {  // 枚举学生
            for (int j = 0; j < m; ++j) {  // 枚举导师
                for (int k = 0; k < n; ++k) {  // 逐位比较两人的答案
                    g[i][j] += students[i][k] == mentors[j][k];  // 相同则布尔值转成 1 累加
                }
            }
        }
        int ans = 0;  // 记录最大兼容性评分和
        auto dfs = [&](this auto&& dfs, int i, int s) {  // 回溯：给第 i 个学生配导师，s 是已累计得分
            if (i >= m) {  // 所有学生都配完了
                ans = max(ans, s);  // 用当前总分更新最优解
                return;  // 递归出口
            }
            for (int j = 0; j < m; ++j) {  // 尝试把导师 j 分给第 i 个学生
                if (!vis[j]) {  // 导师 j 还没被占用
                    vis[j] = true;  // 占用导师 j
                    dfs(i + 1, s + g[i][j]);  // 递归下一个学生，并累加这一对的兼容分
                    vis[j] = false;  // 回溯，释放导师 j，恢复现场
                }
            }
        };
        dfs(0, 0);  // 从第 0 个学生、0 分开始回溯
        return ans;  // 返回最大兼容性评分和
    }
};
