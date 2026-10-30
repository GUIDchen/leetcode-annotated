// 题目：1620. 网络信号最好的坐标（Coordinate With Maximum Network Quality）
// 思路：坐标范围很小（0~50），直接枚举所有整数点，对每个点累加落在半径内的信号塔的质量 floor(q/(1+d))，取质量最大的点（相同则取字典序最小，靠严格小于更新天然满足）。
// 时间复杂度：O(51^2 * n)，n 为信号塔数量；空间复杂度：O(1)，只存当前最优坐标与最大值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {  // towers：每项是 [x, y, q]；radius：信号半径
        int mx = 0;  // 当前扫到的最大网络质量（初始为 0，因此每个点都比一次 0）
        vector<int> ans = {0, 0};  // 记录取得最大质量的坐标，默认原点
        for (int i = 0; i < 51; ++i) {  // 枚举横坐标 0~50
            for (int j = 0; j < 51; ++j) {  // 枚举纵坐标 0~50
                int t = 0;  // 当前这个候选点的网络质量总和
                for (auto& e : towers) {  // 遍历所有信号塔
                    double d = sqrt((i - e[0]) * (i - e[0]) + (j - e[1]) * (j - e[1]));  // 欧氏距离
                    if (d <= radius) {  // 落在信号覆盖范围内才贡献质量
                        t += floor(e[2] / (1 + d));  // 质量按 q/(1+d) 向下取整后累加
                    }
                }
                if (mx < t) {  // 严格小于才更新，保证并列时保留字典序更小的坐标
                    mx = t;  // 记录新的最大质量
                    ans = {i, j};  // 记录取得该质量的坐标
                }
            }
        }
        return ans;  // 返回网络信号最好的整数坐标
    }
};