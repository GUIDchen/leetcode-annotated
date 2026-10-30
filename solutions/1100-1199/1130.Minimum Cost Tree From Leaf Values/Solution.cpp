// 题目：1130. 叶值的最小代价生成树（Minimum Cost Tree From Leaf Values）
// 思路：区间 DP / 记忆化搜索：区间 [i, j] 的叶子最终合并成一棵子树，枚举最后一次合并的分割点 k，代价为左右子树代价之和加上两侧最大叶值的乘积；预先用 g[i][j] 记录区间最大叶值，以便 O(1) 取得乘积因子。
// 时间复杂度：O(n^2) 个区间状态、每个状态枚举 O(n) 个分割点，共 O(n^3)；空间复杂度 O(n^2)，用于存 f 与 g 两张表。
class Solution {  // LeetCode 约定的题解类
public:  // 接口对外可见
    int mctFromLeafValues(vector<int>& arr) {  // arr：叶子节点值；返回构造树的最小代价和
        int n = arr.size();  // n：叶子个数
        int f[n][n];  // f[i][j]：区间 [i, j] 合并成一棵子树的最小代价，同时用作记忆化
        int g[n][n];  // g[i][j]：区间 [i, j] 内的最大叶值，作为合并时的乘积因子
        memset(f, 0, sizeof(f));  // f 清零，0 表示该区间尚未计算
        for (int i = n - 1; ~i; --i) {  // 从右往左枚举左端点，保证用到 g[i][j-1] 时它已有值
            g[i][i] = arr[i];  // 单元素区间的最大值就是该元素本身
            for (int j = i + 1; j < n; ++j) {  // 向右扩展右端点
                g[i][j] = max(g[i][j - 1], arr[j]);  // 区间最大值 = 左边少一列的最大值与 arr[j] 的较大者
            }  // 内层循环结束
        }  // 外层循环结束
        function<int(int, int)> dfs = [&](int i, int j) -> int {  // 记忆化搜索：返回把区间 [i, j] 的叶子合并成一棵树的最小代价
            if (i == j) {  // 只剩一个叶子时无需合并，代价为 0
                return 0;  // 直接返回 0
            }  // if 分支结束
            if (f[i][j] > 0) {  // 已经计算过就直接复用，避免重复搜索
                return f[i][j];  // 返回记忆化保存的结果
            }  // if 分支结束
            int ans = 1 << 30;  // ans 先取足够大的数，便于后面取最小值
            for (int k = i; k < j; ++k) {  // 枚举最后一次合并的分割点 k，左子树 [i, k]、右子树 [k+1, j]
                ans = min(ans, dfs(i, k) + dfs(k + 1, j) + g[i][k] * g[k + 1][j]);  // 代价 = 左右子树代价之和 + 本次合并的乘积（两侧最大叶值相乘）
            }  // 分割点循环结束
            return f[i][j] = ans;  // 记忆化并返回该区间的最小代价
        };  // lambda 定义结束
        return dfs(0, n - 1);  // 从整个区间开始计算，返回最小总代价
    }  // 方法结束
};  // 类定义结束