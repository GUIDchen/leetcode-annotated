// 题目：2809. 使数组和小于等于 x 的最少时间（Minimum Time to Make Array Sum At Most x）
// 思路：把 (nums2, nums1) 按 nums2 升序排序，越早操作的元素会多付几次 nums2；再做背包式 DP，f[i][j] 表示前 i 个元素里选 j 个（共操作 j 秒）能减掉的最大和，最后枚举最小的可行秒数 j。
// 时间复杂度：O(n^2)，两层 DP 循环；空间复杂度：O(n^2)，二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumTime(vector<int>& nums1, vector<int>& nums2, int x) {  // nums1/nums2：两个等长数组；x：目标和；返回最少秒数
        int n = nums1.size();  // n：数组长度，最多只需 n 秒（每秒只需把一个元素归零）
        vector<pair<int, int>> nums;  // 打包成 (nums2, nums1)，方便按 nums2 升序排序
        for (int i = 0; i < n; ++i) {  // 把两个数组按下标合并成一条记录
            nums.emplace_back(nums2[i], nums1[i]);  // 先放 nums2 再放 nums1，这样 pair 的默认比较键就是 nums2
        }
        sort(nums.begin(), nums.end());  // 按 nums2 升序排序：nums2 越小的元素越应该先被操作
        int f[n + 1][n + 1];  // f[i][j]：前 i 个元素中操作 j 个（共 j 秒）能减少的最大和
        memset(f, 0, sizeof(f));  // 整张表清零，f[0][*] 作为边界：不选任何元素时减少量为 0
        for (int i = 1; i <= n; ++i) {  // 逐行推进：i 表示考虑到排序后的第 i 个元素
            for (int j = 0; j <= n; ++j) {  // 逐列推进：j 表示一共操作了几秒（也就是选了几个元素）
                f[i][j] = f[i - 1][j];  // 不选第 i 个元素：直接继承上一行的最优值
                if (j) {  // 只有 j > 0 时才存在「选它」的转移
                    auto [b, a] = nums[i - 1];  // 结构化绑定：b 是 nums2 的值，a 是 nums1 的值
                    f[i][j] = max(f[i][j], f[i - 1][j - 1] + a + b * j);  // 选它：它被安排在第 j 秒操作，收益是 a + b * j（b 要多付 j 次）
                }
            }
        }
        int s1 = accumulate(nums1.begin(), nums1.end(), 0);  // nums1 的元素和，即一次都不操作时的总和
        int s2 = accumulate(nums2.begin(), nums2.end(), 0);  // nums2 的元素和，每过一秒所有尚未归零的元素都会再加一遍
        for (int j = 0; j <= n; ++j) {  // 从小到大枚举秒数，第一个满足条件的 j 就是最少时间
            if (s1 + s2 * j - f[n][j] <= x) {  // j 秒后的总和 = s1 + s2 * j 减去 DP 求出的最大减少量
                return j;  // 已经不超过 x，直接返回这个秒数
            }
        }
        return -1;  // 枚举完所有秒数都不行，说明无解
    }
};  // 类定义结束