// 题目：2087. 网格图中机器人回家的最小代价（Minimum Cost Homecoming of a Robot in a Grid）
// 思路：行方向的移动与列方向的移动互相独立，绕路只会多花钱，因此分别累加起点到终点之间经过的每一行、每一列的代价，两者相加即最小总代价。
// 时间复杂度：O(m + n)，m、n 为需要跨越的行数与列数（两次区间求和）；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCost(vector<int>& startPos, vector<int>& homePos, vector<int>& rowCosts, vector<int>& colCosts) {  // startPos/homePos 为起终点坐标，rowCosts/colCosts 为每一行、每一列的移动代价
        auto calc = [](vector<int>& nums, int i, int j) {  // 辅助 lambda：把 nums 中闭区间 [i, j] 的代价和求出来
            int res = 0;  // 区间累加结果
            for (int k = i; k <= j; ++k) {  // 遍历闭区间 [i, j] 中的每个下标 k
                res += nums[k];  // 把该行（或该列）的代价累加进来
            }  // 内层循环结束
            return res;  // 返回区间和
        };  // lambda 定义结束
        int x0 = startPos[0], y0 = startPos[1];  // 起点坐标：x0 为行号，y0 为列号
        int x1 = homePos[0], y1 = homePos[1];  // 终点坐标：x1 为行号，y1 为列号
        int dx = x0 < x1 ? calc(rowCosts, x0 + 1, x1) : calc(rowCosts, x1, x0 - 1);  // 行方向：向下走就累加 rowCosts[x0+1..x1]，向上走则累加 rowCosts[x1..x0-1]
        int dy = y0 < y1 ? calc(colCosts, y0 + 1, y1) : calc(colCosts, y1, y0 - 1);  // 列方向同理：向右累加 colCosts[y0+1..y1]，向左累加 colCosts[y1..y0-1]
        return dx + dy;  // 行代价与列代价相加即最小总代价
    }  // 结束 minCost 方法
};  // 结束 Solution 类
