// 题目：2644. 找出可整除性得分最大的整数（Find the Maximum Divisibility Score）
// 思路：对每个候选除数统计 nums 中能被它整除的个数，得分更高就替换，得分打平则取更小的除数。
// 时间复杂度：O(m * n)，m 为除数个数、n 为 nums 长度；空间复杂度：O(1)，只用几个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxDivScore(vector<int>& nums, vector<int>& divisors) {  // nums：被除数数组；divisors：候选除数
        int ans = divisors[0];  // 当前最优除数，先假设为第一个
        int mx = 0;  // 当前最高得分
        for (int div : divisors) {  // 逐个尝试每个候选除数
            int cnt = 0;  // 本除数的得分（能整除的个数）
            for (int x : nums) {  // 遍历 nums 逐个判断
                cnt += x % div == 0;  // 整除时比较表达式为 true（即 1），直接累加到得分
            }
            if (mx < cnt) {  // 得分更高，直接替换最优解
                mx = cnt;  // 更新最高得分
                ans = div;  // 更新最优除数
            } else if (mx == cnt) {  // 得分打平，题目要求取数值更小的除数
                ans = min(ans, div);  // 与当前答案比较，保留较小者
            }
        }
        return ans;  // 返回可整除性得分最大的最小除数
    }
};