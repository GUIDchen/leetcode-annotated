// 题目：593. 有效的正方形（Valid Square）
// 思路：正方形四个点中任取三个，其中必有一个顶点与另外两点构成等腰直角三角形；只要四种三点组合都满足这个性质即为正方形。
// 时间复杂度：O(1)，只有四次常数级的三点检查；空间复杂度：O(1)，仅用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {  // p1~p4 是四个点的坐标
        return check(p1, p2, p3) && check(p1, p3, p4) && check(p1, p2, p4) && check(p2, p3, p4);  // 四种三点组合都必须能构成等腰直角三角形
    }

    bool check(vector<int>& a, vector<int>& b, vector<int>& c) {  // 判断 a、b、c 三点能否构成等腰直角三角形
        int x1 = a[0], y1 = a[1];  // 点 a 的横纵坐标
        int x2 = b[0], y2 = b[1];  // 点 b 的横纵坐标
        int x3 = c[0], y3 = c[1];  // 点 c 的横纵坐标
        int d1 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);  // a 到 b 的距离平方
        int d2 = (x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3);  // a 到 c 的距离平方
        int d3 = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3);  // b 到 c 的距离平方
        if (d1 == d2 && d1 + d2 == d3 && d1 > 0) return true;  // d1、d2 作直角边、d3 作斜边；d1 > 0 用来排除重合点
        if (d1 == d3 && d1 + d3 == d2 && d1 > 0) return true;  // 换一种配对：d1、d3 是直角边，d2 是斜边
        if (d2 == d3 && d2 + d3 == d1 && d2 > 0) return true;  // 再换一种配对：d2、d3 是直角边，d1 是斜边
        return false;  // 三种配对都不满足，说明不是等腰直角三角形
    }
};