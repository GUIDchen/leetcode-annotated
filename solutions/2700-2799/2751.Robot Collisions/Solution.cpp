// 题目：2751. 机器人碰撞（Robot Collisions）
// 思路：按下标位置从左到右扫描，用栈保存仍向右走的机器人；遇到向左的机器人就与栈顶反复结算血量，最后按原顺序收集存活者。
// 时间复杂度：O(n log n)，排序主导，每个机器人最多入栈出栈一次；空间复杂度：O(n)，栈与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 公有成员：判题器直接调用下面的方法
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {  // positions：位置；healths：血量；directions：方向（'L' 左 / 'R' 右）；返回按原顺序的存活血量
        int n = positions.size();  // 机器人个数
        vector<int> idx(n);  // 下标数组，用来在排序后仍能找回原始顺序
        iota(idx.begin(), idx.end(), 0);  // 填充 0..n-1

        sort(idx.begin(), idx.end(), [&](int a, int b) {  // 按下标对应的位置从左到右排序，等价于让机器人沿数轴排好队
            return positions[a] < positions[b];  // 比较函数：位置小的排在前面
        });  // 结束 sort 调用

        vector<int> stk;  // 栈：存仍然向右走、可能被右侧机器人撞到的下标；栈内位置递增

        for (int i : idx) {  // 按位置从左到右依次处理每个机器人
            if (directions[i] == 'R') {  // 向右走：先入栈，等待右侧向左的机器人来碰撞
                stk.push_back(i);  // 记录这个向右的机器人
                continue;  // 向右的机器人不会立即碰撞，处理下一个
            }  // 结束“向右走”分支

            while (!stk.empty() && healths[i] > 0) {  // 当前是向左的机器人，且它还没被撞毁、栈里还有向右的机器人
                int j = stk.back();  // 栈顶是最近的向右机器人，最可能先与它相撞

                if (healths[j] > healths[i]) {  // 栈顶血量更高：当前机器人被毁，栈顶掉 1 点血
                    healths[j]--;  // 栈顶机器人血量减一
                    healths[i] = 0;  // 当前机器人血量置 0 表示被毁，循环随之结束
                } else if (healths[j] < healths[i]) {  // 当前机器人血量更高：栈顶被毁，当前机器人掉 1 点血后继续向左撞
                    healths[i]--;  // 当前机器人血量减一
                    healths[j] = 0;  // 栈顶机器人被撞毁
                    stk.pop_back();  // 被毁的机器人出栈
                } else {  // 两者血量相等：同归于尽
                    healths[i] = healths[j] = 0;  // 双方血量都置 0
                    stk.pop_back();  // 栈顶出栈
                    break;  // 当前机器人也被毁，无需再与更左边的机器人比较
                }  // 结束血量比较分支
            }  // 结束碰撞循环
        }  // 结束遍历

        vector<int> ans;  // 按原始下标顺序收集存活机器人的血量
        for (int h : healths) {  // 遍历每个机器人的血量
            if (h > 0) {  // 血量大于 0 表示存活
                ans.push_back(h);  // 记录该存活机器人的血量
            }  // 结束收集分支
        }  // 结束遍历血量
        return ans;  // 返回按原顺序排列的存活血量
    }  // 结束题解方法
};  // 结束题解类
