// 题目：1388. 3n 块披萨（Pizza With 3n Slices）
// 思路：环形数组选 n 个互不相邻的元素并求最大和；断环成链后分别去掉首尾各做一次线性 DP，取较大者。
// 时间复杂度：O(n^2)，两次 O(m*n) 的 DP；空间复杂度：O(m*n)，二维 DP 表（m 为链长）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSizeSlices(vector<int>& slices) {  // slices：环形排列的 3n 块披萨大小
        int n = slices.size() / 3;  // 一共需要选出 n 块（每选一块就淘汰两边的两块）
        auto g = [&](vector<int>& nums) -> int {  // 在断环后的线段上做「不相邻取 n 个」的 DP
            int m = nums.size();  // 当前线段长度
            int f[m + 1][n + 1];  // f[i][j]：前 i 个元素中选 j 个且互不相邻的最大和
            memset(f, 0, sizeof f);  // 全部初始化为 0，方便直接参与 max 比较
            for (int i = 1; i <= m; ++i) {  // 枚举前缀长度
                for (int j = 1; j <= n; ++j) {  // 枚举已选个数
                    f[i][j] = max(f[i - 1][j], (i >= 2 ? f[i - 2][j - 1] : 0) + nums[i - 1]);  // 不选第 i 个 与 选它并跳过相邻元素 取较大者
                }  // 个数枚举结束
            }  // 前缀枚举结束
            return f[m][n];  // 前 m 个里选 n 个的最优解
        };  // 匿名 DP 函数结束
        vector<int> nums(slices.begin(), slices.end() - 1);  // 情况一：去掉最后一块，首尾不再相邻
        int a = g(nums);  // 情况一的最大和
        nums = vector<int>(slices.begin() + 1, slices.end());  // 情况二：去掉第一块
        int b = g(nums);  // 情况二的最大和
        return max(a, b);  // 环形问题的最优解是两种情况中较大的那个
    }  // maxSizeSlices 结束
};  // Solution 类结束