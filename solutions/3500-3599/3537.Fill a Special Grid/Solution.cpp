// 3537. 填充特殊网格 / Fill a Special Grid
// 核心思路：把 2^n 网格递归四等分，按左上→左下→右下→右上的顺序填充，用全局自增计数器保证顺时针递增。
// 复杂度：时间 O(4^n)（等于格子数），空间 O(2^n)（递归深度）。
class Solution {  // 定义题解类
public:  // 公有方法区
    vector<vector<int>> specialGrid(int n) {  // 构造 2^n × 2^n 的特殊网格
        int m = 1 << n;  // 网格边长 m = 2^n
        vector<vector<int>> ans(m, vector<int>(m));  // m × m 的结果矩阵
        int val = 0;  // 依次填入的数值，从 0 开始

        auto dfs = [&](this auto&& dfs, int x, int y, int k) -> void {  // 递归填充左上角为 (x, y) 的 k × k 子块
            if (k == 1) {  // 递归到 1 × 1 的格子
                ans[x][y] = val++;  // 填入当前值并自增
                return;  // 递归结束
            }  // if 语句结束

            int h = k / 2;  // 每个小块边长为 k / 2
            dfs(x, y, h);  // 先填左上块
            dfs(x + h, y, h);  // 再填左下块
            dfs(x + h, y - h, h);  // 再填右下块
            dfs(x, y - h, h);  // 最后填右上块，形成顺时针递增
        };  // lambda 定义结束

        dfs(0, m - 1, m);  // 从左上角 (0, m-1) 开始填充整块
        return ans;  // 返回构造好的网格
    }  // 方法结束
};  // 类定义结束