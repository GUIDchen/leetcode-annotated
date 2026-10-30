// 题目：836. 矩形重叠（Rectangle Overlap）
// 思路：两个轴对齐矩形相交，当且仅当它们在 x 方向和 y 方向上的投影都真正重叠；把四个「分离」条件整体取反即可。
// 时间复杂度：O(1)，只做常数次比较；空间复杂度：O(1)，只用到几个临时变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {  // rec1、rec2 都按 [x1,y1,x2,y2] 给出矩形的左下角与右上角
        int x1 = rec1[0], y1 = rec1[1], x2 = rec1[2], y2 = rec1[3];  // 拆出第一个矩形的四个坐标
        int x3 = rec2[0], y3 = rec2[1], x4 = rec2[2], y4 = rec2[3];  // 拆出第二个矩形的四个坐标
        return !(y3 >= y2 || y4 <= y1 || x3 >= x2 || x4 <= x1);  // 任一方向分离即不重叠，四个分离条件整体取反后就是「相交」
    }  // 方法结束
};