// 题目：2126. 摧毁小行星（Destroying Asteroids）
// 核心思路：贪心——按质量升序排序后能吞就吞；最小的都吞不下时，其余更大的更吞不下，可直接判否。
// 时间复杂度：O(n log n)，由排序主导；空间复杂度：O(log n)，排序递归栈（不计输入本身）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {  // mass 是初始质量；asteroids 是各小行星质量；返回能否全部摧毁
        ranges::sort(asteroids);  // 升序排序：先吃小的让质量增长最快，这是贪心策略正确的前提
        long long m = mass;  // 用 long long 保存当前质量，避免累加后超出 int 范围
        for (int x : asteroids) {  // 从小到大依次尝试吞掉每颗小行星
            if (m < x) {  // 当前质量小于这颗小行星的质量，说明吞不下
                return false;  // 已按最小优先尝试仍失败，后续更大的更不可能吞下，返回 false
            }  // if 语句块结束
            m += x;  // 吞下成功，质量增加这颗小行星的质量
        }
        return true;  // 全部小行星都被吞掉，返回 true
    }
};
