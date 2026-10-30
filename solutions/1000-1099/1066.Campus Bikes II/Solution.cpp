// 题目：1066. 校园自行车分配 II（Campus Bikes II）
// 思路：状态压缩 DP，f[i][j] 表示前 i 个工人骑走自行车集合 j 的最小代价，枚举第 i 个工人骑的车 k 转移。
// 时间复杂度：O(n · 2^m · m)；空间复杂度：O(n · 2^m)，n 为工人数、m 为自行车数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {  // workers/bikes：各点坐标 [x, y]；返回所有工人都分到车的最小曼哈顿距离和
        int n = workers.size(), m = bikes.size();  // 工人数 n 与自行车数 m；题目保证 m >= n
        int f[n + 1][1 << m];  // f[i][j]：前 i 个工人使用自行车集合 j（位掩码）时的最小总距离
        memset(f, 0x3f, sizeof(f));  // 全部初始化为 0x3f3f3f3f，表示「不可达」，便于后面取 min
        f[0][0] = 0;  // 边界：0 个工人、车集合为空，代价为 0
        for (int i = 1; i <= n; ++i) {  // 逐个考虑第 i 个工人（从 1 开始编号，方便取前一行）
            for (int j = 0; j < 1 << m; ++j) {  // 枚举这 i 个工人用到的自行车集合 j（共 2^m 种）
                for (int k = 0; k < m; ++k) {  // 枚举第 i 个工人具体骑哪一辆车 k
                    if (j >> k & 1) {  // 车 k 必须属于集合 j，否则该转移不成立
                        int d = abs(workers[i - 1][0] - bikes[k][0]) + abs(workers[i - 1][1] - bikes[k][1]);  // 第 i-1 个工人到第 k 辆车的曼哈顿距离
                        f[i][j] = min(f[i][j], f[i - 1][j ^ (1 << k)] + d);  // 从「去掉车 k 的前 i-1 个工人状态」转移而来，取更小值
                    }  // end if
                }  // end for k：本集合下所有可能的最后一辆车都试过
            }  // end for j：所有集合枚举完毕
        }  // end for i：所有工人都安排完毕
        return *min_element(f[n], f[n] + (1 << m));  // n 个工人恰好占用 n 辆车，在所有集合里取最小值即全局最优（多出的车对应的状态仍不可达）
    }  // end method
};  // end class