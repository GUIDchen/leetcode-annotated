// 题目：533. 孤独像素 II（Lonely Pixel II）
// 思路：按列聚合黑色像素所在的行号，再逐列校验：该行黑数等于 target、该列黑数等于该行黑数、且这些行完全相同。
// 时间复杂度：O(m*n)，预处理扫一遍矩阵，校验时每列再比较若干行；空间复杂度：O(m*n)，存放每列的黑像素行号。
class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    int findBlackPixel(vector<vector<char>>& picture, int target) {  // picture 是 'B'/'W' 矩阵，target 是要求的黑像素数
        int m = picture.size();  // 行数
        int n = picture[0].size();  // 列数
        vector<int> g[n];  // g[j] 记录第 j 列里所有黑像素所在的行号（变长数组，每列行数不定）
        vector<int> rows(m);  // rows[i] 记录第 i 行的黑像素个数
        for (int i = 0; i < m; ++i) {  // 逐行扫描
            for (int j = 0; j < n; ++j) {  // 逐列扫描
                if (picture[i][j] == 'B') {  // 遇到黑像素
                    ++rows[i];  // 该行黑像素数加一
                    g[j].push_back(i);  // 把行号塞进这一列的行号列表
                }
            }
        }

        int ans = 0;  // 满足条件的黑像素总数
        for (int j = 0; j < n; ++j) {  // 逐列校验
            if (g[j].empty() || (rows[g[j][0]] != target)) {  // 空列，或该列任意黑像素所在行的黑数不是 target，整列作废
                continue;  // 跳过这一列
            }
            int i1 = g[j][0];  // 取这一列第一个黑像素所在行，作为「模板行」
            int ok = 0;  // 候选贡献值，校验通过时置为 target，否则保持 0
            if (g[j].size() == rows[i1]) {  // 该列黑像素数恰好等于该行的黑像素数
                ok = target;  // 先按 target 记账，下面若发现行不同再清零
                for (int i2 : g[j]) {  // 遍历该列所有黑像素所在的行
                    if (picture[i1] != picture[i2]) {  // 只要有一行和模板行不完全相同
                        ok = 0;  // 该列不合法
                        break;  // 提前结束校验
                    }
                }
            }
            ans += ok;  // 合法时这一列的 target 个黑像素全部满足条件，累加进答案
        }
        return ans;  // 返回满足条件的黑像素总数
    }
};