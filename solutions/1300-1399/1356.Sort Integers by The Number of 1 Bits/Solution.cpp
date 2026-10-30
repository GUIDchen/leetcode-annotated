// 题目：1356. 根据数字二进制下 1 的数目排序（Sort Integers by The Number of 1 Bits）
// 思路：把「1 的个数」编码进高位（乘 100000）当作第一关键字，直接整体排序后再取模还原原值。
// 时间复杂度：O(n log n)，排序为主；空间复杂度：O(log n)，排序递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> sortByBits(vector<int>& arr) {  // 按二进制中 1 的个数升序排序，个数相同则按数值升序
        for (int& x : arr) {  // 用引用遍历，直接原地改写每个元素
            x += __builtin_popcount(x) * 100000;  // 把 1 的个数放大 100000 倍加到原值上：高位成为第一关键字，低 17 位保留原值作为第二关键字
        }  // 编码完成
        ranges::sort(arr);  // C++20 ranges 版排序，按编码后的整体数值升序（等价于双关键字排序）
        for (int& x : arr) {  // 再遍历一次，把高位编码去掉
            x %= 100000;  // 对 100000 取模即取回原始数值
        }  // 还原完成
        return arr;  // 返回原地修改后的 arr
    }  // sortByBits 结束
};  // 类定义结束
