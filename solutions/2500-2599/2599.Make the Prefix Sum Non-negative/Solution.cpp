// 题目：2599. 使前缀和数组非负（Make the Prefix Sum Non-negative）
// 思路：边扫边累加前缀和，前缀和变负时把见过的负数最小值（小根堆堆顶）挪到数组末尾，相当于从当前前缀和中「减掉」它。
// 时间复杂度：O(n log n)，每个负数最多进出堆一次；空间复杂度：O(n)，最坏把所有负数都存进堆。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int makePrefSumNonNegative(vector<int>& nums) {  // nums：原数组；返回使所有前缀和都非负所需的最少移动次数
        priority_queue<int, vector<int>, greater<int>> pq;  // 小根堆存放当前已遇到的负数，堆顶是最小（绝对值最大）的那个，优先挪走它最划算
        int ans = 0;  // 记录移动次数
        long long s = 0;  // 前缀和用 long long，避免累加过程溢出 int
        for (int& x : nums) {  // 按原顺序遍历数组，前缀和必须按这个顺序保持非负
            s += x;  // 把当前元素计入前缀和
            if (x < 0) {  // 负数才可能拖累前缀和，先攒进小根堆
                pq.push(x);  // 压入堆中，供后面需要时挪走
            }  // 当前前缀和已经为负，必须挪走一些负数才能修复
            while (s < 0) {  // 每次挪走堆顶（最小负数），它对前缀和的拖累最大，挪走最省次数
                s -= pq.top();  // 注意是 s -= 负数，等价于把该负数从当前前缀和中剔除
                pq.pop();  // 弹出已挪走的元素
                ++ans;  // 移动次数加一
            }  // 修复到前缀和非负为止
        }  // 本元素处理完毕
        return ans;  // 返回总移动次数
    }
};