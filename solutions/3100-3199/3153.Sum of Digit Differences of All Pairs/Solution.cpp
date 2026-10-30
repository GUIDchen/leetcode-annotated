// 题目：3153. 所有数对中数位差之和（Sum of Digit Differences of All Pairs）
// 思路：按位统计 0~9 各数字出现次数，某一位上取值不同的数对数 = Σ cnt[i] * (n - cnt[i])，最后除以 2 去掉有序重复。
// 时间复杂度：O(n * m)，m 为数字位数（本题不超过 9）；空间复杂度：O(1)，只用一个长度 10 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long sumDigitDifferences(vector<int>& nums) {  // nums：输入数组，返回所有数对的数位差之和
        int n = nums.size();  // 数字个数
        int m = floor(log10(nums[0])) + 1;  // 所有数字位数相同，用第一个数算出位数
        int cnt[10];  // 统计当前这一位上 0~9 各数字出现的次数
        long long ans = 0;  // 累加答案，结果可能超过 int 范围
        for (int k = 0; k < m; ++k) {  // 从最低位开始，逐位处理
            memset(cnt, 0, sizeof(cnt));  // 每一位都要重新清零计数
            for (int i = 0; i < n; ++i) {  // 扫描所有数字
                ++cnt[nums[i] % 10];  // 取出当前最低位上的数字并计数
                nums[i] /= 10;  // 去掉最低位，供下一轮统计使用
            }
            for (int i = 0; i < 10; ++i) {  // 遍历 0~9 这十个数字
                ans += 1LL * cnt[i] * (n - cnt[i]);  // 该位上取值不同的无序数对个数：cnt[i] * (n - cnt[i])
            }
        }
        return ans / 2;  // 同一无序数对被正反各算了一次，除以 2
    }
};
