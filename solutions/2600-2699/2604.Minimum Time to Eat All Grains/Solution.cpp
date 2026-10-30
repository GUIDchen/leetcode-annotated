// 题目：2604. 吃掉所有谷子的最短时间（Minimum Time to Eat All Grains）
// 思路：二分答案 t，check(t) 按位置顺序贪心 —— 每只母鸡先吃掉左侧近处谷子，必要时折返向右，判断能否在 t 内吃完全部谷子。
// 时间复杂度：O((n + m) log C)，C 为时间上界；空间复杂度：O(1) 额外空间（排序自身 O(log) 栈）。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int minimumTime(vector<int>& hens, vector<int>& grains) {  // hens：母鸡位置；grains：谷子位置；返回吃完所有谷子的最短时间
        int m = grains.size();  // 谷子数量
        sort(hens.begin(), hens.end());  // 母鸡位置排序，固定从左到右的分配顺序
        sort(grains.begin(), grains.end());  // 谷子位置排序，保证处理顺序单调
        int l = 0;  // 二分下界：时间最小为 0
        int r = abs(hens[0] - grains[0]) + grains[m - 1] - grains[0];  // 二分上界：从最左母鸡出发扫完最左到最右谷子的一种可行耗时
        auto check = [&](int t) -> bool {  // 判定函数：给定时间 t，判断能否吃完全部谷子
            int j = 0;  // j 是下一颗还没吃到的谷子下标
            for (int x : hens) {  // 按位置顺序，让每只母鸡覆盖尽可能多的谷子
                if (j == m) {  // 所有谷子都吃完了
                    return true;  // 提前返回可行，省掉后续母鸡的判断
                }
                int y = grains[j];  // 下一颗待吃谷子的位置
                if (y <= x) {  // 谷子在母鸡左侧或就在脚下
                    int d = x - y;  // d：母鸡需要向左走的距离
                    if (d > t) {  // 走到最左那颗谷子就已超时
                        return false;  // 该时间不可行，直接失败
                    }
                    while (j < m && grains[j] <= x) {  // 先吃掉母鸡左侧紧邻、无需折返的谷子
                        ++j;  // 向右推进待吃下标
                    }
                    while (j < m && min(d, grains[j] - x) + grains[j] - y <= t) {  // 左侧吃完后折返向右：用 min(左行距离, 右侧距离) 判断折返总耗时
                        ++j;  // 仍在时间预算内就继续向右覆盖
                    }
                } else {  // 谷子都在母鸡右侧，只需一路向右
                    while (j < m && grains[j] - x <= t) {  // 距离不超过 t 就能覆盖
                        ++j;  // 继续向右吃
                    }
                }
            }
            return j == m;  // 所有母鸡用完，检查是否已经吃完全部谷子
        };
        while (l < r) {  // 二分最短可行时间
            int mid = (l + r) >> 1;  // 取中点，右移一位等价于除以 2
            if (check(mid)) {  // mid 时间内能吃完
                r = mid;  // 收缩上界，继续尝试更短的时间
            } else {
                l = mid + 1;  // mid 时间内吃不完，答案至少是 mid + 1
            }
        }
        return l;  // 循环结束时 l == r，即最小可行时间
    }
};