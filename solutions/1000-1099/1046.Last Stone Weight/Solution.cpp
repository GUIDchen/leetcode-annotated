// 题目：1046. 最后一块石头的重量（Last Stone Weight）
// 思路：用大根堆反复取出最重与次重的两块石头对撞，重量相等则两块同时粉碎，否则把差值放回堆中，直到堆里不足两块。
// 时间复杂度：O(n log n)，每块石头最多入堆出堆常数次，堆操作 O(log n)；空间复杂度：O(n)，堆最多保存 n 块石头。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int lastStoneWeight(vector<int>& stones) {  // stones：每块石头的重量；返回最后剩下的重量（全碎光则为 0）
        priority_queue<int> pq;  // 大根堆：每次都 O(1) 取到最重的石头
        for (int x : stones) {  // 把所有石头重量入堆
            pq.push(x);  // push 会自底向上维护堆序
        }  // 入堆结束
        while (pq.size() > 1) {  // 堆里不足两块时就没有可对撞的石头了
            int y = pq.top();  // 取最重的一块 y
            pq.pop();  // 把它从堆中删除
            int x = pq.top();  // 取次重的一块 x，此时 x <= y
            pq.pop();  // 同样从堆中删除
            if (x != y) {  // 重量相同则两块一起粉碎，不产生新石头
                pq.push(y - x);  // 否则产生重量为 y - x 的新石头，放回堆里继续参与对撞
            }  // 分支结束
        }  // 对撞循环结束
        return pq.empty() ? 0 : pq.top();  // 堆空说明全部碎光返回 0，否则堆顶就是最后一块的重量
    }  // 方法结束
};  // 题解类结束