// 题目：1610. 可见点的最大数目（Maximum Number of Visible Points）
// 思路：把每个点转成相对观察者的极角并排序，再复制一份加 2π 处理环形；用双指针维护角度跨度 ≤ angle 的窗口，求窗口内最多的点数，最后加上与观察者重合的点。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(n)，存放极角数组。
class Solution {  // 题解类
public:  // 对外接口
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {  // points 是全部点，angle 是视野角度（度），location 是观察者位置
        vector<double> v;  // 保存除观察者自身外所有点相对观察者的极角（弧度）
        int x = location[0], y = location[1];  // 观察者坐标
        int same = 0;  // 与观察者重合的点必定可见，单独计数（atan2(0, 0) 没有意义）
        for (auto& p : points) {  // 遍历每个点
            int xi = p[0], yi = p[1];  // 取出该点的坐标
            if (xi == x && yi == y)  // 该点与观察者重合
                ++same;  // 重合点始终可见，直接累加
            else  // 否则需要计算极角
                v.emplace_back(atan2(yi - y, xi - x));  // atan2(dy, dx) 得到方向角，范围 (-π, π]
        }  // 遍历结束
        sort(v.begin(), v.end());  // 极角升序排序，便于用双指针找角度跨度不超过视野的一段
        int n = v.size();  // 非重合点的个数
        for (int i = 0; i < n; ++i) v.emplace_back(v[i] + 2 * M_PI);  // 复制一份并整体加 2π，把环形角度区间「拉直」，从而可跨 0 度统计

        int mx = 0;  // 窗口内最多能包含的点数
        double t = angle * M_PI / 180;  // 把角度制换算成弧度
        for (int i = 0, j = 0; j < 2 * n; ++j) {  // 双指针滑动窗口：i 为窗口左端，j 为窗口右端，j 扫描整条拉直后的序列
            while (i < j && v[j] - v[i] > t) ++i;  // 右端与左端的角度差超出视野时，左端右移收缩窗口
            mx = max(mx, j - i + 1);  // 用当前窗口长度更新答案
        }  // 滑动窗口结束
        return mx + same;  // 窗口内的点再加上与观察者重合的点
    }
};