// 3394. 判断网格图能否被切割成块 / Check if Grid can be Cut into Sections
// 核心思路：把每个矩形拆成起始边与结束边两个事件点，按坐标排序后做扫描线，统计覆盖数归零的次数，某个方向上能出现 3 次说明可以切出 3 块
// 复杂度：时间 O(n log n)（排序主导）、空间 O(n)
class Solution {  // 定义 Solution 类
#define pii pair<int, int>  // 用宏简化 pair<int, int> 的书写

    bool countLineIntersections(vector<pii>& coordinates) {  // 扫描线统计该方向上可切出的段数是否达到 3
        int lines = 0;  // 已扫描到的可切线数量
        int overlap = 0;  // 当前被矩形覆盖的区间数（重叠计数）
        for (int i = 0; i < coordinates.size(); ++i) {  // 按坐标顺序遍历所有事件点
            if (coordinates[i].second == 0)  // 若该点是矩形的结束边（marker 为 0）
                overlap--;  // 覆盖数减一
            else  // 否则该点是矩形的起始边
                overlap++;  // 覆盖数加一
            if (overlap == 0)  // 覆盖数重新归零，说明此处可以切一刀
                lines++;  // 可切线数加一
        }  // 循环结束
        return lines >= 3;  // 可切线达到 3 条即能把网格切成 3 块
    }  // 方法结束

public:  // 公有方法
    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {  // 判断能否沿水平或垂直方向把矩形切成 3 块
        vector<pii> y_cordinates, x_cordinates;  // y 方向与 x 方向的事件点集合
        for (auto& rectangle : rectangles) {  // 枚举每个矩形，拆成起始边与结束边两个事件
            y_cordinates.push_back(make_pair(rectangle[1], 1));  // 记录 y 方向下边界作为起始事件
            y_cordinates.push_back(make_pair(rectangle[3], 0));  // 记录 y 方向上边界作为结束事件
            x_cordinates.push_back(make_pair(rectangle[0], 1));  // 记录 x 方向左边界作为起始事件
            x_cordinates.push_back(make_pair(rectangle[2], 0));  // 记录 x 方向右边界作为结束事件
        }  // 循环结束
        sort(y_cordinates.begin(), y_cordinates.end());  // 事件点按 (坐标, 类型) 升序排序，同一坐标时结束边排在前面
        sort(x_cordinates.begin(), x_cordinates.end());  // 同样对 x 方向的事件点排序

        // Line-Sweep on x and y cordinates
        return (countLineIntersections(y_cordinates) or countLineIntersections(x_cordinates));  // 任一方向能切出 3 块即返回 true
    }  // 方法结束
};  // 类定义结束