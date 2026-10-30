// 题目：3269. 构建两个递增数组（Constructing Two Increasing Arrays）
// 思路：网格 DP，f[i][j] 表示 nums1 前 i 项、nums2 前 j 项都已放好后末尾数字的最小值，转移时由 nxt 贪心算出放下一项所能取到的最小合法数字。
// 时间复杂度：O(m·n)，空间复杂度：O(m·n)，m、n 分别为两个数组的长度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minLargest(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2：给定的 0/1 数组；返回构造出的两个递增数组中最大元素的最小值
        int m = nums1.size(), n = nums2.size();  // m、n：两个数组的长度
        int f[m + 1][n + 1];  // f[i][j]：放下 nums1 前 i 项、nums2 前 j 项后，末尾数字的最小可能值
        memset(f, 0, sizeof(f));  // DP 表清零
        auto nxt = [](int x, int y) -> int {  // nxt：当前末尾数字为 x 时，为数值 y 选出的最小合法数字（需大于 x 且与 y 同奇偶）
            return (x & 1 ^ y) == 1 ? x + 1 : x + 2;  // x 与 y 奇偶性不同时 x+1 即为最小合法数，相同时 x+1 奇偶性不符，必须跳到 x+2
        };  // lambda 定义结束
        for (int i = 1; i <= m; ++i) {  // 边界：nums2 尚未放任何数，只能依次放 nums1 的前缀
            f[i][0] = nxt(f[i - 1][0], nums1[i - 1]);  // 由前一状态递推
        }
        for (int j = 1; j <= n; ++j) {  // 边界：nums1 尚未放任何数，只能依次放 nums2 的前缀
            f[0][j] = nxt(f[0][j - 1], nums2[j - 1]);  // 由前一状态递推
        }
        for (int i = 1; i <= m; ++i) {  // 从左到右枚举 nums1 已放好的前缀长度
            for (int j = 1; j <= n; ++j) {  // 内层枚举 nums2 已放好的前缀长度
                int x = nxt(f[i - 1][j], nums1[i - 1]);  // 方案一：这一步放 nums1[i-1]
                int y = nxt(f[i][j - 1], nums2[j - 1]);  // 方案二：这一步放 nums2[j-1]
                f[i][j] = min(x, y);  // 取两种方案中末尾数字更小的那个
            }
        }
        return f[m][n];  // 全部放完后的最小末尾数字即为答案
    }
};
