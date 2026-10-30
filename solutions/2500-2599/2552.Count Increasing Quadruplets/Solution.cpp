// 题目：2552. 统计上升四元组（Count Increasing Quadruplets）
// 思路：枚举中间下标 j、k。f[j][k] 统计 i < j 且 nums[i] < nums[k] 的个数，g[j][k] 统计 l > k 且 nums[l] > nums[j] 的个数；两者相乘即该 (j, k) 贡献的上升四元组数。因为只有 nums[j] > nums[k] 时才有意义，计数用「先扫一遍一侧、再让下标移动并动态扣减」的方式 O(1) 维护。
// 时间复杂度：O(n^2)，两轮各 O(n^2) 的扫描；空间复杂度：O(n^2)，两张 4001 x 4001 的静态计数表。
const int N = 4001;  // 计数表规模上限：n ≤ 4000，这里多留一位防止越界
int f[N][N];  // f[j][k]：满足 i < j 且 nums[i] < nums[k] 的 i 的个数
int g[N][N];  // g[j][k]：满足 l > k 且 nums[l] > nums[j] 的 l 的个数

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countQuadruplets(vector<int>& nums) {  // nums 是 1..n 的一个排列
        int n = nums.size();  // n 是数组长度
        memset(f, 0, sizeof f);  // 清空 f：评测机会用同一份数组跑多个用例，必须重置
        memset(g, 0, sizeof g);  // 清空 g
        for (int j = 1; j < n - 2; ++j) {  // 枚举第二个下标 j（前后都要留位置：1 ≤ j ≤ n-3）
            int cnt = 0;  // cnt 统计 l > j 且 nums[l] > nums[j] 的个数
            for (int l = j + 1; l < n; ++l) {  // 先扫一遍右侧，数出所有满足 nums[l] > nums[j] 的 l
                if (nums[l] > nums[j]) {  // 找到这样一个 l
                    ++cnt;  // 计数加一
                }
            }  // 右侧计数完成，cnt 现在是 k = j 时的初始值
            for (int k = j + 1; k < n - 1; ++k) {  // 枚举第三个下标 k（j < k < n-1），从左往右移动
                if (nums[j] > nums[k]) {  // nums[j] > nums[k]，即 nums[k] < nums[j]
                    f[j][k] = cnt;  // 把当前的右侧计数写入 f[j][k]（此时 cnt 正好是 l > k 的个数）
                } else {  // 否则 nums[k] > nums[j]
                    --cnt;  // nums[k] 曾被计入 cnt，k 右移后不再属于 l > k，故减一
                }
            }  // k 扫描结束
        }  // j 扫描结束
        long long ans = 0;  // ans 累计四元组个数，数量级可达 n^4，必须用 long long
        for (int k = 2; k < n - 1; ++k) {  // 枚举第三个下标 k（左侧至少两个位置：k ≥ 2）
            int cnt = 0;  // cnt 统计 i < k 且 nums[i] < nums[k] 的个数
            for (int i = 0; i < k; ++i) {  // 先扫一遍左侧，数出所有满足 nums[i] < nums[k] 的 i
                if (nums[i] < nums[k]) {  // 找到这样一个 i
                    ++cnt;  // 计数加一
                }
            }  // 左侧计数完成，cnt 现在是 j = k-1 时的初始值
            for (int j = k - 1; j > 0; --j) {  // 枚举第二个下标 j，从 k-1 向左扫到 1
                if (nums[j] > nums[k]) {  // nums[j] > nums[k]，满足四元组条件里的 nums[k] < nums[j]
                    g[j][k] = cnt;  // 把当前的左侧计数写入 g[j][k]
                    ans += 1ll * f[j][k] * g[j][k];  // 左右两侧数量相乘后累加（1ll 防止乘法溢出）
                } else {  // 否则 nums[j] < nums[k]
                    --cnt;  // j 向左移出后不再属于 i < j 的左侧，且它被计入过 cnt，故减一
                }
            }
        }
        return ans;  // 返回上升四元组的总数
    }
};