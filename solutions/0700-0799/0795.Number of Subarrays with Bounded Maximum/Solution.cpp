// 题目：795. 区间子数组个数（Number of Subarrays with Bounded Maximum）
// 思路：用容斥，把「最大值在 [left, right] 内」转化为「最大值 <= right」减去「最大值 <= left-1」。对固定上界 x，线性扫描并维护以当前元素结尾的合法子数组数 t，累加即得答案。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(1)，只用常数个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {  // nums：原数组；left、right：子数组最大值的允许区间
        auto f = [&](int x) {  // f(x)：最大值不超过 x 的连续子数组个数
            int cnt = 0, t = 0;  // cnt 是子数组总数，t 是以当前位置结尾的连续合法段长度
            for (int& v : nums) {  // 从左到右扫描每个元素
                t = v > x ? 0 : t + 1;  // 元素超过上界时合法段被切断，t 归零；否则可以继续延长
                cnt += t;  // 以当前位置结尾的 t 个子数组都合法，全部累加
            }  // 扫描结束
            return cnt;  // 返回最大值 <= x 的子数组数
        };  // f 结束
        return f(right) - f(left - 1);  // 容斥：最大值 <= right 的数量减去最大值 <= left-1 的数量
    }  // numSubarrayBoundedMax 结束
};  // 类定义结束