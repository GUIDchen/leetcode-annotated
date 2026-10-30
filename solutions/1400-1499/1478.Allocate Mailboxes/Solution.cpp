// 题目：1478. 安排邮筒（Allocate Mailboxes）
// 思路：排序后区间 DP。g[i][j] 表示只用 1 个邮筒服务 houses[i..j] 的最小距离和（邮筒放在中位数处）；f[i][j] 表示前 i+1 个房子放 j 个邮筒的最小代价，枚举最后一个邮筒的覆盖起点 p 转移。
// 时间复杂度：O(n^2 * k)，区间预处理 O(n^2)；空间复杂度：O(n^2 + n*k)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDistance(vector<int>& houses, int k) {  // houses：房子坐标；k：邮筒个数
        int n = houses.size();  // 房子个数
        sort(houses.begin(), houses.end());  // 排序后距离才具有单调性，中位数位置才是最优
        int g[n][n];  // g[i][j]：用 1 个邮筒服务第 i..j 个房子的最小距离和
        memset(g, 0, sizeof(g));  // 先全部清零（g[i][i] 单个房子代价为 0）
        for (int i = n - 2; ~i; --i) {  // i 从后往前枚举区间左端；~i 即 i != -1
            for (int j = i + 1; j < n; ++j) {  // j 枚举区间右端，保证 i < j
                g[i][j] = g[i + 1][j - 1] + houses[j] - houses[i];  // 两端各剥一个房子，最外层房屋的距离贡献即 houses[j] - houses[i]
            }
        }
        int f[n][k + 1];  // f[i][j]：前 i+1 个房子安排 j 个邮筒的最小总距离
        memset(f, 0x3f, sizeof(f));  // 初始化为无穷大，表示这些状态不可达
        for (int i = 0; i < n; ++i) {  // 依次扩展已处理的房子数量
            f[i][1] = g[0][i];  // 只放 1 个邮筒时，全部房子都由它服务
            for (int j = 1; j <= k && j <= i + 1; ++j) {  // 枚举邮筒数量 j，不能超过房子数量 i+1
                for (int p = 0; p < i; ++p) {  // 枚举最后一个邮筒服务的起始房子 p+1，前 p+1 个房子用 j-1 个邮筒
                    f[i][j] = min(f[i][j], f[p][j - 1] + g[p + 1][i]);  // 前半段最优 + 最后一段单邮筒代价
                }
            }
        }
        return f[n - 1][k];  // 全部 n 个房子安排 k 个邮筒的最小总距离
    }
};