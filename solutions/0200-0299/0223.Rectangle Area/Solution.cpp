// 题目：223. 矩形面积（Rectangle Area）
// 思路：总面积 = A 面积 + B 面积 - 交集面积；交集宽 = min(右边界) - max(左边界)，高同理，负值截断为 0。
// 时间复杂度：O(1)，只做常数次算术运算；空间复杂度：O(1)，只用了几个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {  // 两个矩形都给出左下角 (x1, y1) 与右上角 (x2, y2)，返回覆盖的总面积
        int a = (ax2 - ax1) * (ay2 - ay1);  // A 的面积 = 宽 × 高
        int b = (bx2 - bx1) * (by2 - by1);  // B 的面积 = 宽 × 高
        int width = min(ax2, bx2) - max(ax1, bx1);  // 交集宽：两条右边界取小、两条左边界取大再相减，不相交时会得到负数
        int height = min(ay2, by2) - max(ay1, by1);  // 交集高：同理取 y 方向的公共部分
        return a + b - max(height, 0) * max(width, 0);  // 总面积 = A + B - 交集；max(..., 0) 把不相交时的负数截断成 0，避免多减
    }
};