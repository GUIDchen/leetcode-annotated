// 题目：1497. 检查数组对是否可以被 k 整除（Check If Array Pairs Are Divisible by k）
// 思路：按键余数分类计数，余数 i 必须与余数 k-i 数量相等，余数 0 的元素只能两两自配，故个数必须为偶数。
// 时间复杂度：O(n + k)；空间复杂度：O(k)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canArrange(vector<int>& arr, int k) {  // 判断能否把数组两两配对，使每对元素之和都能被 k 整除
        vector<int> cnt(k);  // cnt[r] 记录余数为 r 的元素个数
        for (int& x : arr) {  // 逐个统计元素的余数
            ++cnt[((x % k) + k) % k];  // 先取模再加 k 再取模，把负数余数也映射到 [0, k)
        }  // 统计结束
        for (int i = 1; i < k; ++i) {  // 检查非零余数：i 与 k-i 必须成对出现
            if (cnt[i] != cnt[k - i]) {  // 两边数量不等就无法一一配对
                return false;  // 配对失败
            }  // if 结束
        }  // for 结束
        return cnt[0] % 2 == 0;  // 余数为 0 的元素只能和同类配对，所以总数必须是偶数
    }  // 方法结束
};  // 类定义结束