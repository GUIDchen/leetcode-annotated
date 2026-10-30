// 题目：446. 等差数列划分 II - 子序列（Arithmetic Slices II - Subsequence）
// 思路：动态规划，f[i][d] 表示以 nums[i] 结尾、公差为 d 的等差子序列个数（含长度为 2 的）；枚举 j < i，把 f[j][d] 累加进答案，并把这份计数以公差 d 延续到 i。
// 复杂度：时间复杂度 O(n^2)，枚举所有 (j, i) 数对；空间复杂度 O(n^2)，每个下标一张哈希表、最多 O(n) 个公差。
class Solution {  // 题解类：统计等差子序列个数（长度至少 3）
public:  // 公开部分
    int numberOfArithmeticSlices(vector<int>& nums) {  // nums 是输入数组，返回所有等差子序列的数量
        int n = nums.size();  // 数组长度
        unordered_map<long long, int> f[n];  // f[i][d]：以 nums[i] 结尾、公差为 d 的等差子序列个数（含长度 2 的）
        int ans = 0;  // 答案：长度至少 3 的等差子序列个数
        for (int i = 0; i < n; ++i) {  // 枚举子序列的最后一个元素
            for (int j = 0; j < i; ++j) {  // 枚举子序列的倒数第二个元素
                long long d = 1LL * nums[i] - nums[j];  // 公差；用 long long 防止两数相减溢出 int
                int cnt = f[j][d];  // 以 j 结尾、公差同为 d 的序列，后面接上 i 就都能延长
                ans += cnt;  // 这些序列长度都 >= 2，接上 i 后长度 >= 3，全部计入答案
                f[i][d] += cnt + 1;  // 以 i 结尾、公差 d 的序列数 = 转来的 cnt 个 + 新形成的长度 2 序列 (j, i)
            }  // 倒数第二个元素枚举结束
        }  // 最后一个元素枚举结束
        return ans;  // 返回答案
    }  // numberOfArithmeticSlices 方法结束
};  // Solution 类定义结束