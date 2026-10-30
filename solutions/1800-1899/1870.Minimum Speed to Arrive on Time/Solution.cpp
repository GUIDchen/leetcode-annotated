// 题目：1870. 准时到达的列车最小时速（Minimum Speed to Arrive on Time）
// 思路：速度越大总耗时单调不增，于是对速度二分答案；判定函数按「非末段向上取整、末段保留小数」累计耗时。
// 时间复杂度：O(n log 1e7)，二分约 24 次、每次 O(n) 判定；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minSpeedOnTime(vector<int>& dist, double hour) {  // dist：各段距离；hour：允许的总时间（小时）
        if (dist.size() > ceil(hour)) {  // 每段至少要耗 1 小时（末段除外），段数超过可用整数小时就必然来不及
            return -1;  // 无解
        }  // 结束 if
        const int m = 1e7;  // 速度上界：题目约定答案不超过 1e7
        int l = 1, r = m + 1;  // 二分区间 [l, r)，答案只在 [1, 1e7] 内
        int n = dist.size();  // 段数，供下面的判定函数复用
        auto check = [&](int v) {  // 判定函数：速度为 v 时能否在 hour 小时内到达
            double s = 0;  // 累计总耗时
            for (int i = 0; i < n; ++i) {  // 逐段累加耗时
                double t = dist[i] * 1.0 / v;  // 第 i 段在速度 v 下的实际耗时
                s += i == n - 1 ? t : ceil(t);  // 只有末段能保留小数，其余段必须等到整数小时才能发车
            }  // 结束 for
            return s <= hour;  // 总耗时不超过 hour 即说明速度 v 可行
        };  // 结束 lambda
        while (l < r) {  // 二分查找最小的可行速度
            int mid = (l + r) >> 1;  // 取中点，等价于 (l + r) / 2
            if (check(mid)) {  // mid 可行，答案落在左半区
                r = mid;  // 收缩右边界，保留 mid 作为候选
            } else {  // mid 不可行，答案落在右半区
                l = mid + 1;  // 收缩左边界
            }  // 结束 if/else 分支
        }  // 结束 while
        return l > m ? -1 : l;  // 收敛到上界之外说明 1e7 也不够快，返回 -1
    }  // 结束方法
};  // 结束类
