// 题目：3264. K 次乘运算后的最终数组 I（Final Array State After K Multiplication Operations I）
// 思路：用小根堆维护元素下标，比较规则为「数值小者优先，数值相同则下标小者优先」；每次取出堆顶（当前最小值）乘以 multiplier 后重新入堆，重复 k 次即得最终数组。
// 时间复杂度：O(n + k log n)，建堆 O(n)、每次操作 O(log n)；空间复杂度：O(n)，堆中始终保存 n 个下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外公开
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {  // nums 为初始数组，k 为操作次数，multiplier 为每次所乘的数；返回操作后的数组
        auto cmp = [&nums](int i, int j) {  // 定义小根堆的比较器：按下标比较，实际比的是它们对应的数值
            return nums[i] == nums[j] ? i > j : nums[i] > nums[j];  // 数值不同就比数值；数值相同则比下标，保证并列时下标更小的元素优先
        };  // lambda 比较器定义结束
        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);  // 存放数组下标的小根堆，堆顶即当前最小元素的下标

        for (int i = 0; i < nums.size(); ++i) {  // 把所有下标入堆
            pq.push(i);  // 下标 i 入堆
        }  // 建堆完成

        while (k--) {  // 重复 k 次乘法操作（k-- 递减到 0 为止）
            int i = pq.top();  // 取出堆顶，即当前最小元素的下标
            pq.pop();  // 把该下标从堆中弹出
            nums[i] *= multiplier;  // 最小值乘以 multiplier
            pq.push(i);  // 修改后的下标重新入堆，供下一轮继续取最小
        }  // 本轮操作结束

        return nums;  // 返回 k 次操作后的最终数组
    }  // 方法结束
};  // 类定义结束
