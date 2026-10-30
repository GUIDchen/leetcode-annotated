// 3974. Maximum Total Sum of K Selected Elements | K 个元素的最大总和（中等）
// 核心思路：要挑 k 个元素并各配一个系数，越大的元素越该配越大的系数，于是先升序排序，再从末尾往前取 k 个元素，第 t 个（从 0 数）配的系数是 max(1, mul - t)，累加即答案。
// 复杂度：时间 O(n log n)，主要是排序；空间 O(log n)，为排序的递归栈开销（返回答案只用常数变量）。
class Solution {  // 定义题解类
public:  // 公有接口
    long long maxSum(vector<int>& nums, int k, int mul) {  // 返回按规则选 k 个元素能得到的最大总和
        sort(nums.begin(), nums.end());  // 升序排序，方便从最大值开始贪心
        int n = nums.size();  // 数组长度
        long long ans = 0;  // 累加的总和，用 long long 防溢出

        for (int i = n - 1; i >= n - k; --i) {  // 从最大的元素开始，倒着取 k 个（下标 n-1 到 n-k）
            int m = max(1, mul);  // 当前元素可用的系数，至少为 1；mul 递减到 0 或负数后都按 1 计
            ans += 1LL * nums[i] * m;  // 大元素配大系数，乘积计入总和（1LL 保证按 64 位相乘）
            mul--;  // 系数减一，留给下一个更小的元素
        }  // 选取结束

        return ans;  // 返回最大总和
    }  // 方法结束
};  // 类定义结束