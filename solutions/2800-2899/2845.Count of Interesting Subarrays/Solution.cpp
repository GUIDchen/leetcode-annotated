// 题目：2845. 统计趣味子数组的数目（Count of Interesting Subarrays）
// 思路：把「模 modulo 等于 k」的元素映射成 1、其余映射成 0，趣味条件等价于子数组和在模 modulo 下等于 k；用前缀和 + 哈希表统计。
// 时间复杂度：O(n)，一遍扫描；空间复杂度：O(min(n, modulo))，哈希表最多保存 modulo 种余数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {  // nums：原数组；modulo：取模值；k：目标余数
        int n = nums.size();  // 数组长度
        vector<int> arr(n);  // 0/1 数组：元素模 modulo 等于 k 记 1，否则记 0
        for (int i = 0; i < n; ++i) {  // 逐个元素完成上述 0/1 映射
            arr[i] = int(nums[i] % modulo == k);  // 布尔值转成 0 或 1
        }
        unordered_map<int, int> cnt;  // 哈希表：记录前缀和模 modulo 每个余数出现的次数
        cnt[0] = 1;  // 空前缀的余数视为 0，先记一次，方便统计从下标 0 开始的子数组
        long long ans = 0;  // 答案：满足条件的子数组个数
        int s = 0;  // 当前前缀和
        for (int x : arr) {  // 从左到右扫描 0/1 数组
            s += x;  // 更新前缀和
            ans += cnt[(s - k + modulo) % modulo];  // 需要之前出现过余数为 (s - k) mod modulo 的前缀，这些前缀之后到当前位置都构成趣味子数组
            cnt[s % modulo]++;  // 把当前前缀和的余数计入哈希表，供后面的位置使用
        }
        return ans;  // 返回满足条件的子数组总数
    }
};