// 题目：568. 最大休假天数（Maximum Vacation Days）
// 思路：按周做 DP，f[k][j] 表示第 k 周结束待在城市 j 的最大休假天数；转移来自上周同城（不飞）或任何能直飞 j 的城市，再加上本周在该城的休假天数。
// 时间复杂度：O(K·n²)，每周每城枚举来源城市；空间复杂度：O(K·n)，需要整张 DP 表（C 版为变长数组）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {  // flights 是城市间直飞矩阵，days 是每城每周的休假天数
        int n = flights.size();  // n 是城市数量
        int K = days[0].size();  // K 是假期的总周数
        int f[K + 1][n];  // f[k][j]：第 k 周结束待在城市 j 的最大休假天数（k 从 0 开始）
        memset(f, -0x3f, sizeof(f));  // memset 按字节置为 0x3f 的负值，等价于把 int 全部初始化为很小的负数（负无穷）
        f[0][0] = 0;  // 第 0 周开始前只能待在城市 0，休假天数为 0
        for (int k = 1; k <= K; ++k) {  // 逐周推进，k 表示第 k 周
            for (int j = 0; j < n; ++j) {  // 枚举本周所在的城市 j
                f[k][j] = f[k - 1][j];  // 先假设不飞：上周也在 j 城
                for (int i = 0; i < n; ++i) {  // 枚举上周所在城市 i，看能否直飞到 j
                    if (flights[i][j] == 1) {  // flights[i][j] == 1 表示 i 可以直飞 j（含原地不动）
                        f[k][j] = max(f[k][j], f[k - 1][i]);  // 能飞则用上周 i 城的最优值更新本周 j 城
                    }  // 来源城市枚举结束
                }  // 城市 j 本周的转移结束
                f[k][j] += days[j][k - 1];  // 加上本周在城市 j 的休假天数（days 的第 k-1 列）
            }  // 本周枚举结束
        }  // 所有周推进结束
        int ans = 0;  // ans 记录最终的最大休假天数
        for (int j = 0; j < n; ++j) {  // 枚举最后一周可能停留的城市
            ans = max(ans, f[K][j]);  // 取所有城市中的最大值
        }  // 枚举结束
        return ans;  // 返回最大休假天数
    }
};