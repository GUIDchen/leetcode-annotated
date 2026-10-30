// 题目：2936. 包含相等值数字块的数量（Number of Equal Numbers Blocks）
// 思路：从左到右扫描，每个块的起点用二分找出「第一个与块值不同的下标」，块数加一后直接跳到该位置。
// 时间复杂度：O(b log n)，b 为块的个数、n 为数组长度；空间复杂度：O(1)，只用常数个变量。
/**
 * Definition for BigArray.
 * class BigArray {
 * public:
 *     BigArray(vector<int> elements);
 *     int at(long long index);
 *     long long size();
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countBlocks(BigArray* nums) {  // nums：只能通过 at(index) 与 size() 随机访问的大数组
        int ans = 0;  // 累计相等值块的个数
        using ll = long long;  // 下标是 long long，起个别名少写几个字
        ll n = nums->size();  // 数组总长度
        auto search = [&](ll l) {  // 闭包：返回从下标 l 开始的相等值块之后的下一个位置
            ll r = n;  // 右端点先设为 n 作哨兵，保证整块延伸到末尾时也能正确返回 n
            int x = nums->at(l);  // 该块的基准值
            while (l < r) {  // 标准二分：找第一个值不等于 x 的下标
                ll mid = (l + r) >> 1;  // 取中点，用右移代替除以 2
                if (nums->at(mid) != x) {  // 中点值不同，说明边界在左半侧
                    r = mid;  // 收缩右端点
                } else {  // 中点值仍相同，说明边界在右半侧
                    l = mid + 1;  // 收缩左端点（mid 本身已确认相同，可以跳过）
                }
            }
            return l;  // l == r 即为该块之后的下一个位置
        };  // 闭包定义结束
        for (long long i = 0; i < n; ++ans) {  // 每找到一个块就计数加一，并跳过整块
            i = search(i);  // 直接跳到当前块的右边界
        }
        return ans;  // 返回块的总数
    }
};  // 类定义结束