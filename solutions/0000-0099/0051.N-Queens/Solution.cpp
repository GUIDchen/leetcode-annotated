// 题目：51. N 皇后（N-Queens）
// 思路：逐行深搜 + 回溯。用三个数组分别标记列、副对角线（i+j）、主对角线（n-i+j）是否被占用，每行放一个皇后，冲突就剪枝。
// 时间复杂度：O(n!)，回溯树的规模；空间复杂度：O(n)，递归栈与三个标记数组（不含存放答案的空间）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<string>> solveNQueens(int n) {  // n 为棋盘边长，返回所有合法的 N 皇后布局
        vector<int> col(n);  // col[j] 标记第 j 列是否已经放了皇后
        vector<int> dg(n << 1);  // dg[i + j] 标记副对角线（/ 方向）是否被占用，下标范围 0..2n-1
        vector<int> udg(n << 1);  // udg[n - i + j] 标记主对角线（\ 方向）是否被占用，加 n 偏移避免负数下标
        vector<vector<string>> ans;  // 收集所有合法棋盘
        vector<string> t(n, string(n, '.'));  // 当前棋盘，先全部填成 '.'
        function<void(int)> dfs = [&](int i) -> void {  // 深搜第 i 行；用 function 包一层以便递归调用自身
            if (i == n) {  // 前 n 行都放好了，得到一个合法解
                ans.push_back(t);  // 把当前棋盘整体存入答案
                return;  // 本分支结束，回溯到上一层
            }  // if 结束
            for (int j = 0; j < n; ++j) {  // 尝试把第 i 行的皇后放在第 j 列
                if (col[j] + dg[i + j] + udg[n - i + j] == 0) {  // 列、两条对角线都没被占用才可落子（三者和为 0 即都空闲）
                    t[i][j] = 'Q';  // 落子：在棋盘上标记皇后
                    col[j] = dg[i + j] = udg[n - i + j] = 1;  // 同时占用该列与两条对角线
                    dfs(i + 1);  // 递归处理下一行
                    col[j] = dg[i + j] = udg[n - i + j] = 0;  // 回溯：撤销该列与两条对角线的占用
                    t[i][j] = '.';  // 回溯：把皇后从棋盘上拿掉
                }  // if 结束
            }  // for 结束
        };  // lambda（dfs）定义结束
        dfs(0);  // 从第 0 行开始搜索
        return ans;  // 返回所有合法布局
    }  // solveNQueens 结束
};  // 类定义结束