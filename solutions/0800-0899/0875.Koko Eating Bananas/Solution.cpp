// 题目：875. 爱吃香蕉的珂珂（Koko Eating Bananas）
// 核心思路：总耗时随速度单调不增，在 [1, max(piles)] 上二分答案，用向上取整的耗时之和判断当前速度是否可行。
// 时间复杂度：O(m log M)，m 为堆数、M 为最大堆的石子数；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minEatingSpeed(vector<int>& piles, int h) {  // piles：每堆香蕉数量；h：守卫离开的时限（小时）
        int l = 1, r = ranges::max(piles);  // 二分区间左端为 1（速度不能为 0），右端为最大的一堆，速度再快也不会更好
        while (l < r) {  // 二分答案：在区间内找最小的可行速度
            int mid = (l + r) >> 1;  // 取中点作为候选速度，右移一位等价于整除 2
            int s = 0;  // s 统计以 mid 速度吃完所有香蕉需要的总小时数
            for (int x : piles) {  // 遍历每一堆香蕉
                s += (x + mid - 1) / mid;  // 向上取整：ceil(x / mid) 写成 (x + mid - 1) / mid，不足一小时也按一小时算
            }  // 所有堆的耗时统计完毕
            if (s <= h) {  // 总耗时不超过时限，说明 mid 可行，还可以尝试更慢的速度
                r = mid;  // 收缩上界到 mid 并保留 mid（它是可行解）
            } else {  // 否则吃得太慢会超时
                l = mid + 1;  // 下界右移一位，抛弃所有不大于 mid 的速度
            }  // 分支结束
        }  // 二分结束，此时 l == r，就是最小的可行速度
        return l;  // 返回答案
    }  // minEatingSpeed 结束
};  // Solution 类结束