// 题目：1037. 有效的回旋镖（Valid Boomerang）
// 思路：用叉积判断三点是否共线，(y2-y1)*(x3-x2) 与 (y3-y2)*(x2-x1) 不相等即三点不共线，构成回旋镖。
// 时间复杂度：O(1)，只做常数次运算；空间复杂度：O(1)，只用几个临时变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isBoomerang(vector<vector<int>>& points) {  // points 是三个点的坐标，返回它们是否构成回旋镖
        int x1 = points[0][0], y1 = points[0][1];  // 第一个点的横纵坐标
        int x2 = points[1][0], y2 = points[1][1];  // 第二个点的横纵坐标
        int x3 = points[2][0], y3 = points[2][1];  // 第三个点的横纵坐标
        return (y2 - y1) * (x3 - x2) != (y3 - y2) * (x2 - x1);  // 两个斜率交叉相乘后比较，不相等说明三点不共线（避免浮点误差）
    }  // 方法结束
};  // 类结束