// 题目：853. 车队（Car Fleet）
// 思路：按位置从右到左（离终点由近到远）扫描，算出每辆车到终点的耗时；耗时严格大于当前车队耗时就会形成新车队。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，用于排序的下标数组。
class Solution {  // 题解类
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {  // target 为终点位置，position/speed 分别是初始位置与速度
        int n = position.size();  // 车辆数
        vector<int> idx(n);  // 只对下标排序，避免同时搬移位置和速度两个数组
        iota(idx.begin(), idx.end(), 0);  // 填入 0..n-1 的连续下标
        sort(idx.begin(), idx.end(), [&](int i, int j) {  // 按下标所指位置从大到小排序（离终点近的在前）
            return position[i] > position[j];  // 位置大的排在前面
        });  // 排序回调结束
        int ans = 0;  // 车队数量
        double pre = 0;  // 上一个（更靠右）车队的到达耗时
        for (int i : idx) {  // 从离终点最近的车辆开始处理
            double t = 1.0 * (target - position[i]) / speed[i];  // 该车若独自行驶，到达终点所需时间
            if (t > pre) {  // 比前面的车队更慢就追不上，必然单独成为新车队
                ++ans;  // 车队数加一
                pre = t;  // 更新当前车队的到达耗时
            }  // 否则会并入前面的车队，不计数
        }  // 循环结束
        return ans;  // 返回车队总数
    }  // 方法结束
};  // 题解类结束