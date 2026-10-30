// 题目：3048. 标记所有下标的最早秒数 I（Earliest Second to Mark Indices I）
// 思路：对答案秒数 t 二分；check(t) 先记录每个下标在前 t 秒内最后一次出现的时刻，再按时间顺序模拟「攒减一次数」与「标记」是否可行。
// 时间复杂度：O((n + m) log m)，每次 check 为 O(n + t)、二分 log m 次；空间复杂度：O(n)，last 数组记录最后出现位置。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {  // nums：各下标的初始值；changeIndices：每秒可以操作的下标
        int n = nums.size();  // n 为下标个数，也是需要被全部标记的元素个数
        int last[n + 1];  // last[i]：下标 i 在前 t 秒内最后一次出现的时刻（下标从 1 开始，故开 n+1）
        auto check = [&](int t) {  // 判断「前 t 秒之内能否把所有下标都标记完」
            memset(last, 0, sizeof(last));  // 每轮先清零，避免上一轮遗留的时间信息干扰判断
            for (int s = 0; s < t; ++s) {  // 第一遍：统计前 t 秒中每个下标最后一次出现的位置
                last[changeIndices[s]] = s;  // 覆盖式赋值，循环结束后保存的自然就是最后一次出现的位置
            }  // 最后出现位置的统计结束
            int decrement = 0, marked = 0;  // decrement：已攒下的减一操作次数；marked：已标记的下标个数
            for (int s = 0; s < t; ++s) {  // 第二遍：严格按时间顺序模拟每一秒的操作
                int i = changeIndices[s];  // 第 s 秒只能操作下标 i
                if (last[i] == s) {  // 这是下标 i 的最后一次出现机会，必须在这一秒完成标记
                    if (decrement < nums[i - 1]) {  // 攒下的减一次数不足以把 nums[i-1] 减到 0
                        return false;  // 无法在该时刻标记，说明前 t 秒不够用
                    }  // 可标记性判断结束
                    decrement -= nums[i - 1];  // 花掉 nums[i-1] 次减一操作，把该下标清零
                    ++marked;  // 清零后才能标记，已标记数加一
                } else {  // 不是最后一次出现，这一秒用来攒减一的机会
                    ++decrement;  // 预留一次减一操作，供后面真正标记时抵扣
                }  // 两种情况的处理结束
            }  // 逐秒模拟结束
            return marked == n;  // 所有下标都被标记才算前 t 秒可行
        };  // 闭包 lambda 定义结束

        int m = changeIndices.size();  // m 为可用的总秒数
        int l = 1, r = m + 1;  // 二分答案区间 [1, m+1]，r 取 m+1 作为无解哨兵
        while (l < r) {  // 求最小的可行秒数
            int mid = (l + r) >> 1;  // 取区间中点
            if (check(mid)) {  // 前 mid 秒已经能够全部标记
                r = mid;  // 答案不超过 mid，收缩右边界
            } else {  // 前 mid 秒还标记不完
                l = mid + 1;  // 答案严格大于 mid，收缩左边界
            }  // 判断分支结束
        }  // 二分结束，l 就是最小可行秒数
        return l > m ? -1 : l;  // 超过总秒数说明无解，返回 -1
    }  // 方法结束
};  // 类定义结束