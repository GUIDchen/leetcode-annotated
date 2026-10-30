// 题目：2601. 质数减法运算（Prime Subtraction Operation）
// 思路：先筛出 1000 以内全部质数，再从右往左扫描；遇到 nums[i] >= nums[i+1] 就二分找第一个大于二者差值的质数减掉，让 nums[i] 恰好落到右邻之下。
// 时间复杂度：O(1000·k + n·log k)，k 为质数个数；空间复杂度：O(k) 存放质数表。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    bool primeSubOperation(vector<int>& nums) {  // nums：可修改的输入数组，返回能否通过若干次质数减法使其严格递增
        vector<int> p;  // 质数表 p：保存 1000 以内的质数，天然从小到大有序
        for (int i = 2; i <= 1000; ++i) {  // 题目保证 nums[i] <= 1000，枚举到 1000 就够用
            bool ok = true;  // 先假设 i 是质数
            for (int j : p) {  // 用已经筛出的小质数逐个试除
                if (i % j == 0) {  // i 能被某个小质数整除，说明它是合数
                    ok = false;  // 标记为非质数
                    break;  // 已经确定不是质数，提前结束试除
                }
            }
            if (ok) {  // 所有小质数都除不尽，确认 i 是质数
                p.push_back(i);  // 把 i 追加进质数表，供后续使用
            }
        }
        int n = nums.size();  // 数组长度
        for (int i = n - 2; i >= 0; --i) {  // 从右往左处理：右侧元素确定后，左侧允许的上界才唯一
            if (nums[i] < nums[i + 1]) {  // 已经严格小于右邻元素
                continue;  // 无需做减法，直接看前一个位置
            }
            int j = upper_bound(p.begin(), p.end(), nums[i] - nums[i + 1]) - p.begin();  // 二分找第一个大于 nums[i]-nums[i+1] 的质数，只有它能把 nums[i] 压到右邻之下
            if (j == p.size() || p[j] >= nums[i]) {  // j 越界说明没有更大的质数；p[j] >= nums[i] 说明减完会小于等于 0
                return false;  // 这个位置无解，整体不可能成功
            }
            nums[i] -= p[j];  // 减去该质数，使 nums[i] < nums[i + 1] 成立
        }
        return true;  // 所有位置都调整完毕，返回成功
    }
};