// 题目：3224. 使差值相等的最少数组改动次数（Minimum Array Changes to Make Differences Equal）
// 思路：枚举目标差值 t，用差分数组累计每对 (x,y) 的代价：t=y-x 为 0，t<=max(y,k-x) 且 t!=x-y 为 1，其余为 2；前缀和的最小值即答案。
// 时间复杂度：O(n + k)，遍历数组与差分数组各一次；空间复杂度：O(k)，差分数组长度为 k+2。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外公开
    int minChanges(vector<int>& nums, int k) {  // nums：输入数组（长度 n 为偶数）；k：元素可改成 0..k 的任意整数
        int d[k + 2];  // 差分数组覆盖目标差值 0..k，多开两位给 +1 操作留出边界
        memset(d, 0, sizeof(d));  // 差分数组整体清零
        int n = nums.size();  // 数组长度
        for (int i = 0; i < n / 2; ++i) {  // 每一对对称下标 (i, n-1-i) 独立地贡献代价
            int x = min(nums[i], nums[n - i - 1]);  // 取出这对元素中的较小值 x
            int y = max(nums[i], nums[n - i - 1]);  // 取出这对元素中的较大值 y
            d[0] += 1;  // 任意目标差值的基础代价是 1 次修改
            d[y - x] -= 1;  // t 恰好等于原差值 y-x 时不用修改，代价减 1
            d[y - x + 1] += 1;  // 越过原差值后代价恢复为 1
            d[max(y, k - x) + 1] -= 1;  // 在单次修改能凑出的最大差值 m 之后，先减 1 ...
            d[max(y, k - x) + 1] += 2;  // ... 再加 2，两句净增 1：超过 m 就必须改两个数，代价升到 2
        }  // 所有对称对处理完毕
        int ans = n, s = 0;  // ans 以「最多改 n 次」为上界；s 是差分数组的前缀和
        for (int x : d) {  // 扫描每个目标差值 t（包含多开的一位，不影响最小值的正确性）
            s += x;  // 前缀和还原出「把所有差值都改成 t」所需的总修改次数
            ans = min(ans, s);  // 取所有目标差值中的最少修改次数
        }  // 目标差值枚举结束
        return ans;  // 返回最少修改次数
    }  // 方法结束
};