// 3625. Count Number of Trapezoids II（3625. 统计梯形的数目 II）
// 核心思路：枚举所有点对得直线 (k, b) 与中点，cnt1 统计同斜率下不同截距的线段数，cnt2 统计同斜率同中点的线段数；按前缀和两两组合，前者累加、后者扣除共线退化情形。
// 复杂度：时间 O(n^2) 建表 + O(n^2) 统计，空间 O(n^2) 存储线段信息。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    int countTrapezoids(vector<vector<int>>& points) {  // 统计所有点对构成的梯形数目
        int n = points.size();  // 点的个数
        unordered_map<double, unordered_map<double, int>> cnt1;  // 斜率 k -> (截距 b -> 线段数)
        unordered_map<int, unordered_map<double, int>> cnt2;  // 中点编码 -> (斜率 k -> 线段数)

        cnt1.reserve(n * n);  // 预留桶数，避免频繁 rehash
        cnt2.reserve(n * n);  // 预留桶数，避免频繁 rehash

        for (int i = 0; i < n; ++i) {  // 枚举点对 (i, j)，j < i
            int x1 = points[i][0], y1 = points[i][1];  // 第一个点的坐标
            for (int j = 0; j < i; ++j) {  // 只需枚举 j < i，避免重复
                int x2 = points[j][0], y2 = points[j][1];  // 第二个点的坐标
                int dx = x2 - x1, dy = y2 - y1;  // 两点坐标差
                double k = (dx == 0 ? 1e9 : 1.0 * dy / dx);  // 斜率，竖直线用一个极大值代替
                double b = (dx == 0 ? x1 : 1.0 * (1LL * y1 * dx - 1LL * x1 * dy) / dx);  // 截距，竖直线用横坐标代替

                cnt1[k][b] += 1;  // 累计该直线上的线段数
                int p = (x1 + x2 + 2000) * 4001 + (y1 + y2 + 2000);  // 把中点坐标编码成一个整数
                cnt2[p][k] += 1;  // 累计该中点、该斜率的线段数
            }
        }

        int ans = 0;  // 答案：平行四边形/梯形数目
        for (auto& [_, e] : cnt1) {  // 遍历每个斜率分组
            int s = 0;  // 之前各截距上线段数的前缀和
            for (auto& [_, t] : e) {  // 遍历该斜率下每条直线的线段数
                ans += s * t;  // 不同直线上的线段两两配对，形成平行底边
                s += t;  // 累加前缀和
            }
        }
        for (auto& [_, e] : cnt2) {  // 遍历每个中点分组
            int s = 0;  // 之前各斜率上线段数的前缀和
            for (auto& [_, t] : e) {  // 遍历该中点下的线段数
                ans -= s * t;  // 同中点同斜率说明线段共线重叠，属于退化情况要扣除
                s += t;  // 累加前缀和
            }
        }
        return ans;  // 返回统计结果
    }
};
