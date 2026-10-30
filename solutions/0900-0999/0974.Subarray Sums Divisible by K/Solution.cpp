// 题目：974. 和可被 K 整除的子数组（Subarray Sums Divisible by K）
// 思路：前缀和模 k 同余的两个位置之间，子数组和必被 k 整除，用哈希表统计同余前缀和出现次数。
// 时间复杂度：O(n)，一次遍历；空间复杂度：O(k)，哈希表最多存 k 种余数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int subarraysDivByK(vector<int>& nums, int k) {  // nums：输入数组；k：除数，返回和能被 k 整除的连续子数组个数
        unordered_map<int, int> cnt{{0, 1}};  // cnt 记录「前缀和模 k 的余数 → 出现次数」，余数 0 已出现 1 次（空前缀）
        int ans = 0, s = 0;  // ans 计数答案，s 保存当前前缀和模 k 的余数
        for (int& x : nums) {  // 逐个元素遍历，用引用避免拷贝
            s = ((s + x) % k + k) % k;  // 把余数统一到 [0, k) 区间：C++ 的 % 对负数结果为负，所以先加 k 再取模
            ans += cnt[s]++;  // 此前出现过 cnt[s] 次相同余数，就能与当前位置组成 cnt[s] 个合法子数组，然后本余数次数加一
        }  // for 循环结束
        return ans;  // 返回统计到的子数组总数
    }  // 题解方法结束
};  // Solution 类结束