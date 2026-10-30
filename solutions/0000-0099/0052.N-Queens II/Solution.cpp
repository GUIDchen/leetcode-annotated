// 题目：52. N 皇后 II（N-Queens II）
// 思路：逐行深搜 + 回溯，只统计方案数而不存棋盘。用 bitset 标记列、副对角线（i+j）、主对角线（i-j+n）的占用情况。
// 时间复杂度：O(n!)，回溯树的规模；空间复杂度：O(1)，bitset 与递归栈的开销都是常数级。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int totalNQueens(int n) {  // n 为棋盘边长，返回合法布局的个数
        bitset<10> cols;  // 列占用标记；n ≤ 9，10 位足够
        bitset<20> dg;  // 副对角线（i + j）占用标记，最多 2n-1 ≤ 17 条
        bitset<20> udg;  // 主对角线（i - j + n）占用标记，加 n 偏移避免负数下标
        int ans = 0;  // 合法布局计数器
        function<void(int)> dfs = [&](int i) {  // 深搜第 i 行；用 function 包装以支持在 lambda 内部递归自调用
            if (i == n) {  // 所有行都放完了，说明找到一个合法布局
                ++ans;  // 方案数加一
                return;  // 回到上一层继续尝试
            }  // if 结束
            for (int j = 0; j < n; ++j) {  // 枚举第 i 行皇后所在的列 j
                int a = i + j, b = i - j + n;  // a 为副对角线编号，b 为加偏移后的主对角线编号
                if (cols[j] || dg[a] || udg[b]) continue;  // 任一方向已被占用，则这个位置不能放，直接试下一列
                cols[j] = dg[a] = udg[b] = 1;  // 占用当前列与两条对角线
                dfs(i + 1);  // 递归处理下一行
                cols[j] = dg[a] = udg[b] = 0;  // 回溯：释放列与两条对角线的占用
            }  // for 结束
        };  // lambda（dfs）定义结束
        dfs(0);  // 从第 0 行开始搜索
        return ans;  // 返回方案总数
    }  // totalNQueens 结束
};  // 类定义结束