// 3453. 分割正方形 I / Separate Squares I
// 核心思路：二分水平分割线高度 y，用每个正方形落在 y 以下的面积之和判断是否已达到总面积一半，取最小的可行高度。
// 复杂度：时间复杂度 O(n·log((maxY)/eps))，空间复杂度 O(1)。
class Solution {  // 题解类
public:  // 公有接口
    vector<vector<int>>* squares;  // 指向输入正方形的指针，供 check 复用
    double s;  // 所有正方形的面积总和

    bool check(double y1) {  // 判断水平线 y=y1 以下的面积是否已达到总面积的一半
        double t = 0.0;  // 累加 y1 以下的面积
        for (const auto& a : *squares) {  // 遍历每个正方形
            int y = a[1];  // 正方形左下角的纵坐标
            int l = a[2];  // 正方形边长
            if (y < y1) {  // 正方形底边在分割线之下才会产生贡献
                t += (double) l * min(y1 - y, (double) l);  // 截取高度取 min(y1-y, l)，再乘宽 l 得到面积
            }  // 结束单块面积判断
        }  // 结束正方形遍历
        return t >= s / 2.0;  // 下方面积已够一半则分割线可行
    }  // 结束 check

    double separateSquares(vector<vector<int>>& squares) {  // 求使上下两部分面积相等的最小高度
        this->squares = &squares;  // 把输入挂到成员变量上供 check 使用
        s = 0.0;  // 总面积清零
        double l = 0.0;  // 二分左界：最小可能的纵坐标
        double r = 0.0;  // 二分右界：所有正方形上边界的最大值
        for (const auto& a : squares) {  // 预处理总面积与 y 的上界
            s += (double) a[2] * a[2];  // 累加正方形面积
            r = max(r, (double) a[1] + a[2]);  // 更新最高的上边界
        }  // 结束预处理
        const double eps = 1e-5;  // 二分精度
        while (r - l > eps) {  // 区间尚未收敛
            double mid = (l + r) / 2.0;  // 取中点作为候选分割线
            if (check(mid)) {  // 中点处下方面积已满足一半
                r = mid;  // 收缩右界，继续找更小的可行高度
            } else {  // 中点处下方面积不足
                l = mid;  // 抬高左界
            }  // 结束分支
        }  // 结束二分
        return r;  // 返回满足条件的最小高度
    }  // 结束 separateSquares
};  // 结束题解类
