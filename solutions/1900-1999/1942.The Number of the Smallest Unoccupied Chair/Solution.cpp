// 题目：1942. 最小未被占据椅子的编号（The Number of the Smallest Unoccupied Chair）
// 思路：按到达时间排序后用两个小根堆模拟：busy 存 (离开时间, 椅子编号)，idle 存当前空闲的椅子编号；每来一人先把已离开者的椅子还回 idle，再取编号最小的空闲椅子。
// 时间复杂度：O(n log n)，排序与堆操作；空间复杂度：O(n)，两个堆与 times 的扩展字段。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int smallestChair(vector<vector<int>>& times, int targetFriend) {  // times：每位朋友的 (到达, 离开) 时刻；targetFriend：目标朋友的下标
        using pii = pair<int, int>;  // 给 pair<int, int> 起别名，减少重复书写
        priority_queue<pii, vector<pii>, greater<pii>> busy;  // 小根堆 busy：(离开时间, 椅子编号)，离开最早的在堆顶
        priority_queue<int, vector<int>, greater<int>> idle;  // 小根堆 idle：当前空闲的椅子编号，编号最小的在堆顶
        int n = times.size();  // n 是朋友数，也等于椅子数（每人一把椅子足够）
        for (int i = 0; i < n; ++i) {  // 给每个人补上原始下标，排序后仍能认出是谁
            times[i].push_back(i);  // 把下标追加为第三个字段
            idle.push(i);  // 初始时 0..n-1 号椅子全部空闲
        }
        ranges::sort(times);  // ranges::sort 按到达时间升序处理（到达时间互不相同）
        for (const auto& e : times) {  // 按到达时间从早到晚依次安排每位朋友
            int arrival = e[0], leaving = e[1], i = e[2];  // 取出到达时刻、离开时刻和原始下标
            while (!busy.empty() && busy.top().first <= arrival) {  // 先释放所有「在他到达时已经离开」的人占用的椅子
                idle.push(busy.top().second);  // 离开时刻不晚于本次到达，这把椅子此刻已空出来，还回空闲堆
                busy.pop();  // 从 busy 堆移除这条占用记录，避免重复释放
            }
            int j = idle.top();  // 取编号最小的空闲椅子给他
            if (i == targetFriend) {  // 当前处理的正是目标朋友
                return j;  // 直接返回他坐到的椅子编号
            }
            idle.pop();  // 不是目标朋友，椅子从此被占用，从空闲堆弹出
            busy.emplace(leaving, j);  // 登记该椅子的释放时刻，等时刻到了再还回空闲堆
        }
        return -1;  // 遍历结束仍未返回属于异常情况，题目保证有解，返回 -1 兜底
    }
};
