// 题目：1779. 找到最近的有相同 X 或 Y 坐标的点（Find Nearest Point That Has the Same X or Y Coordinate）
// 思路：一次遍历所有点，跳过 x、y 都不相同的点；对有效点用曼哈顿距离维护最小值，并记录最早出现的下标。
// 时间复杂度：O(n)，n 为点的个数；空间复杂度：O(1)，只用到常数个变量。
int nearestValidPoint(int x, int y, int** points, int pointsSize, int* pointsColSize) {  // x、y 是给定坐标，points 是点集，pointsSize 是点数，pointsColSize 是每行列数（本题恒为 2）
    int ans = -1;  // 答案下标，初始 -1 表示还没有找到有效点
    int min = INT_MAX;  // 当前最小曼哈顿距离，初始为无穷大
    for (int i = 0; i < pointsSize; i++) {  // 按下标从小到大遍历，保证距离相同时返回最小下标
        int* point = points[i];  // 取出第 i 个点（一个二元数组）
        if (point[0] != x && point[1] != y) {  // x、y 都不相等，说明不是有效点
            continue;  // 直接跳过该点
        }
        int d = abs(x - point[0]) + abs(y - point[1]);  // 有效点：计算与给定点的曼哈顿距离
        if (d < min) {  // 只有严格更小才更新，相等时保留更小的下标
            min = d;  // 更新最小距离
            ans = i;  // 更新答案下标
        }
    }
    return ans;  // 返回最近有效点的下标；没有有效点时仍为 -1
}