// 题目：2187. 完成旅途的最少时间（Minimum Time to Complete Trips）
// 思路：答案具有单调性（时间越长能跑的趟数越多），于是对时间做二分；上界取「只用最快的车跑完全部趟数」。
// 时间复杂度：O(n·log(mi·totalTrips))；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumTime(vector<int>& time, int totalTrips) {  // time：每辆车跑一趟的耗时；totalTrips：需要完成的总趟数
        int mi = *min_element(time.begin(), time.end());  // 最快的单趟耗时，用来估计答案上界
        long long left = 1, right = 1LL * mi * totalTrips;  // 二分区间：只用最快的车连跑全部趟数一定够，作为上界
        while (left < right) {  // 二分查找最小的可行时间
            long long cnt = 0;  // 记录在 mid 时间内所有车合计能跑的趟数
            long long mid = (left + right) >> 1;  // 取中点，右移一位等价于除以 2
            for (int v : time) {  // 枚举每一辆车
                cnt += mid / v;  // 该车在 mid 时间内能跑 mid / v 趟
            }  // 内层循环结束
            if (cnt >= totalTrips) {  // 趟数足够，说明 mid 可行，尝试更小的答案
                right = mid;  // 保留 mid，收缩右边界
            } else {  // 趟数不足，说明 mid 太小
                left = mid + 1;  // 排除 mid，收缩左边界
            }  // 分支结束
        }  // 二分结束，左右边界重合
        return left;  // 该位置即最小可行时间
    }  // 方法结束
};  // 类定义结束