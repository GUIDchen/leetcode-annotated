// 题目：1482. 制作 m 束花所需的最少天数（Minimum Number of Days to Make m Bouquets）
// 核心思路：可行性随天数单调递增，于是二分答案，并用一次贪心扫描判断能否凑出 m 束相邻的 k 朵花。
// 时间复杂度：O(n log max(bloomDay))；空间复杂度：O(1)，只用到常数额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minDays(vector<int>& bloomDay, int m, int k) {  // bloomDay：每朵花的开花日；m 束、每束 k 朵相邻花
        int mx = ranges::max(bloomDay);  // 最晚开花日，作为二分上界参考
        int l = 1, r = mx + 1;  // 二分区间 [l, r)，r 取开区间便于表示「无解」
        auto check = [&](int days) {  // 判定函数：等到第 days 天能否凑出 m 束花
            int cnt = 0, cur = 0;  // cnt：已扎成的花束数；cur：当前连续开花的花朵数
            for (int x : bloomDay) {  // 顺序扫描每朵花的开花时间
                cur = x <= days ? cur + 1 : 0;  // 已开花则连续长度 +1，未开花则连续段清零
                if (cur == k) {  // 连续 k 朵即可扎成一束
                    cnt++;  // 花束数加一
                    cur = 0;  // 这 k 朵已被用掉，连续计数归零
                }  // if (cur == k) 分支结束
            }  // for 循环结束
            return cnt >= m;  // 能凑够 m 束，说明 days 天可行
        };  // lambda 定义结束
        while (l < r) {  // 二分查找最小的可行天数
            int mid = (l + r) >> 1;  // 取中点，右移一位等价于整除 2
            if (check(mid)) {  // 检查 mid 天是否可行
                r = mid;  // 收缩右边界，继续尝试更小的天数
            } else {  // mid 天不可行，答案一定更大
                l = mid + 1;  // 答案必定在 mid 右侧
            }  // else 分支结束
        }  // while 循环结束
        return l > mx ? -1 : l;  // 收敛到 mx+1 说明永远凑不够，返回 -1
    }  // minDays 方法结束
};  // Solution 类定义结束
