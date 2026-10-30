// 题目：2143. 在两个数组的区间中选取数字（Choose Numbers From Two Arrays in Range）
// 思路：按区间右端点做 DP，f[i][j] 表示以 i 结尾、每个位置选 nums1 记 +、选 nums2 记 -、偏移后总和为 j 的区间个数；总和为 0 的计入答案。
// 时间复杂度：O(n (s1 + s2))，n 为数组长度，s1/s2 为两数组元素和；空间复杂度：O(n (s1 + s2))。
class Solution {  // LeetCode 约定的题解类
public:
    int countSubranges(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2：两个等长数组，区间内每个位置各取一个数
        int n = nums1.size();  // 数组长度
        int s1 = accumulate(nums1.begin(), nums1.end(), 0);  // nums1 的总和，走「加法」方向时总和的绝对值上界
        int s2 = accumulate(nums2.begin(), nums2.end(), 0);  // nums2 的总和，作为偏移量基准，让 DP 下标非负
        int f[n][s1 + s2 + 1];  // f[i][j]：以 i 结尾、总和加偏移 s2 后为 j 的合法区间个数
        memset(f, 0, sizeof(f));  // 全部初始化为 0
        int ans = 0;  // 累计所有合法区间（总和为 0）的数量
        const int mod = 1e9 + 7;  // 方案数很多，按 1e9+7 取模
        for (int i = 0; i < n; ++i) {  // 枚举区间的右端点 i
            int a = nums1[i], b = nums2[i];  // 当前位置的两个候选值：选 nums1 记 +a，选 nums2 记 -b
            f[i][a + s2]++;  // 区间只含 i 且选 nums1：总和为 a
            f[i][-b + s2]++;  // 区间只含 i 且选 nums2：总和为 -b
            if (i) {  // 长度大于 1 的区间要从右端点 i-1 转移
                for (int j = 0; j <= s1 + s2; ++j) {  // 枚举所有可能的偏移后总和
                    if (j >= a) {  // 前一段总和 j-a 不越下界才可以转移
                        f[i][j] = (f[i][j] + f[i - 1][j - a]) % mod;  // 在 i 处选 nums1，总和增加 a
                    }
                    if (j + b <= s1 + s2) {  // 前一段总和 j+b 不越上界才可以转移
                        f[i][j] = (f[i][j] + f[i - 1][j + b]) % mod;  // 在 i 处选 nums2，总和减少 b
                    }
                }
            }
            ans = (ans + f[i][s2]) % mod;  // 偏移 s2 对应真实总和 0，把以 i 结尾的合法区间计入答案
        }
        return ans;  // 返回答案
    }
};  // 题解类结束