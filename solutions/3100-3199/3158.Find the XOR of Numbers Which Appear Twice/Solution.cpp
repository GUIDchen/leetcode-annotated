// 题目：3158. 求出出现两次数字的 XOR 值（Find the XOR of Numbers Which Appear Twice）
// 核心思路：用大小为 51 的计数数组统计每个值出现的次数（值域 1..50），某值计数恰好变成 2 时把它异或进答案，第三次及以后不再重复异或。
// 时间复杂度：O(n)，每个元素只做一次自增与判等；空间复杂度：O(1)，计数数组固定 51 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int duplicateNumbersXOR(vector<int>& nums) {  // nums：输入数组，值域为 1..50
        int cnt[51]{};  // 计数数组，下标即元素值；{} 保证全部初始化为 0
        int ans = 0;  // 答案的异或累加器，0 是异或的单位元
        for (int x : nums) {  // 遍历每个元素
            if (++cnt[x] == 2) {  // 先自增计数，再判断是否刚好第二次出现（第三次不会再命中）
                ans ^= x;  // 把出现两次的值异或进答案
            }  // if 结束
        }  // 遍历结束
        return ans;  // 返回答案
    }  // 方法结束
};  // 类定义结束