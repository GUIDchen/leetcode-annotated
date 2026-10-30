// 题目：254. 因子的组合（Factor Combinations）
// 思路：回溯。dfs(n, i) 表示剩余待分解的数 n 与下一个因子的下界 i；先把「当前路径 + n」记为一个解，再从 i 到 sqrt(n) 枚举因子 j 继续分解 n/j。
// 时间复杂度：与解的个数和每个解的长度成正比（近似 O(n log n)）；空间复杂度：O(log n)，递归深度等于因子个数。

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> getFactors(int n) {  // n：待分解的正整数（题目保证 n > 1）
        vector<int> t;  // 回溯路径：已经选定的因子，按非递减顺序保存
        vector<vector<int>> ans;  // 结果集：保存所有合法的因子组合
        function<void(int, int)> dfs = [&](int n, int i) {  // 内层递归函数：n 是剩余待分解的数，i 是下一个因子的下界
            if (t.size()) {  // 路径非空时，剩余的数 n 本身可以直接作为最后一个因子收尾
                vector<int> cp = t;  // 复制一份当前路径，避免修改回溯用的 t
                cp.emplace_back(n);  // 把剩余的 n 追加为组合的最后一个因子
                ans.emplace_back(cp);  // 得到一个完整的因子组合，加入结果集
            }
            for (int j = i; j <= n / j; ++j) {  // 枚举下一个因子 j：从下界 i 开始，只需到 sqrt(n)（写成 n/j 可避免乘法溢出）
                if (n % j == 0) {  // j 能整除剩余的数 n，才是合法因子
                    t.emplace_back(j);  // 选中因子 j，压入回溯路径
                    dfs(n / j, j);  // 继续分解 n/j，下界设为 j，保证因子非递减从而不重复
                    t.pop_back();  // 回溯：撤销刚选的 j，尝试下一个因子
                }
            }
        };  // 结束内层递归 lambda 的定义
        dfs(n, 2);  // 从 n 开始分解，因子最小取 2
        return ans;  // 返回所有因子组合
    }  // 结束方法
};  // 结束类