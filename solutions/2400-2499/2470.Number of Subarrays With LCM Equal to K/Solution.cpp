// 题目：2470. 最小公倍数等于 K 的子数组数目（Number of Subarrays With LCM Equal to K）
// 核心思路：固定左端点 i，让右端点 j 向右扩展，边扩展边求区间最小公倍数；因为一旦出现不是 k 的约数的元素，区间 lcm 就不可能等于 k，可以直接 break，所以每个左端点只扫到第一个不整除处。
// 时间复杂度：O(n^2·log k)，内层每个 j 做一次 lcm；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int subarrayLCM(vector<int>& nums, int k) {  // nums 是输入数组，k 是目标最小公倍数
        int ans = 0;  // 统计 lcm 恰好等于 k 的子数组个数
        for (int i = 0; i < nums.size(); ++i) {  // 枚举子数组的左端点 i
            int a = 1;  // a 是以 i 开头、向右延伸的子数组当前的 lcm（1 是 lcm 的单位元）
            for (int j = i; j < nums.size(); ++j) {  // 枚举右端点 j，让子数组逐步变长
                if (k % nums[j] != 0) {  // nums[j] 不是 k 的约数，lcm 不可能等于 k
                    break;  // 再往右扩展只会让 lcm 更大，直接结束这一轮
                }
                a = lcm(a, nums[j]);  // 更新当前子数组的最小公倍数
                ans += a == k;  // lcm 正好等于 k 就计数加一（bool 转成 0/1）
            }
        }
        return ans;  // 返回满足条件的子数组个数
    }
};
