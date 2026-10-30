// 题目：2263. 数组变为有序的最小操作次数（Make Array Non-decreasing or Non-increasing）
// 思路：目标只有「非递减」和「非递增」两种。反转数组后求一次非递减，就等价于求原数组的非递增，两次取较小值。非递减用 DP：f[i][j] 表示前 i 个数非递减且第 i 个数取 j 的最小代价，用上一行的前缀最小值把转移降到 O(1)。
// 时间复杂度：O(n * V)，V = 1001 为取值上界，反转与两次求解仍是同阶；空间复杂度：O(n * V)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int convertArray(vector<int>& nums) {  // nums：原数组；返回把它变成非递减或非递增所需的最小操作次数
        int a = solve(nums);  // 先求变成非递减的最小代价
        reverse(nums.begin(), nums.end());  // 原地反转数组：反转后的非递减，等价于原数组的非递增
        int b = solve(nums);  // 再求反转后数组变成非递减的最小代价
        return min(a, b);  // 两个方向取较小值作为最终答案
    }  // convertArray 结束

    int solve(vector<int>& nums) {  // 辅助函数：把 nums 变成非递减数组的最小操作次数
        int n = nums.size();  // 元素个数
        int f[n + 1][1001];  // DP 表（栈上变长数组）：f[i][j] 为前 i 个数非递减且第 i 个数取 j 的最小代价
        memset(f, 0, sizeof(f));  // 全部清零，保证 f[0][*] = 0 这个空数组的合法初态
        for (int i = 1; i <= n; ++i) {  // 按原数组顺序逐个确定每个位置的取值
            int mi = 1 << 30;  // 维护上一行 f[i-1][0..j] 的前缀最小值，供 O(1) 转移使用
            for (int j = 0; j <= 1000; ++j) {  // 枚举当前元素的取值 j（题目保证 0 <= nums[i] <= 1000）
                mi = min(mi, f[i - 1][j]);  // 把 f[i-1][j] 并入前缀最小值，即前一个数可取 0..j 中任意值
                f[i][j] = mi + abs(nums[i - 1] - j);  // 转移：前一个数不超过 j 的最小代价 + 把当前元素改成 j 的代价
            }
        }
        return *min_element(f[n], f[n] + 1001);  // 最后一个数取任何值都合法，取整行的最小值即为答案
    }
};