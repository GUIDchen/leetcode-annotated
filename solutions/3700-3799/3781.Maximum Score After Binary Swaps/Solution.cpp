// 题目：3781. 二进制交换后的最大分数（Maximum Score After Binary Swaps）
// 核心思路：操作只能把 '1' 向左移动，因此第 k 个 '1' 最终只能落在它原位置或更左侧；从左到右扫描，把 nums[i] 压入大根堆，遇到 s[i]=='1' 就取走堆中最大值作为该位置的值。
// 复杂度：时间 O(n log n)，每个元素至多入堆出堆各一次；空间 O(n)，堆最多存 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // public 区的方法供判题器调用
    long long maximumScore(vector<int>& nums, string s) {  // 长度为 n 的 nums 与 01 串 s，求操作后所有 s[i]=='1' 位置上的 nums[i] 之和的最大值
        long long ans = 0;  // 累加答案，初值 0
        priority_queue<int> pq;  // 大根堆：保存前缀中尚未分配给某个 '1' 的数字
        for (int i = 0; i < nums.size(); i++) {  // 从左到右扫描，堆里始终是还没被取用的数字
            int x = nums[i];  // 当前位置的数字
            char c = s[i];  // 当前位置在 01 串上的标记
            pq.push(x);  // 先把当前数字放进堆，供它自己或左侧的 '1' 使用
            if (c == '1') {  // 第 k 个 '1' 只能落在原位置或更左侧，故此刻从前缀中挑最大值
                ans += pq.top();  // 取出堆顶最大值累加进答案
                pq.pop();  // 弹出被取用的数字，避免重复使用
            }  // 分支结束
        }  // 扫描结束
        return ans;  // 返回最大得分
    }  // 方法结束
};  // 类定义结束
