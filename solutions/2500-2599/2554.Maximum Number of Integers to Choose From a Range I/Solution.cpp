// 题目：2554. 从一个范围内选择最多整数 I（Maximum Number of Integers to Choose From a Range I）
// 思路：禁用值放进哈希集合，从 1 到 n 从小到大贪心选取（选最小的数最省总和），循环条件里同时守住总和不超 maxSum。
// 时间复杂度：O(bannedSize + n)，建集合加一次线性枚举，每次查询 O(1)；空间复杂度：O(bannedSize)，哈希集合存放禁用值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxCount(vector<int>& banned, int n, int maxSum) {  // banned 是禁用数字，n 是范围上界，maxSum 是所选数字之和的上限
        unordered_set<int> ban(banned.begin(), banned.end());  // 用哈希集合去重，并提供 O(1) 的成员查询
        int ans = 0, s = 0;  // ans 是已选个数，s 是已选数字的总和
        for (int i = 1; i <= n && s + i <= maxSum; ++i) {  // 从小到大枚举，s + i <= maxSum 保证不会超限，超了自动退出
            if (!ban.count(i)) {  // 当前数字不在禁用集合里，说明可以选
                ++ans;  // 选取个数加一
                s += i;  // 累加到已选总和
            }  // 禁用判断结束
        }  // 枚举结束（超限时由循环条件退出）
        return ans;  // 返回最多能选的整数个数
    }  // maxCount 方法结束
};  // Solution 类定义结束