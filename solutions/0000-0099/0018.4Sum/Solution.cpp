// 题目：18. 四数之和（4Sum）
// 思路：先排序，再枚举前两个数 i、j（跳过重复），后两个数用左右双指针 k、l 相向收缩；四数相加转 long long 防止溢出。
// 时间复杂度：O(n^3)，两层枚举加一次双指针扫描；空间复杂度：O(1)，不计排序与答案本身占用的空间。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> fourSum(vector<int>& nums, int target) {  // nums：输入数组（会被就地排序）；target：目标和
        int n = nums.size();  // 元素个数，后面用来定循环上界和双指针右端
        vector<vector<int>> ans;  // 收集所有互不相同的四元组
        if (n < 4) {  // 不足 4 个数，凑不出四元组
            return ans;  // 直接返回空答案
        }
        sort(nums.begin(), nums.end());  // 排序后数组有序才能用双指针，同时让相同元素相邻便于去重
        for (int i = 0; i < n - 3; ++i) {  // 枚举第一个数，至少给后面留 3 个位置
            if (i && nums[i] == nums[i - 1]) {  // 与下标 i-1 的值相同，同一组答案会重复产出
                continue;  // 跳过这个重复的起点
            }
            for (int j = i + 1; j < n - 2; ++j) {  // 枚举第二个数，至少给 k、l 留 2 个位置
                if (j > i + 1 && nums[j] == nums[j - 1]) {  // j 是内层起点时不能跳过；其余情况与上一个相同就去重
                    continue;  // 跳过重复的第二个数
                }
                int k = j + 1, l = n - 1;  // 双指针：k 从左往右增大和，l 从右往左减小和
                while (k < l) {  // 两指针未相遇就还没枚举完
                    long long x = (long long) nums[i] + nums[j] + nums[k] + nums[l];  // 四数之和，强转 long long 避免 int 相加溢出
                    if (x < target) {  // 当前和偏小
                        ++k;  // 左指针右移，使和变大
                    } else if (x > target) {  // 当前和偏大
                        --l;  // 右指针左移，使和变小
                    } else {  // 恰好等于 target，得到一个合法四元组
                        ans.push_back({nums[i], nums[j], nums[k++], nums[l--]});  // 记录答案，并把两个指针同时内移一步
                        while (k < l && nums[k] == nums[k - 1]) {  // 跳过与刚用过的 k 相同的值，避免重复答案
                            ++k;  // 继续右移
                        }
                        while (k < l && nums[l] == nums[l + 1]) {  // 跳过与刚用过的 l 相同的值，避免重复答案
                            --l;  // 继续左移
                        }
                    }
                }
            }
        }
        return ans;  // 返回全部不重复的四元组
    }
};
