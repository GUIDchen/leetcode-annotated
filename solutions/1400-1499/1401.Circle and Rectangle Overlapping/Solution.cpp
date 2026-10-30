// 题目：1401. 圆和矩形是否有重叠（Circle and Rectangle Overlapping）
// 思路：把圆心到矩形的最近点拆成 x、y 两轴独立计算：落在区间内距离为 0，否则取到最近端点的差；再比较平方和与半径平方。
// 时间复杂度：O(1)，只有常数次运算；空间复杂度：O(1)，只用几个临时变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {  // radius 半径，圆心 (xCenter, yCenter)，矩形对角 (x1, y1)-(x2, y2)
        auto f = [](int i, int j, int k) -> int {  // 无捕获 lambda：求一维坐标 k 到闭区间 [i, j] 的距离
            if (i <= k && k <= j) {  // k 落在区间内部
                return 0;  // 在区间内则最近距离为 0
            }  // 区间内判断结束
            return k < i ? i - k : k - j;  // 在左侧取 i - k，在右侧取 k - j
        };  // lambda 定义结束
        int a = f(x1, x2, xCenter);  // 圆心横坐标到矩形横向区间的距离
        int b = f(y1, y2, yCenter);  // 圆心纵坐标到矩形纵向区间的距离
        return a * a + b * b <= radius * radius;  // 最近点距离平方不超过半径平方即判定重叠（避免开方误差）
    }  // checkOverlap 方法结束
};  // Solution 类结束