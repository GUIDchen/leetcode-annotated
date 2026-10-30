// 题目：1001. 网格照明（Grid Illumination）
// 思路：不去模拟照亮每个格子，而是用哈希表分别统计每一行、每一列、主对角线(i-j)、副对角线(i+j)上的灯数；查询时四者任一大于 0 即被照亮，随后关掉 3×3 邻域内的灯并同步减计数。
// 时间复杂度：O(m + q)，m 为灯数、q 为查询数；空间复杂度：O(m)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> gridIllumination(int n, vector<vector<int>>& lamps, vector<vector<int>>& queries) {  // n：网格边长；lamps：灯的坐标；queries：查询坐标；返回每个查询位置是否被照亮
        auto f = [&](int i, int j) -> long long {  // 把二维坐标压成一个整数键，方便放进哈希表
            return (long long) i * n + j;  // key = i * n + j，乘 n 保证不同坐标不会算出同一个键
        };
        unordered_set<long long> s;  // 存放当前仍然亮着的灯的坐标键（顺便去重）
        unordered_map<int, int> row, col, diag1, diag2;  // 四个方向的灯数统计：行、列、主对角线(i-j)、副对角线(i+j)
        for (auto& lamp : lamps) {  // 逐盏处理输入中的所有灯
            int i = lamp[0], j = lamp[1];  // 取出一盏灯的坐标
            if (!s.count(f(i, j))) {  // 同一位置可能重复给出，只统计一次，避免计数虚高
                s.insert(f(i, j));  // 把这盏灯记入灯集合
                row[i]++;  // 该行的灯数加一
                col[j]++;  // 该列的灯数加一
                diag1[i - j]++;  // 主对角线（i-j 相同）灯数加一
                diag2[i + j]++;  // 副对角线（i+j 相同）灯数加一
            }
        }
        int m = queries.size();  // 查询的个数
        vector<int> ans(m);  // 答案数组，初始 0 表示该位置未被照亮
        for (int k = 0; k < m; ++k) {  // 依次处理每个查询
            int i = queries[k][0], j = queries[k][1];  // 当前查询的坐标
            if (row[i] > 0 || col[j] > 0 || diag1[i - j] > 0 || diag2[i + j] > 0) {  // 行、列、两条对角线上任一方向还有灯，该格子就被照亮
                ans[k] = 1;  // 标记这个查询的结果为 1
            }
            for (int x = i - 1; x <= i + 1; ++x) {  // 关灯范围：以 (i, j) 为中心的 3 行
                for (int y = j - 1; y <= j + 1; ++y) {  // 关灯范围：对应的 3 列
                    if (x < 0 || x >= n || y < 0 || y >= n || !s.count(f(x, y))) {  // 越界，或者该位置本来就没有灯，无需处理
                        continue;  // 跳到下一个格子
                    }
                    s.erase(f(x, y));  // 从灯集合中删除这盏灯
                    row[x]--;  // 所在行的灯数减一
                    col[y]--;  // 所在列的灯数减一
                    diag1[x - y]--;  // 所在主对角线的灯数减一
                    diag2[x + y]--;  // 所在副对角线的灯数减一
                }
            }
        }
        return ans;  // 返回全部查询的结果数组
    }
};