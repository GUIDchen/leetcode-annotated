// 题目：2442. 反转之后不同整数的数目（Count Number of Distinct Integers After Reverse Operations）【中等】
// 思路：先把原数组放进哈希集合并去重，再对每个数逐位取模弹出、从低位到高位重组成反转数插入集合，最后集合大小就是不同整数个数。
// 时间复杂度：O(n·log10M)，每个数按十进制位数反转，M 为数值大小；空间复杂度：O(n)，集合最多存 2n 个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countDistinctIntegers(vector<int>& nums) {  // nums 是输入数组
        unordered_set<int> s(nums.begin(), nums.end());  // 先用区间构造把原数组放进集合：自动去重，并贡献「原数」这一半答案
        for (int x : nums) {  // 按值拷贝遍历每个数，因此下面修改 x 不会动到 nums 本身
            int y = 0;  // y 用来边算边累积反转后的数
            while (x) {  // 反复取出 x 的最低位，直到 x 被除成 0
                y = y * 10 + x % 10;  // x % 10 取出最低位，接到 y 的末尾（相当于把 y 左移一位十进制）
                x /= 10;  // 整除 10 丢掉刚取走的最低位，为取下一位做准备
            }
            s.insert(y);  // 把反转后的数也加入集合，重复的会被自动忽略
        }
        return s.size();  // 集合大小就是「原数 + 反转数」中不同整数的个数
    }
};