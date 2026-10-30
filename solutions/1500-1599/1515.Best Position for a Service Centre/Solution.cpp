// 题目：1515. 服务中心的最佳位置（Best Position for a Service Centre）
// 思路：目标函数是各点到服务中心的欧氏距离之和（凸函数），用梯度下降 + 步长衰减迭代逼近最优位置。
// 时间复杂度：O(n log(1/eps))，每轮遍历 n 个点；空间复杂度：O(1)，只维护坐标与梯度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double getMinDistSum(vector<vector<int>>& positions) {  // positions：所有客户点坐标；返回服务中心到所有点距离之和的最小值
        int n = positions.size();  // n：客户点个数
        double x = 0, y = 0;  // x、y：当前迭代的服务中心坐标，先置 0 准备累加
        for (auto& p : positions) {  // 遍历所有点求重心，作为迭代起点（重心离最优点通常很近，收敛快）
            x += p[0];  // 累加横坐标
            y += p[1];  // 累加纵坐标
        }  // 结束累加
        x /= n;  // 取平均得到初始横坐标
        y /= n;  // 取平均得到初始纵坐标
        double decay = 0.999;  // decay：每轮步长的衰减系数，让迭代后期更稳定、不发散
        double eps = 1e-6;  // eps：梯度足够小的判停阈值
        double alpha = 0.5;  // alpha：初始学习率（步长倍数）
        while (true) {  // 无限循环，直到梯度足够小才 return
            double gradX = 0, gradY = 0;  // gradX/gradY：本轮梯度（距离和对 x、y 的偏导）
            double dist = 0;  // dist：当前坐标到所有点的距离和，即目标函数值
            for (auto& p : positions) {  // 遍历每个点，累计梯度与距离和
                double a = x - p[0], b = y - p[1];  // a、b：当前坐标与点 p 的坐标差
                double c = sqrt(a * a + b * b);  // c：当前坐标到点 p 的欧氏距离
                gradX += a / (c + 1e-8);  // 距离对 x 的偏导是 a/c，加 1e-8 避免与点重合时除零
                gradY += b / (c + 1e-8);  // 距离对 y 的偏导是 b/c，同样加 1e-8 防止除零
                dist += c;  // 累加目标函数值
            }  // 结束内层遍历
            double dx = gradX * alpha, dy = gradY * alpha;  // 沿梯度反方向乘以学习率得到本轮的移动量
            if (abs(dx) <= eps && abs(dy) <= eps) {  // 移动量已经很小，说明已收敛到最优位置附近
                return dist;  // 返回此时的距离和作为最小总距离
            }  // 结束收敛判断
            x -= dx;  // 沿负梯度方向移动横坐标（梯度上升的反方向即下降）
            y -= dy;  // 沿负梯度方向移动纵坐标
            alpha *= decay;  // 步长衰减，下一轮移动更保守
        }  // 继续下一轮迭代
    }  // 结束方法
};  // 结束题解类