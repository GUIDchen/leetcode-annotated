// 题目：2411. 按位或最大的最小子数组长度（Smallest Subarrays With Maximum Bitwise OR）
// 思路：从右往左扫描，用 f[j] 记录第 j 位上最近一次出现的下标；答案取决于所有出现过的位中最远的那个下标。
// 时间复杂度：O(32n)，每个位置固定检查 32 个二进制位；空间复杂度：O(n)，用于存放答案数组（f 只占常数 32）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> smallestSubarrays(vector<int>& nums) {  // nums 是输入数组，返回每个起点对应的最小长度
        int n = nums.size();  // n 为数组长度
        vector<int> f(32, -1);  // f[j] 表示第 j 位最近一次出现的下标，-1 表示还没出现过
        vector<int> ans(n);  // 存放每个下标对应的答案
        for (int i = n - 1; ~i; --i) {  // 从右往左遍历，~i 等价于 i >= 0
            int t = 1;  // 子数组至少包含 nums[i] 本身，长度从 1 开始
            for (int j = 0; j < 32; ++j) {  // 逐位检查 32 个二进制位
                if ((nums[i] >> j) & 1) {  // nums[i] 的第 j 位是 1
                    f[j] = i;  // 该位最近出现的下标更新为当前位置 i
                } else if (f[j] != -1) {  // nums[i] 没有这一位，但右侧存在带这一位的元素
                    t = max(t, f[j] - i + 1);  // 为了把这一位纳入按位或，子数组必须延伸到 f[j]
                }
            }
            ans[i] = t;  // 当前位置的答案就是这个所需的最大长度
        }
        return ans;  // 返回所有起点对应的最小子数组长度
    }
};