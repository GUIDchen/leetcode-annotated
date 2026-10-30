// 题目：888. 公平的糖果交换（Fair Candy Swap）
// 思路：设两人总量差的一半为 diff，交换后必须满足 a - b = diff；枚举 Alice 的一颗糖 a，在 Bob 的集合里查 a - diff 是否存在。
// 时间复杂度：O(n + m)，求和、建集合、枚举各线性一次；空间复杂度：O(m)，Bob 糖果值的哈希集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> fairCandySwap(vector<int>& aliceSizes, vector<int>& bobSizes) {  // aliceSizes / bobSizes 分别是两人每颗糖的大小
        int s1 = accumulate(aliceSizes.begin(), aliceSizes.end(), 0);  // 累加 Alice 的糖果总量
        int s2 = accumulate(bobSizes.begin(), bobSizes.end(), 0);  // 累加 Bob 的糖果总量
        int diff = (s1 - s2) >> 1;  // 交换后两人相等，等价于 a - b = (s1 - s2) / 2，右移一位即除以 2
        unordered_set<int> s(bobSizes.begin(), bobSizes.end());  // 用哈希集合保存 Bob 的所有糖果大小，便于 O(1) 查询
        vector<int> ans;  // 保存答案 [a, b]
        for (int& a : aliceSizes) {  // 枚举 Alice 要换出的那颗糖 a
            int b = a - diff;  // 由 a - b = diff 反解出需要从 Bob 换来的 b
            if (s.count(b)) {  // Bob 恰好拥有大小为 b 的糖果，交换即可配平
                ans = vector<int>{a, b};  // 记录这一对答案
                break;  // 题目保证有解，找到就可以退出循环
            }  // 分支结束
        }  // 枚举结束
        return ans;  // 返回找到的交换方案
    }  // 方法结束
};  // 类定义结束
