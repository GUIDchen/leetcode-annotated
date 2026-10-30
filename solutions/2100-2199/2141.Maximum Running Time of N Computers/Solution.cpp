// 题目：2141. 同时运行 N 台电脑的最长时间（Maximum Running Time of N Computers）
// 思路：二分答案时长 mid，每块电池最多贡献 min(电量, mid)，若所有贡献之和 >= n * mid 说明 mid 可行。
// 时间复杂度：O(m log(sum))，m 为电池数，sum 为总电量；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:
    long long maxRunTime(int n, vector<int>& batteries) {  // n：电脑台数；batteries：每块电池的电量
        long long l = 0, r = 0;  // 二分区间 [l, r]，初始都置 0
        for (int x : batteries) {  // 累加全部电量，作为答案的上界（所有电脑总时长不可能超过总电量）
            r += x;  // 把当前电池电量加到上界里
        }
        while (l < r) {  // 整数二分：l 为可行、r 待放宽的边界
            long long mid = (l + r + 1) >> 1;  // 中点向上取整，配合下面的 l = mid 避免死循环
            long long s = 0;  // 统计所有电池在 mid 时长下能贡献的总电量
            for (int x : batteries) {  // 逐块电池累加
                s += min(1LL * x, mid);  // 单块电池最多用到 mid 小时；1LL 把 int 提升为 long long 防止溢出
            }
            if (s >= n * mid) {  // 总贡献够 n 台电脑同时跑 mid 小时，说明 mid 可行
                l = mid;  // 抬高下界
            } else {  // 总电量不足，说明 mid 偏大
                r = mid - 1;  // 上界收缩到 mid-1
            }
        }
        return l;  // l 就是最大可行时长
    }
};  // 题解类结束