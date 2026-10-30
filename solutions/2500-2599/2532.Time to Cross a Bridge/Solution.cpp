// 题目：2532. 过桥的时间（Time to Cross a Bridge）
// 核心思路：时间离散模拟。按往返过桥耗时升序排序后用大根堆存两侧等待者（下标越大越慢、越优先），小根堆存两侧正在搬箱子的完成时刻；右岸回程优先于左岸去程，无人可过桥时把时钟快进到最早完成时刻。
// 时间复杂度：O(k log k + (n + k) log k)，共 O(n + k) 次过桥、每次常数次堆操作；空间复杂度：O(k)，四个堆最多存 k 个工人。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findCrossingTime(int n, int k, vector<vector<int>>& time) {  // n 为待搬箱子数、k 为工人数；time[i] = {左到右, 捡箱, 右到左, 放箱} 耗时，返回搬完全部箱子的时刻
        using pii = pair<int, int>;  // 别名：工作堆里存的是「完成时刻, 工人下标」
        for (int i = 0; i < k; ++i) {  // 给每个工人补上原始编号
            time[i].push_back(i);  // 追加到第 5 列，排序后仍能找回是哪个工人
        }  // 编号补全
        sort(time.begin(), time.end(), [](auto& a, auto& b) {  // 按「左岸到右岸 + 右岸到左岸」的往返耗时升序排序
            int x = a[0] + a[2], y = b[0] + b[2];  // 两人的基础往返耗时
            return x == y ? a[4] < b[4] : x < y;  // 耗时相同则按编号升序，保证顺序确定
        });  // 排序后：下标越大代表越慢，正好对应大根堆的优先级
        int cur = 0;  // 当前模拟时刻，从 0 开始
        priority_queue<int> waitInLeft, waitInRight;  // 两侧等待过桥的人：大根堆，堆顶下标最大即最慢的人
        priority_queue<pii, vector<pii>, greater<pii>> workInLeft, workInRight;  // 两侧正在搬箱子的人：小根堆，堆顶完成最早
        for (int i = 0; i < k; ++i) {  // 初始时所有工人都在左岸
            waitInLeft.push(i);  // 把每个工人放进左岸等待堆
        }  // 初始化完成
        while (true) {  // 持续模拟，唯一的出口在右岸彻底空闲时 return
            while (!workInLeft.empty()) {  // 把左岸已经搬完箱子的人转回等待堆
                auto [t, i] = workInLeft.top();  // 取出完成时刻最早的工人
                if (t > cur) {  // 最早的人还没完成，说明此刻不会有人转入
                    break;  // 结束本轮转移
                }  // 说明他已完成
                workInLeft.pop();  // 弹出这件已完成的任务
                waitInLeft.push(i);  // 该工人回到左岸等待过桥
            }  // 左岸转移完毕
            while (!workInRight.empty()) {  // 把右岸已经放完箱子的人转回等待堆
                auto [t, i] = workInRight.top();  // 取出右岸完成时刻最早的工人
                if (t > cur) {  // 还没完成就停止转移
                    break;  // 结束本轮转移
                }  // 说明他已完成
                workInRight.pop();  // 弹出这件已完成的任务
                waitInRight.push(i);  // 该工人回到右岸等待回程
            }  // 右岸转移完毕
            bool leftToGo = n > 0 && !waitInLeft.empty();  // 左岸还有箱子且有人在等，才可能出发去右岸
            bool rightToGo = !waitInRight.empty();  // 右岸有人等待回程，就应优先把他送回来
            if (!leftToGo && !rightToGo) {  // 两侧都没人能过桥，只能等某个工人搬完
                int nxt = 1 << 30;  // 用足够大的数作为下一时刻的初值
                if (!workInLeft.empty()) {  // 左岸还有正在搬箱子的人
                    nxt = min(nxt, workInLeft.top().first);  // 候选时刻：左岸最早完成时间
                }  // 左岸没有搬运中的工人
                if (!workInRight.empty()) {  // 右岸还有正在放箱子的人
                    nxt = min(nxt, workInRight.top().first);  // 候选时刻：右岸最早完成时间
                }  // 右岸没有搬运中的工人
                cur = nxt;  // 时钟直接快进到最早的完成时刻，避免空转
                continue;  // 进入下一轮重新处理事件
            }  // 事件推进完毕
            if (rightToGo) {  // 右岸有人等待时，回程优先于去程（题面规定）
                int i = waitInRight.top();  // 取右岸最慢（下标最大）的工人，他最优先
                waitInRight.pop();  // 让他离开等待队列
                cur += time[i][2];  // 时钟推进他「右岸到左岸」的过桥耗时
                if (n == 0 && waitInRight.empty() && workInRight.empty()) {  // 箱子已全部搬完且右岸再无他人
                    return cur;  // 全部完成，返回最终时刻
                }  // 还有人要处理，继续
                workInLeft.push({cur + time[i][3], i});  // 他已到左岸开始放箱子，登记其完成时刻
            } else {  // 否则一定是左岸有人可出发（两侧都无人的情况已被 continue 排除）
                int i = waitInLeft.top();  // 取左岸最慢的工人，他优先过桥
                waitInLeft.pop();  // 让他离开等待队列
                cur += time[i][0];  // 时钟推进他「左岸到右岸」的过桥耗时
                --n;  // 他从左岸带走一个箱子，待搬数量减一
                workInRight.push({cur + time[i][1], i});  // 他到右岸开始捡箱子，登记其完成时刻
            }  // 一次过桥处理完毕
        }  // 本轮结束，继续下一轮模拟
    }  // 方法结束
};  // 类定义结束