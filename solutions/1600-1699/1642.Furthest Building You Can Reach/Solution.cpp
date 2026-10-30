// 题目：1642. 可以到达的最远建筑（Furthest Building You Can Reach）
// 思路：贪心 + 小顶堆，把每个上坡差值先记作「用梯子」，堆内数量超过梯子数时弹出最小差值改用砖块支付（梯子留给更大的跳跃）。
// 时间复杂度：O(n log n)，每个差值入堆出堆各一次；空间复杂度：O(n)，堆最多保存 n-1 个差值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外开放
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {  // heights：楼层高度；bricks：砖块数；ladders：梯子数，返回能到达的最远建筑下标
        priority_queue<int, vector<int>, greater<int>> q;  // 小顶堆：维护所有交给梯子支付的上坡差值，堆顶是最小的那个
        int n = heights.size();  // 建筑总数
        for (int i = 0; i < n - 1; ++i) {  // 逐个检查相邻两栋楼，最后一栋没有「下一栋」，无需前进
            int a = heights[i], b = heights[i + 1];  // a 是当前楼高，b 是下一栋楼的高度
            int d = b - a;  // 高度差，正数表示需要往上爬
            if (d > 0) {  // 只有上坡才消耗资源，下坡或持平可以直接走
                q.push(d);  // 先假设这一跳用梯子，把差值放进堆
                if (q.size() > ladders) {  // 梯子用超了，说明必须有一跳改付砖块
                    bricks -= q.top();  // 弹出最小的差值，改用砖块支付（梯子留给更大的跳跃）
                    q.pop();  // 把这个差值真正从堆中移除
                    if (bricks < 0) {  // 砖块已经透支，说明到不了下一栋
                        return i;  // 只能停在当前这栋楼
                    }  // 砖块不足分支结束
                }  // 梯子数量调整结束
            }  // 上坡处理结束
        }  // 相邻关系遍历结束
        return n - 1;  // 所有跳跃都能完成，能到达最后一栋
    }  // 方法结束
};  // 类定义结束