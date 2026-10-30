// 题目：1425. 带限制的子序列和（Constrained Subsequence Sum）
// 核心思路：设 f[i] 为以 i 结尾的最大子序列和，转移只依赖前 k 个位置中最大的 f，用单调队列把窗口最值维护成 O(1)。
// 时间复杂度：O(n)，每个下标最多进出队列一次；空间复杂度：O(n)，f 数组与单调队列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int constrainedSubsetSum(vector<int>& nums, int k) {  // nums：原数组；k：相邻被选元素下标差的上限
        deque<int> q = {0};  // 单调队列存候选下标，初始放入 0 号位置作为哨兵
        int n = nums.size();  // 数组长度
        int f[n];  // f[i]：以 i 结尾的合法子序列最大和
        f[0] = 0;  // 哨兵状态：还没选任何元素时和为 0
        int ans = INT_MIN;  // 记录全局最大值，初值取最小整数
        for (int i = 0; i < n; ++i) {  // 从左到右计算每个位置
            while (i - q.front() > k) {  // 队首下标与 i 的距离超过 k 就不能再用来转移
                q.pop_front();  // 弹出过期的队首
            }  // 过期检查结束
            f[i] = max(0, f[q.front()]) + nums[i];  // 可以放弃前面的序列（取 0），也可接上队列里的最优候选
            ans = max(ans, f[i]);  // 用当前状态更新全局最大值
            while (!q.empty() && f[q.back()] <= f[i]) {  // 维护队列内 f 值单调递减
                q.pop_back();  // 队尾比当前更差且下标更小，之后不可能再被选中，弹出
            }  // 单调性维护结束
            q.push_back(i);  // 当前下标入队，供后面的位置转移使用
        }  // 所有位置处理完毕
        return ans;  // 返回所有合法子序列和中的最大值
    }  // 方法结束
};  // 题解类定义结束
