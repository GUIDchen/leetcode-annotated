// 3431. Minimum Unlocked Indices to Sort Nums / 3431. 对数字排序的最小解锁下标
// 核心思路：先用 3 是否出现在 1 之前判定无解，再统计落在 (first2, last1) 或 (first3, last2) 内的锁定下标。
// 复杂度：时间 O(n)，空间 O(1)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 判题器调用的公有方法
    int minUnlockedIndices(vector<int>& nums, vector<int>& locked) {  // 返回使 nums 非递减有序所需解锁的最少下标个数
        int n = nums.size();  // 数组长度 n
        int first2 = n, first3 = n;  // 记录 2 与 3 第一次出现的位置，初值 n 表示不存在
        int last1 = -1, last2 = -1;  // 记录 1 与 2 最后一次出现的位置，初值 -1 表示不存在

        for (int i = 0; i < n; ++i) {  // 第一遍扫描：统计 1、2、3 各自的首末位置
            if (nums[i] == 1) {  // 遇到数值 1
                last1 = i;  // 更新 1 的最后一次出现位置
            } else if (nums[i] == 2) {  // 遇到数值 2
                first2 = min(first2, i);  // 更新 2 的第一次出现位置
                last2 = i;  // 更新 2 的最后一次出现位置
            } else {  // 遇到数值 3
                first3 = min(first3, i);  // 更新 3 的第一次出现位置
            }
        }  // 第一遍扫描结束

        if (first3 < last1) {  // 若 3 出现在 1 之前，仅靠解除锁定无法排成有序
            return -1;  // 该矛盾无解，返回 -1
        }  // 无解判断结束

        int ans = 0;  // 记录需要解锁的下标个数
        for (int i = 0; i < n; ++i) {  // 第二遍扫描，统计必须解锁的位置
            if (locked[i] == 1 && ((first2 <= i && i < last1) || (first3 <= i && i < last2))) {  // 锁定位置落在 (first2, last1) 或 (first3, last2) 区间内时必须解锁
                ++ans;  // 该下标需要解锁，计数加一
            }
        }

        return ans;  // 返回最少解锁下标数
    }  // 方法结束
};  // 类定义结束
