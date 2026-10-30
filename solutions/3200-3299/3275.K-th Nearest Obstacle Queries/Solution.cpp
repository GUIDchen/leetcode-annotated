// 题目：3275. 第 K 近障碍物查询（K-th Nearest Obstacle Queries）
// 思路：用大根堆维护当前最近的 k 个曼哈顿距离，堆顶就是这 k 个里最远的，也就是第 k 近的距离。
// 时间复杂度：O(q log k)，每个查询入堆、出堆各一次；空间复杂度：O(k)，堆中最多保留 k 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> resultsArray(vector<vector<int>>& queries, int k) {  // queries：障碍物坐标；k：查询的是第 k 近
        vector<int> ans;  // 保存每个查询的答案
        priority_queue<int> pq;  // 大根堆，只保留当前最近的 k 个距离，堆顶是这 k 个中的最大值
        for (const auto& q : queries) {  // 依次加入每个障碍物并回答一次查询
            int x = abs(q[0]) + abs(q[1]);  // 该障碍物到原点的曼哈顿距离
            pq.push(x);  // 把距离放进堆
            if (pq.size() > k) {  // 堆中元素超过 k 个
                pq.pop();  // 弹出最远的，保证堆里始终是最近的 k 个
            }
            ans.push_back(pq.size() == k ? pq.top() : -1);  // 凑够 k 个时返回第 k 近，否则返回 -1
        }
        return ans;  // 返回所有查询的答案
    }
};
