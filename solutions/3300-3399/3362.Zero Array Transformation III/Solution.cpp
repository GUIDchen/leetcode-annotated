// 题目：3362. 零数组变换 III（Zero Array Transformation III）
// 思路：区间按左端点排序后从左到右扫描，用大根堆维护可用区间的右端点；当前位置减量不足时贪心选用右端点最远的区间（能覆盖最多后续位置），扫描结束后堆中剩余区间数即可删除的最大个数。
// 时间复杂度：O((n+m) log m)，每轮入堆出堆各一次；空间复杂度：O(n+m)，差分数组与堆。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露题解方法
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {  // nums：目标数组；queries：可选的区间操作
        sort(queries.begin(), queries.end());  // 按左端点排序，保证扫描时区间按左端点递增入堆
        priority_queue<int> pq;  // 大根堆，存未使用区间的右端点，堆顶是能覆盖到最远位置的区间
        int n = nums.size();  // 数组长度
        vector<int> d(n + 1, 0);  // 差分数组，记录已选区间造成的减量变化
        int s = 0, j = 0;  // s：当前位置累计可用的减量；j：下一个待入堆区间的下标
        for (int i = 0; i < n; ++i) {  // 从左到右处理每个位置
            s += d[i];  // 差分前缀还原出当前位置的减量
            while (j < queries.size() && queries[j][0] <= i) {  // 左端点不大于 i 的区间都已能覆盖位置 i，全部入堆
                pq.push(queries[j][1]);  // 把区间右端点放进大根堆
                ++j;  // 区间指针后移
            }  // 入堆循环结束
            while (s < nums[i] && !pq.empty() && pq.top() >= i) {  // 减量仍不足，且堆顶区间还能覆盖当前位置，就贪心再多用一个区间
                ++s;  // 当前位置的减量加一
                int end = pq.top();  // 取出覆盖最远的区间右端点
                pq.pop();  // 该区间已被使用，弹出堆
                --d[end + 1];  // 差分收口：从 end+1 起可用减量减一
            }  // 贪心取区间循环结束
            if (s < nums[i]) {  // 堆里已经没有能覆盖当前位置的区间，仍然减不够
                return -1;  // 无解，返回 -1
            }  // if 分支结束
        }  // 主循环结束
        return pq.size();  // 堆中剩余未被使用的区间数就是最多可以删除的个数
    }  // 题解方法结束
};  // 题解类结束
