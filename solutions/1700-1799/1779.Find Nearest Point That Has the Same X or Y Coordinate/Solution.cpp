// 题目：1779. 找到最近的有相同 X 或 Y 坐标的点（Find Nearest Point That Has the Same X or Y Coordinate）
// 思路：一次遍历所有点，只考察与给定点同 x 或同 y 的点，用曼哈顿距离维护最小值，并保留最早出现的下标。
// 时间复杂度：O(n)，n 为点的个数；空间复杂度：O(1)，只用到常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int nearestValidPoint(int x, int y, vector<vector<int>>& points) {  // x、y 是给定坐标，points 是点集
        int ans = -1, mi = 1e6;  // ans 记录答案下标（-1 表示暂无有效点），mi 记录当前最小距离（题目坐标上界很小，1e6 可当无穷大）
        for (int i = 0; i < points.size(); ++i) {  // 按下标从小到大遍历，距离相同时自然保留更小的下标
            int a = points[i][0], b = points[i][1];  // 取出第 i 个点的横纵坐标
            if (a == x || b == y) {  // 只要有一个坐标相同，就是有效点
                int d = abs(a - x) + abs(b - y);  // 计算该有效点的曼哈顿距离
                if (d < mi) {  // 只有严格更小才更新
                    mi = d;  // 更新最小距离
                    ans = i;  // 更新答案下标
                }
            }
        }
        return ans;  // 返回最近有效点的下标；没有有效点时就是 -1
    }
};