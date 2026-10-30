// 题目：2786. 访问数组中的位置使分数最大（Visit Array Positions to Maximize Score）
// 核心思路：按奇偶性分两状态的线性 DP。f[p] 表示最后停留位置奇偶性为 p 时的最大得分；从同奇偶位置接过来不扣 x，从另一奇偶接过来扣 x，再加上当前值。
// 时间复杂度：O(n)，每个位置只做常数次比较；空间复杂度：O(1)，只用两个状态。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maxScore(vector<int>& nums, int x) {  // nums：数组；x：切换奇偶性要扣的分数；返回可获得的最高分数
        const long long inf = 1LL << 60;  // 用一个足够大的数当“负无穷”，表示该状态尚不可达
        vector<long long> f(2, -inf);  // f[p] 表示最后停留位置奇偶性为 p 时的最大得分，两个状态初始都不可达
        f[nums[0] & 1] = nums[0];  // 起点固定在下标 0，直接拿到 nums[0]，它所在的状态就是它的奇偶性
        int n = nums.size();  // n 是数组长度
        for (int i = 1; i < n; ++i) {  // 从下标 1 开始，逐个尝试作为新的落点
            int v = nums[i];  // 当前元素的值
            f[v & 1] = max(f[v & 1], f[v & 1 ^ 1] - x) + v;  // 若续在同奇偶性的最优解后面不扣 x，若从另一奇偶性切换过来则扣 x，最后加上当前值
        }  // 循环结束
        return max(f[0], f[1]);  // 答案取两种奇偶性终态中的较大值
    }  // 方法结束
};  // 类定义结束