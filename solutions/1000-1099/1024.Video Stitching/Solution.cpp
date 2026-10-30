// 题目：1024. 视频拼接（Video Stitching）
// 思路：先用 last[a] 记录从时刻 a 出发能到达的最远时刻，再按时间轴从左到右贪心：维护已覆盖的最远点 mx 与上一次切片的边界 pre，走完一段就再切一刀。
// 时间复杂度：O(n + time)，n 为片段数；空间复杂度：O(time)，last 数组长度等于 time。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int videoStitching(vector<vector<int>>& clips, int time) {  // clips：每个片段的 [起点, 终点]；time：需要覆盖的区间 [0, time]；返回最少片段数，无法覆盖则返回 -1
        vector<int> last(time);  // last[a] 表示所有从 a 开始的片段中能延伸到的最远时刻；下标只到 time-1 就够
        for (auto& v : clips) {  // 遍历每个片段
            int a = v[0], b = v[1];  // a 是片段起点，b 是片段终点
            if (a < time) {  // 起点已经 >= time 的片段对覆盖 [0, time] 没有帮助，直接忽略（同时避免越界）
                last[a] = max(last[a], b);  // 同一时刻可能有多个片段，只保留能延伸得最远的那一个
            }
        }
        // 贪心维护三个量：mx 当前能覆盖到的最远时刻，ans 已用片段数，pre 当前这一刀切片的起点
        int mx = 0, ans = 0;  // mx：目前能延伸到的最远时刻；ans：最少片段数
        int pre = 0;  // pre：当前这个片段开始生效的时刻（上一次加片段时更新）
        for (int i = 0; i < time; ++i) {  // 沿时间轴从 0 走到 time - 1，逐点推进
            mx = max(mx, last[i]);  // 把从时刻 i 开始的片段能到达的最远点纳入覆盖范围
            if (mx <= i) {  // 最远只能到 i，说明 i 以及之后的时刻无法被覆盖，区间 [0, time] 拼不出来
                return -1;  // 无法完成拼接
            }
            if (pre == i) {  // 走完了上一段能覆盖的全部范围，需要再取一个片段，答案是必须是最少的
                ++ans;  // 片段数加一
                pre = mx;  // 新片段从当前位置生效，覆盖范围推进到 mx
            }
        }
        // 时间轴走完，ans 即覆盖 [0, time] 所需的最少片段数
        return ans;  // 返回最少片段数
    }
};