// 题目：2594. 修车的最少时间（Minimum Time to Repair Cars）
// 思路：答案具有单调性——时间 t 越长越能修完，于是二分时间；检验时每个修理工 r 在 t 分钟内能修 floor(sqrt(t / r)) 辆车，累加判断是否够 cars 辆。
// 时间复杂度：O(n log(maxTime))，二分约 log 次、每次扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long repairCars(vector<int>& ranks, int cars) {  // ranks 是每位修理工的工级，cars 是待修车辆数
        long long left = 0, right = 1LL * ranks[0] * cars * cars;  // 二分下界取 0，上界取「只用最快的修理工 r 修完全部车」所需的时长
        while (left < right) {  // 标准二分：区间收缩到唯一答案
            long long mid = (left + right) >> 1;  // 取中点时间，右移一位等价于除以 2
            long long cnt = 0;  // mid 分钟内所有修理工能修的车辆总数
            for (int r : ranks) {  // 枚举每位修理工
                cnt += sqrt(mid / r);  // 工级 r 的修理工耗时 r*n^2，故能修 floor(sqrt(mid/r)) 辆
            }
            if (cnt >= cars) {  // mid 分钟内够修完全部车辆
                right = mid;  // 说明答案不大于 mid，收缩右边界
            } else {  // 时间不够
                left = mid + 1;  // 答案一定大于 mid，收紧左边界
            }
        }
        return left;  // 二分收敛后的 left 就是最少需要的分钟数
    }
};