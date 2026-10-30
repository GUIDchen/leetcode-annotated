// 3963. 构造恰好一条路径的网格 / Create Grid With Exactly One Path
// 核心思路：构造一条“先沿第一行向右走到最右列，再沿最右列向下走到最后一行”的 L 形通道，其余格子全部填墙，
//          这样从左上角到右下角只有唯一一条路径。
// 复杂度：时间 O(m * n)（填充并修改网格），空间 O(m * n)（返回的网格本身）。

class Solution {
public:
    vector<string> createGrid(int m, int n) {  // 构造 m 行 n 列、恰好只有一条路径的网格
        vector<string> g(m, string(n, '#'));  // 初始化 m 行 n 列，全部为墙 '#'

        g[0] = string(n, '.');  // 把第一行整行打通为通道 '.'

        for (int i = 0; i < m; i++) {  // 逐行打通最右一列
            g[i][n - 1] = '.';  // 最右列设为通道 '.'，与第一行连成唯一通路
        }

        return g;  // 返回构造好的网格
    }
};