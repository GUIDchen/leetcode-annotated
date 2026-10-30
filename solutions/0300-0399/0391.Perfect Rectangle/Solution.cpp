// 题目：391. 完美矩形（Perfect Rectangle）
// 思路：所有小矩形面积之和须等于外包矩形面积，且四个角各只出现一次；其余顶点只出现 2 次或 4 次才说明既无重叠也无空缺。
// 时间复杂度：O(n log n)，n 个小矩形的 4n 个顶点要在有序表里插入；空间复杂度：O(n)，顶点计数表最多存 4n 项。
#include <bits/stdc++.h>  // 引入标准库万能头，判题环境允许这种写法
using namespace std;  // 使用 std 命名空间，省去 std:: 前缀

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isRectangleCover(vector<vector<int>>& rectangles) {  // rectangles 每项是 {x1, y1, x2, y2} 的小矩形，判断它们能否不重不漏拼成一个大矩形
        long long area = 0;  // 累加所有小矩形的面积，用于和外包矩形面积比对
        int minX = rectangles[0][0], minY = rectangles[0][1];  // 外包矩形的左下角坐标，先用第一个小矩形的左下角初始化
        int maxX = rectangles[0][2], maxY = rectangles[0][3];  // 外包矩形的右上角坐标，先用第一个小矩形的右上角初始化

        using pii = pair<int, int>;  // 给坐标二元组起别名，后面写起来更短
        map<pii, int> cnt;  // 顶点计数表：键是顶点坐标，值是它被多少个小矩形覆盖

        for (auto& r : rectangles) {  // 逐个处理每个小矩形
            area += (r[2] - r[0]) * 1LL * (r[3] - r[1]);  // 1LL 把乘法提升到 64 位，避免面积相乘溢出

            minX = min(minX, r[0]);  // 更新外包矩形的左边界
            minY = min(minY, r[1]);  // 更新外包矩形的下边界
            maxX = max(maxX, r[2]);  // 更新外包矩形的右边界
            maxY = max(maxY, r[3]);  // 更新外包矩形的上边界

            ++cnt[{r[0], r[1]}];  // 左下角顶点计数加一
            ++cnt[{r[0], r[3]}];  // 左上角顶点计数加一
            ++cnt[{r[2], r[3]}];  // 右上角顶点计数加一
            ++cnt[{r[2], r[1]}];  // 右下角顶点计数加一
        }

        if (area != (long long) (maxX - minX) * (maxY - minY) || cnt[{minX, minY}] != 1 || cnt[{minX, maxY}] != 1 || cnt[{maxX, maxY}] != 1 || cnt[{maxX, minY}] != 1) {  // 面积必须等于外包矩形面积，且外包矩形的四个角落顶点只能各出现一次
            return false;  // 任一条件不满足，都不可能做到完美覆盖
        }

        cnt.erase({minX, minY});  // 删掉左下角顶点，它之后不应再被内部线段用到
        cnt.erase({minX, maxY});  // 删掉左上角顶点
        cnt.erase({maxX, maxY});  // 删掉右上角顶点
        cnt.erase({maxX, minY});  // 删掉右下角顶点

        return all_of(cnt.begin(), cnt.end(), [](pair<pii, int> e) {  // 剩下的内部顶点：完美覆盖时只会是两矩形交点或四矩形交汇的十字中心
            return e.second == 2 || e.second == 4;  // 出现次数必须是 2 或 4，否则说明有重叠或空缺
        });  // all_of 对所有剩余顶点依次做这个判断
    }
};