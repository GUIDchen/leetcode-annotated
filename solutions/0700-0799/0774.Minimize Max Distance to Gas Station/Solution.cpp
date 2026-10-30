// 题目：774. 最小化去加油站的最大距离（Minimize Max Distance to Gas Station）
// 核心思路：二分答案 x（允许的最大间距）；判定时每个相邻区间需要新增 floor(间距/x) 个加油站，总数不超过 k 则 x 可行。
// 时间复杂度 O(n·log(1e8/1e-6))，每次判定 O(n)；空间复杂度 O(1)（只用到常数个变量）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对判题器可见
    double minmaxGasDist(vector<int>& stations, int k) {  // stations：已排序的加油站坐标；k：还能新建的加油站个数；返回最小化的最大间距
        double left = 0, right = 1e8;  // 二分区间：答案一定在 0 到 1e8 之间
        auto check = [&](double x) {  // 判定函数：lambda 按引用捕获 stations 与 k
            int s = 0;  // s 统计把间距压到不超过 x 需要新增的加油站总数
            for (int i = 0; i < stations.size() - 1; ++i) {  // 枚举每一对相邻加油站
                s += (int) ((stations[i + 1] - stations[i]) / x);  // 该区间需要向下取整的「间距 / x」个新站，强转 int 即向下取整
            }  // for 循环结束
            return s <= k;  // 所需总数不超过 k，说明 x 可行（还可以更小）
        };  // lambda 定义结束
        while (right - left > 1e-6) {  // 浮点二分：区间宽度缩小到 1e-6 以内即认为收敛
            double mid = (left + right) / 2.0;  // 取区间中点作为候选答案
            if (check(mid)) {  // mid 可行
                right = mid;  // 可行就收缩右边界，继续尝试更小的间距
            } else {  // mid 不可行
                left = mid;  // 不可行就抬高左边界，间距必须更大
            }  // if 结束
        }  // while 结束
        return left;  // left 停在可行解一侧，即最小化的最大间距
    }  // 方法结束
};  // 类定义结束