// 题目：2871. 将数组分割成最多数目的子数组（Split Array Into Maximum Number of Subarrays）
// 思路：贪心从左往右切，当前子数组的按位与一旦变成 0 就立刻切一段；最后没凑成 0 的残余并进前一段。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSubarrays(vector<int>& nums) {  // nums 为输入数组，返回最多能切出的子数组数目
        int score = -1, ans = 1;  // score 为当前子数组的按位与（-1 是全 1，便于开始累与）；ans 是段数基准，初值 1 让「一段都没切」时直接返回 1
        for (int num : nums) {  // 从左往右遍历每个数
            score &= num;  // 把当前数并入当前子数组的按位与
            if (score == 0) {  // 与值变成 0，这一段已经不可能更小，立刻切分最优
                --score;  // 把 score 复位成全 1，开始统计下一段
                ++ans;  // 段数基准加一，记录这里切了一刀
            }  // 切分判断结束
        }  // 遍历结束
        return ans == 1 ? 1 : ans - 1;  // 没切过就返回 1（整体与值大于 0）；否则切了几刀就是几段
    }  // 方法结束
};  // 类定义结束