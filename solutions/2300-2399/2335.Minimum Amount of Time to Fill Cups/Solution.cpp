// 题目：2335. 装满杯子需要的最短总时长（Minimum Amount of Time to Fill Cups）
// 核心思路：每一秒同时给当前剩余最多的两种杯子各倒一杯，排序后让最大的两个杯子同时减一，直到全部为零。
// 时间复杂度：O(sum(amount))，每秒只做常数次比较；空间复杂度：O(1)，仅用常数额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int fillCups(vector<int>& amount) {  // amount：三种杯子各自还需要的杯数，返回值是最短总秒数
        int ans = 0;  // ans：已经花费的秒数，也就是最终答案
        while (amount[0] + amount[1] + amount[2]) {  // 只要三种杯子的需求之和不为 0，说明还没装满，继续下一秒
            sort(amount.begin(), amount.end());  // 升序排序，使 amount[2] 是需求最多的杯子、amount[1] 次之
            ++ans;  // 开始新的一秒，秒数加一
            amount[2]--;  // 需求最多的那种杯子倒一杯（需求减一）
            amount[1] = max(0, amount[1] - 1);  // 次多的杯子也倒一杯；减去后可能变成负数，用 max 夹到 0 表示该杯子已空
        }  // 循环体结束，回到条件重新判断
        return ans;  // 返回装满所有杯子所需的最短总时长
    }  // fillCups 方法结束
};  // Solution 类结束