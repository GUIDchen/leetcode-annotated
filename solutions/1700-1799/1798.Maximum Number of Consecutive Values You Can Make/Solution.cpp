// 题目：1798. 你能构造出连续值的最大数目（Maximum Number of Consecutive Values You Can Make）
// 思路：把硬币升序排序，维护「[0, ans-1] 都能凑出」的不变式；当前硬币 v <= ans 时区间可无缝扩展到 [0, ans+v-1]，否则出现空缺直接停止。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(1)，只用了几个变量（排序本身的栈空间不计）。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    int getMaximumConsecutive(vector<int>& coins) {  // coins：可用硬币面值（每个最多用一次），返回能连续构造出的最大值个数
        sort(coins.begin(), coins.end());  // 升序排序，保证从小到大扩展可构造区间
        int ans = 1;  // 不变式：[0, ans-1] 全部可构造，初始只有 0，所以 ans = 1
        for (int& v : coins) {  // 从小到大遍历每个面值
            if (v > ans) break;  // 面值大于区间右端 +1 就会出现缝隙，后面更大的面值更不可能接上
            ans += v;  // 区间从 [0, ans-1] 扩展成 [0, ans+v-1]，依然连续
        }  // for 结束
        return ans;  // 返回连续构造的个数
    }  // 方法结束
};  // 类定义结束