// 3402. 使每一列严格递增的最少操作次数 / Minimum Operations to Make Columns Strictly Increasing
// 核心思路：逐列贪心，维护上一个元素的取值（列首之前视作 -1），当前值不大于它时就抬到「前值 + 1」，累加差值
// 复杂度：时间 O(m * n)，空间 O(1)
class Solution {  // 定义题目解答类
public:
    int minimumOperations(vector<vector<int>>& grid) {  // 方法入口：每列只能做减法，使其严格递增
        int m = grid.size(), n = grid[0].size();  // m 为行数，n 为列数
        int ans = 0;  // 累计操作次数
        for (int j = 0; j < n; ++j) {  // 逐列处理
            int pre = -1;  // 上一个元素的取值，列首之前视作 -1
            for (int i = 0; i < m; ++i) {  // 从上到下扫描该列
                int cur = grid[i][j];  // 当前元素
                if (pre < cur) {  // 已严格大于前一个值，无需操作
                    pre = cur;  // 直接更新前一个值
                } else {  // 否则必须把它减到「前一个值 + 1」
                    ++pre;  // 目标值加一
                    ans += pre - cur;  // 累加需要减掉的差值
                }
            }
        }
        return ans;  // 返回最小操作次数
    }
};
