// 题目：498. 对角线遍历（Diagonal Traverse）
// 思路：把矩阵按 i+j 相同的对角线分组，编号 k 从 0 到 m+n-1；每条对角线先按普通顺序收集，k 为偶数时整体反转，从而形成 Z 字形输出。
// 时间复杂度：O(m*n)，每个元素恰好被访问一次；空间复杂度：O(min(m,n))，临时容器只存一条对角线。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {  // mat 是 m 行 n 列的矩阵
        int m = mat.size();  // 行数 m
        int n = mat[0].size();  // 列数 n
        vector<int> ans;  // 最终答案序列
        vector<int> t;  // 临时容器：暂存当前对角线上的元素
        for (int k = 0; k < m + n - 1; ++k) {  // 一共有 m+n-1 条对角线，k 是它们的编号
            int i = (k < n) ? 0 : k - n + 1;  // 起点的行号：前 n 条从第一行开始，之后沿最后一行右移
            int j = (k < n) ? k : n - 1;  // 起点的列号：前 n 条是 k，之后固定在最后一列
            while (i < m && j >= 0) {  // 沿右上方向一直走到越界，从而收集整条对角线
                t.push_back(mat[i][j]);  // 记录当前元素
                ++i;  // 行号下移
                --j;  // 列号左移
            }  // 这条对角线收集完毕
            if (k % 2 == 0) {  // 偶数编号的对角线方向相反，需要反转
                ranges::reverse(t);  // ranges::reverse 直接在原容器上翻转
            }  // 分支结束
            ans.insert(ans.end(), t.begin(), t.end());  // 把这条对角线追加到答案末尾
            t.clear();  // 清空临时容器，复用给下一条对角线
        }  // 所有对角线处理完毕
        return ans;  // 返回 Z 字形遍历结果
    }  // 方法体结束
};  // 类定义结束
