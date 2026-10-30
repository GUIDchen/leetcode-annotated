// 题目：3296. 移山所需的最少秒数（Minimum Number of Seconds to Make Mountain Height Zero）
// 思路：答案对时间单调，二分秒数 t；判定时每个工人能削掉的高度由 wt*k(k+1)/2 <= t 解出 k，累加与 mountainHeight 比较。
// 时间复杂度：O(n log(1e16))，n 为工人数；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {  // mountainHeight 是总高度，workerTimes 是每个工人在第 1 块上花的时间倍数
        using ll = long long;  // 起别名，二分边界与中间结果都用 64 位整型防溢出
        ll l = 1, r = 1e16;  // 答案的二分区间：最少 1 秒，上界给一个足够大的 1e16
        auto check = [&](ll t) -> bool {  // 判定函数：限时 t 秒时所有工人最多能削掉多少高度
            ll h = 0;  // 累计全部工人可削掉的高度
            for (int& wt : workerTimes) {  // 枚举每个工人
                h += (long long) (sqrt(t * 2.0 / wt + 0.25) - 0.5);  // 由 wt*k(k+1)/2 <= t 解出 k = floor(sqrt(2t/wt+1/4)-1/2)，即该工人能削的块数
            }  // 该工人累加完毕，继续下一个
            return h >= mountainHeight;  // 总高度达到要求就说明 t 秒可行
        };  // 判定函数结束
        while (l < r) {  // 二分最小的可行时间
            ll mid = (l + r) >> 1;  // 取中点，右移一位等价于除以 2
            if (check(mid)) {  // mid 秒可行，答案不会超过 mid
                r = mid;  // 把右边界收缩到 mid
            } else {  // mid 秒不可行
                l = mid + 1;  // 答案至少是 mid+1
            }  // 分支结束
        }  // 区间收敛到单点
        return l;  // 此时 l 就是最少需要的秒数
    }  // minNumberOfSeconds 方法结束
};  // Solution 类定义结束
