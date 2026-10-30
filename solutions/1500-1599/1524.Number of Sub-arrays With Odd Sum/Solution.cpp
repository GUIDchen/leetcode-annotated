// 题目：1524. 和为奇数的子数组数目（Number of Sub-arrays With Odd Sum）
// 核心思路：子数组和 = 两个前缀和之差；前缀和奇偶性不同时差为奇数。用 cnt[0]/cnt[1] 记录已出现的前缀和奇偶个数即可。
// 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numOfSubarrays(vector<int>& arr) {  // arr：输入数组，返回和为奇数的子数组个数（结果对 1e9+7 取模）
        const int mod = 1e9 + 7;  // 取模用的常数
        int cnt[2] = {1, 0};  // cnt[0]、cnt[1] 分别是前缀和为偶数、奇数的个数；空前缀（和为 0）算一个偶数前缀
        int ans = 0, s = 0;  // ans 为答案，s 为当前前缀和（只关心它的奇偶性）
        for (int x : arr) {  // 遍历每个元素
            s += x;  // 累加前缀和
            ans = (ans + cnt[s & 1 ^ 1]) % mod;  // s&1 是当前前缀和奇偶，^1 取反表示「相反奇偶」的前缀个数；& 的优先级高于 ^
            ++cnt[s & 1];  // 把当前前缀和的奇偶计入计数，供后续元素使用
        }  // 循环结束
        return ans;  // 返回取模后的答案
    }  // 方法结束
};  // 类定义结束