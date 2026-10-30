// 题目：2856. 删除数对后的最小数组长度（Minimum Array Length After Pair Removals）
// 核心思路：每次删除出现次数最多的两种不同值各一个，用大根堆模拟，删除次数最多则剩余长度最少。
// 时间复杂度：O(n + m log m)，m 为不同值的个数；空间复杂度：O(m)。
class Solution {  // LeetCode 约定的题解类
public:  // 对外公开的接口区域
    int minLengthAfterRemovals(vector<int>& nums) {  // nums 为有序数组，可删除任意两个不同值的元素
        unordered_map<int, int> cnt;  // 统计每个值出现的次数
        for (int x : nums) {  // 遍历数组
            ++cnt[x];  // 对应值的计数加一
        }  // 结束 for 循环
        priority_queue<int> pq;  // 大根堆，堆顶是当前剩余个数最多的那种值
        for (auto& [_, v] : cnt) {  // 把每种值的出现次数入堆（键用 _ 占位）
            pq.push(v);  // 次数入堆
        }  // 结束 for 循环
        int ans = nums.size();  // 剩余元素个数，初始为数组长度
        while (pq.size() > 1) {  // 只要还剩至少两种不同的值就能继续配对删除
            int x = pq.top();  // 取出个数最多的那种值
            pq.pop();  // 弹出堆顶
            int y = pq.top();  // 取出个数第二多的那种值
            pq.pop();  // 弹出堆顶
            x--;  // 两个值各消耗一个元素
            y--;  // 同上
            if (x > 0) {  // 还有剩余就放回堆里继续参与配对
                pq.push(x);  // 放回堆
            }  // 结束 if 分支
            if (y > 0) {  // 第二种值同理
                pq.push(y);  // 放回堆
            }  // 结束 if 分支
            ans -= 2;  // 一次配对删掉两个元素
        }  // 结束 while 循环
        return ans;  // 返回剩下的元素个数
    }  // 结束函数体
};  // 结束类定义