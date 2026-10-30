// 题目：3381. 长度可被 K 整除的子数组的最大元素和（Maximum Subarray Sum With Length Divisible by K）
// 思路：前缀和的经典做法。子数组 (j, i] 长度能被 k 整除 ⟺ i ≡ j (mod k)；用 f[r] 维护 j % k == r 的最小前缀和，遍历 i 时用 s - f[i % k] 更新答案。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(k)，只需要 k 个余数槽位。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解法接口
    long long maxSubarraySum(vector<int>& nums, int k) {  // nums：输入数组；k：子数组长度必须能被它整除
        using ll = long long;  // 定义长整型别名，防止前缀和溢出 int
        ll inf = 1e18;  // 用 1e18 表示「无穷大」
        vector<ll> f(k, inf);  // f[r]：所有下标 j 满足 j % k == r 的前缀和最小值，初始为无穷
        ll ans = -inf;  // 答案初始为负无穷，表示还没有找到可用子数组
        ll s = 0;  // 前缀和 s：s 等于 nums[0..i] 的元素和
        f[k - 1] = 0;  // 想象下标 -1 处有一个空前缀和 0，(-1) % k == k-1，因此初始化 f[k-1] = 0
        for (int i = 0; i < nums.size(); ++i) {  // 枚举前缀的右端点 i
            s += nums[i];  // 累加当前元素，得到前缀和 s
            ans = max(ans, s - f[i % k]);  // 用 s 减去同余类中的最小前缀和，得到长度被 k 整除的子数组和，取最大
            f[i % k] = min(f[i % k], s);  // 把当前前缀和 s 更新到它所属的余数槽位（保留更小的，供以后相减）
        }  // 遍历结束
        return ans;  // 返回最大子数组和
    }  // maxSubarraySum 方法结束
};  // Solution 类定义结束
