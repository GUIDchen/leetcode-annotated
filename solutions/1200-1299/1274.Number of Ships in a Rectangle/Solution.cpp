// 题目：1274. 矩形内船只的数目（Number of Ships in a Rectangle）
// 思路：在矩形上分治，先用 hasShips 判断当前矩形有没有船；有船且已缩成单点就计 1，否则四等分后递归求和。
// 时间复杂度：O(log(maxX·maxY)) 量级的 hasShips 调用；空间复杂度：O(log(maxX·maxY))，递归栈深度。
/**
 * // This is Sea's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Sea {
 *   public:
 *     bool hasShips(vector<int> topRight, vector<int> bottomLeft);
 * };
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countShips(Sea sea, vector<int> topRight, vector<int> bottomLeft) {  // sea：只提供 hasShips 的接口；topRight / bottomLeft：当前矩形的右上、左下角
        int x1 = bottomLeft[0], y1 = bottomLeft[1];  // 取出矩形的左边界 x1 与下边界 y1
        int x2 = topRight[0], y2 = topRight[1];  // 取出矩形的右边界 x2 与上边界 y2
        if (x1 > x2 || y1 > y2) {  // 矩形范围非法（左下角跑到了右上角外面）
            return 0;  // 非法矩形里不可能有船
        }  // 结束 if 块
        if (!sea.hasShips(topRight, bottomLeft)) {  // 先问接口整个矩形内有没有船，没有就剪枝
            return 0;  // 空矩形直接剪掉，不再细分
        }  // 结束 if 块
        if (x1 == x2 && y1 == y2) {  // 矩形缩成一个点，且已确认有船
            return 1;  // 这个点就是一艘船
        }  // 结束 if 块
        int midx = (x1 + x2) >> 1;  // x 方向取中点，右移一位等价于除以 2
        int midy = (y1 + y2) >> 1;  // y 方向取中点
        int a = countShips(sea, topRight, {midx + 1, midy + 1});  // 右上象限递归：x 在 midx+1..x2，y 在 midy+1..y2
        int b = countShips(sea, {midx, y2}, {x1, midy + 1});  // 左上象限递归：x 在 x1..midx，y 在 midy+1..y2
        int c = countShips(sea, {midx, midy}, bottomLeft);  // 左下象限递归：x 在 x1..midx，y 在 y1..midy
        int d = countShips(sea, {x2, midy}, {midx + 1, y1});  // 右下象限递归：x 在 midx+1..x2，y 在 y1..midy
        return a + b + c + d;  // 四块互不重叠，船只总数就是四块之和
    }  // countShips 方法结束
};  // Solution 类定义结束